//
// Created by Aaron Ishibashi on 4/13/22.
//
#include "Shader.h"
#include "Logging.h"
#include "FileSys.h"

#include "Platform.h"


// Prepends shader version data depending on OpenGL or GLES.
// This is needed to support particular graphics cards that require this heading data.
// Code mainly from https://github.com/ryancheung/sdl2-gpu-with-imgui/blob/master/Main.cpp
static uint32_t
LoadShader(GPU_ShaderEnum shaderType, const std::string &path)
{
    SDG::RWopsMem rwops;
    char *source;
    const char *header;
    int64_t fileSize, headerSize;
    GPU_Renderer *renderer = GPU_GetCurrentRenderer();
    uint32_t shader;

    // Open the shader file
    rwops = SDG::FileSys::DecryptFile(path, SDG::FileSys::BaseDir::Root, &fileSize);
    if (!rwops.IsOpen())
    {
        // Open file error messages already handled in DecryptFile.
        return 0;
    }

    // Create the version header to prepend
    switch (renderer->shader_language)
    {
        case GPU_LANGUAGE_GLSL:
            header = "#version 100\nprecision highp int;\nprecision highp float;\n";
            break;
        case GPU_LANGUAGE_GLSLES:
            header = "#version 100\nprecision mediump int;\nprecision mediump float;\n";
            break;
        default:
            SDG_Err("Shader language currently unsupported.");
            return 0;
    }

    headerSize = strlen(header);

    // Allocate shader source buffer
    source = (char *)malloc(headerSize + fileSize + 1);

    // Prepend version header
    strcpy_s(source, headerSize + 1, header);

    // Read shader file into buffer
    SDL_RWread(rwops.rwops, source + headerSize, fileSize, 1);
    source[headerSize + fileSize] = '\0'; // null terminate the str

    // Compile shader
    shader = GPU_CompileShader(shaderType, source);

    // Clean up
    free(source);
    rwops.Free();

    return shader;
}


SDG::Shader::Shader() : block{}, program{}
{

}


SDG::Shader::~Shader()
{
    Close();
}



uint32_t
SDG::Shader::GetVarLocation(const std::string &varId) const
{
    int location = GPU_GetUniformLocation(program, varId.c_str());

    return (uint32_t)location;
}


bool
SDG::Shader::Compile(const std::string &vertexPath, const std::string &fragPath)
{
    uint32_t vertShader = LoadShader(GPU_VERTEX_SHADER, vertexPath.c_str());
    if (!vertShader)
    {
        SDG_Err("Failed to load vertex shader ({}) =>\n{}", vertexPath, GPU_GetShaderMessage());
        return false;
    }

    uint32_t fragShader = LoadShader(GPU_FRAGMENT_SHADER, fragPath.c_str());
    if (!fragShader)
    {
        SDG_Err("Failed to load fragment shader ({})", fragPath);
        GPU_FreeShader(vertShader);
        return false;
    }

    uint32_t shaderProgram = GPU_LinkShaders(vertShader, fragShader);
    if (!shaderProgram)
    {
        SDG_Err("Failed to load shader program: {}", GPU_GetShaderMessage());
        GPU_FreeShader(vertShader);
        GPU_FreeShader(fragShader);
        return false;
    }

    // Now that the shaders have linked, we can free them.
    GPU_FreeShader(vertShader);
    GPU_FreeShader(fragShader);

    auto shaderBlock = GPU_LoadShaderBlock(program,
            "gpu_Vertex",                // position name
            "gpu_TexCoord",             // texcoord name
            "gpu_Color",                   // color name
            "gpu_ModelViewProjectionMatrix"); // modelViewMatrix name

    program = shaderProgram;
    block = shaderBlock;
    return true;
}

// Set Float Uniform
SDG::Shader &
SDG::Shader::SetVariable(const std::string &varId, float value)
{
    GPU_SetUniformf((int) GetVarLocation(varId), value);
    return *this;
}

// Set Vector of float uniform
SDG::Shader &
SDG::Shader::SetVariable(const std::string &varId, std::vector<float> values, int elementsPerValue)
{
    GPU_SetUniformfv((int) GetVarLocation(varId), elementsPerValue, (int)values.size() / elementsPerValue, values.data());
    return *this;
}

void
SDG::Shader::Close()
{
    if (program)
    {
        GPU_FreeShaderProgram(program);
        program = 0;
    }
}

void
SDG::Shader::Activate()
{
    GPU_ActivateShaderProgram(program, &block);
}

void
SDG::Shader::Deactivate()
{
    GPU_DeactivateShaderProgram();
}



SDG::Shader &
SDG::Shader::SetImage(const std::string &varId, GPU_Image *image)
{
    GPU_SetShaderImage(image, GetVarLocation(varId), 1);
    return *this;
}


