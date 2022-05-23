#include "Shader.h"
#include "SDG/Debug.hpp"
#include "SDG/FileSys/File.h"
#include <SDL_gpu.h>

// Prepends shader version data depending on OpenGL or GLES.
// This is needed to support particular graphics cards that require this heading data.
// Code mainly from https://github.com/ryancheung/sdl2-gpu-with-imgui/blob/master/Main.cpp
static uint32_t
LoadShader(GPU_ShaderEnum shaderType, const SDG::Path &path)
{
    char *source;
    const char *header;
    size_t headerSize;
    uint32_t shader;
    GPU_Renderer *renderer = GPU_GetCurrentRenderer();


    // Open the shader file
    SDG::File file;
    if (!file.Open(path))
    {
        SDG_Core_Err("LoadShader file loading error: {}", file.GetError());
        return 0;
    }

    // Create the version header to prepend
    switch (renderer->shader_language)
    {
        case GPU_LANGUAGE_GLSL:    // High precision for OpenGL shaders
            header = "#version 100\nprecision highp int;\nprecision highp float;\n";
            break;
        case GPU_LANGUAGE_GLSLES:  // Medium precision for OpenGLES shaders
            header = "#version 100\nprecision mediump int;\nprecision mediump float;\n";
            break;
        default:
            SDG_Core_Err("Shader language currently unsupported.");
            return 0;
    }

    headerSize = strlen(header);

    // Allocate shader source buffer
    source = (char *)malloc(headerSize + file.Size() + 1);
        // Prepend version header and write in shader file contents
        memcpy(source, header, headerSize);
        memcpy(source + headerSize, file.Data(), file.Size());
        source[headerSize + file.Size()] = '\0'; // null terminate the str

    // Compile shader
    shader = GPU_CompileShader(shaderType, source);

    // Clean up
    free(source);

    return shader;
}

struct SDG::Shader::Impl {
    Impl() : program(), block() { }
    uint32_t program;
    GPU_ShaderBlock block;
};

SDG::Shader::Shader() : impl(new Impl)
{

}


SDG::Shader::~Shader()
{
    Close();
}



uint32_t
SDG::Shader::GetVarLocation(const std::string &varId) const
{
    int location = GPU_GetUniformLocation(impl->program, varId.c_str());

    return (uint32_t)location;
}


bool
SDG::Shader::Compile(const Path &vertexPath, const Path &fragPath)
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
SDG::Shader &
SDG::Shader::SetUniform(const std::string &varId, float value)
{
    GPU_SetUniformf((int) GetVarLocation(varId), value);
    return *this;
}



// Set Vector of float uniform
SDG::Shader &
SDG::Shader::SetUniform(const std::string &varId, std::vector<float> values, int elementsPerValue)
{
    GPU_SetUniformfv((int) GetVarLocation(varId), elementsPerValue, (int)values.size() / elementsPerValue, values.data());
    return *this;
}

void
SDG::Shader::Close()
{
    if (impl->program)
    {
        GPU_FreeShaderProgram(impl->program);
        impl->program = 0;
    }
}

void
SDG::Shader::Activate()
{
    GPU_ActivateShaderProgram(impl->program, &impl->block);
}

void
SDG::Shader::Deactivate()
{
    GPU_DeactivateShaderProgram();
}


SDG::Shader &
SDG::Shader::SetImage(const std::string &varId, Texture2D texture)
{
    GPU_SetShaderImage(texture.Image().Get(), GetVarLocation(varId), 1);
    return *this;
}
