//
// Created by Aaron Ishibashi on 4/13/22.
//
#include "Shader.h"
#include "Logging.h"


// Prepends shader version data depending on OpenGL or GLES.
// This is needed to support particular graphics cards that require this heading data.
// Code mainly from https://github.com/ryancheung/sdl2-gpu-with-imgui/blob/master/Main.cpp
static uint32_t LoadShader(GPU_ShaderEnum shaderType, const std::string &path)
{
    SDL_RWops *rwops;
    char *shaderSource;
    const char *versionHeader;
    int64_t fileSize, versionHeaderSize;
    GPU_Renderer *renderer = GPU_GetCurrentRenderer();
    uint32_t shader;

    // Open the shader file
    rwops = SDL_RWFromFile(path.c_str(), "rb");
    if (!rwops)
    {
        SDG_Err("Failed to load shader file \"{}\": {}", path, SDL_GetError());
        return 0;
    }

    // Get source length
    fileSize = SDL_RWseek(rwops, 0, SEEK_END);
    if (fileSize < 0)
    {
        SDG_Err("File seek failed while getting shader source file size: {}", SDL_GetError());
        return 0;
    }
    SDL_RWseek(rwops, 0, SEEK_SET);


    // Create the version header to prepend
    switch (renderer->shader_language)
    {
        case GPU_LANGUAGE_GLSL:
            versionHeader = "#version 100\nprecision highp int;\nprecision highp float;\n";
            break;
        case GPU_LANGUAGE_GLSLES:
            versionHeader = "#version 100\nprecision mediump int;\nprecision mediump float;\n";
            break;
        default:
            SDG_Err("Shader language currently not supported.");
            return 0;
    }

    versionHeaderSize = strlen(versionHeader);

    // Allocate shader source buffer
    shaderSource = (char *)malloc(versionHeaderSize + fileSize + 1);

    // Prepend version header
    strcpy(shaderSource, versionHeader);

    // Read shader file into buffer
    SDL_RWread(rwops, shaderSource + versionHeaderSize, 1, fileSize);
    shaderSource[versionHeaderSize + fileSize] = '\0';

    // Compile shader
    shader = GPU_CompileShader(shaderType, shaderSource);

    // Clean up
    free(shaderSource);
    SDL_RWclose(rwops);

    return shader;
}


Shader::Shader() : block{}, program{}
{

}


Shader::~Shader()
{
    Close();
}



uint32_t
Shader::GetVarLocation(const std::string &varId) const
{
    int location = GPU_GetUniformLocation(program, varId.c_str());
    //SDG_Log("Uniform \"{}\" location: {}", varId, location);
    return (uint32_t)location;
}


bool
Shader::Compile(const std::string &vertexPath, const std::string &fragPath)
{
    uint32_t vertShader = LoadShader(GPU_VERTEX_SHADER, vertexPath.c_str());
    if (!vertShader)
    {
        SDG_Err("Failed to load vertex shader ({}): {}", vertexPath, GPU_GetShaderMessage());
        return false;
    }

    uint32_t fragShader = LoadShader(GPU_FRAGMENT_SHADER, fragPath.c_str());
    if (!fragShader)
    {
        SDG_Err("Failed to load fragment shader: {}", GPU_GetShaderMessage());
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

    GPU_FreeShader(vertShader);
    GPU_FreeShader(fragShader);

    auto shaderBlock = GPU_LoadShaderBlock(program, "gpu_Vertex", "gpu_TexCoord", NULL, "gpu_ModelViewProjectionMatrix");

    program = shaderProgram;
    block = shaderBlock;
    return true;
}

// Set Float Uniform
Shader &Shader::SetVariable(const std::string &varId, float value)
{
    GPU_SetUniformf((int) GetVarLocation(varId), value);
    return *this;
}

// Set Vector of float uniform
Shader &Shader::SetVariable(const std::string &varId, std::vector<float> values, int elementsPerValue)
{
    GPU_SetUniformfv((int) GetVarLocation(varId), elementsPerValue, (int)values.size() / elementsPerValue, values.data());
    return *this;
}

void Shader::Close()
{
    if (program)
    {
        GPU_FreeShaderProgram(program);
        program = 0;
    }
}

void Shader::Activate()
{
    GPU_ActivateShaderProgram(program, &block);
}



Shader &Shader::SetImage(const std::string &varId, GPU_Image *image)
{
    GPU_SetShaderImage(image, GetVarLocation(varId), 1);
    return *this;
}


