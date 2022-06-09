#include "Shader.h"

#include <Engine/Debug/Log.h>
#include <Engine/FileSys/File.h>
#include <Engine/Lib/Memory.h>

#include <SDL_gpu.h>

namespace SDG
{
    // Prepends shader version data depending on OpenGL or GLES.
    // This is needed to support particular graphics cards that require this heading data.
    static uint32_t
    LoadShader(GPU_ShaderEnum shaderType, const Path &path)
    {
        GPU_Renderer *renderer = GPU_GetCurrentRenderer();
        if (!renderer)
        {
            SDG_Core_Err("LoadShader, failed to get current renderer settings: {}", GPU_PopErrorCode().details);
            return 0;
        }

        // Open the shader file
        File file;
        if (!file.Open(path))
        {
            SDG_Core_Err("LoadShader file loading error: {}", file.GetError());
            return 0;
        }

        String source(62 + file.Size()); // 62 taken from length of the longest header below

        // Create the version header to prepend
        switch (renderer->shader_language)
        {
            case GPU_LANGUAGE_GLSL:    // High precision for OpenGL shaders.
                source.Append("#version 100\nprecision highp int;\n"
                    "precision highp float;\n");
                break;
            case GPU_LANGUAGE_GLSLES:  // Medium precision for OpenGLES shaders
                source.Append("#version 100\nprecision mediump int;\n"
                    "precision mediump float;\n");
                break;
            default:
                SDG_Core_Err("Shader language currently unsupported.");
                return 0;
        }

        source.Append(file.Cstr(), file.Size());
    
        return GPU_CompileShader(shaderType, source.Cstr());
    }

    struct Shader::Impl
    {
        Impl() : program(), block() { }
        uint32_t program;
        GPU_ShaderBlock block;
    };

    Shader::Shader() : impl(new Impl)
    {

    }


    Shader::~Shader()
    {
        Close();
    }

    uint32_t
    Shader::GetVarLocation(const std::string &varId) const
    {
        int location = GPU_GetUniformLocation(impl->program, varId.c_str());

        return (uint32_t)location;
    }


    bool
    Shader::Compile(const Path &vertexPath, const Path &fragPath)
    {
        uint32_t vertShader = LoadShader(GPU_VERTEX_SHADER, vertexPath);
        if (!vertShader)
        {
            SDG_Core_Err("Failed to load vertex shader ({}) =>\n{}", vertexPath.Str(),
                    GPU_GetShaderMessage());
            return false;
        }

        uint32_t fragShader = LoadShader(GPU_FRAGMENT_SHADER, fragPath);
        if (!fragShader)
        {
            SDG_Core_Err("Failed to load fragment shader ({})", fragPath.Str());
            GPU_FreeShader(vertShader);
            return false;
        }

        uint32_t shaderProgram = GPU_LinkShaders(vertShader, fragShader);
        if (!shaderProgram)
        {
            SDG_Core_Err("Failed to load shader program: {}", GPU_GetShaderMessage());
            GPU_FreeShader(vertShader);
            GPU_FreeShader(fragShader);
            return false;
        }

        // Now that the shaders have linked, we can free them.
        GPU_FreeShader(vertShader);
        GPU_FreeShader(fragShader);

        auto shaderBlock = GPU_LoadShaderBlock(impl->program,
                "gpu_Vertex",                // position name
                "gpu_TexCoord",             // texcoord name
                "gpu_Color",                   // color name
                "gpu_ModelViewProjectionMatrix"); // modelViewMatrix name

        impl->program = shaderProgram;
        impl->block = shaderBlock;
        return true;
    }

    // Set Float Uniform
    Shader &
    Shader::SetUniform(const std::string &varId, float value)
    {
        GPU_SetUniformf((int) GetVarLocation(varId), value);
        return *this;
    }



    // Set Vector of float uniform
    Shader &
    Shader::SetUniform(const std::string &varId, std::vector<float> values, int elementsPerValue)
    {
        GPU_SetUniformfv((int) GetVarLocation(varId), elementsPerValue, (int)values.size() / elementsPerValue, values.data());
        return *this;
    }

    void
    Shader::Close()
    {
        if (impl->program)
        {
            GPU_FreeShaderProgram(impl->program);
            impl->program = 0;
        }
    }

    void
    Shader::Activate()
    {
        GPU_ActivateShaderProgram(impl->program, &impl->block);
    }

    void
    Shader::Deactivate()
    {
        GPU_DeactivateShaderProgram();
    }


    Shader &
    Shader::SetImage(const std::string &varId, Texture texture)
    {
        GPU_SetShaderImage(texture.Image().Get(), GetVarLocation(varId), 1);
        return *this;
    }

}

