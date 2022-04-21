//
// Created by Aaron Ishibashi on 4/13/22.
//
#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <SDL_gpu.h>

namespace SDG
{
    class Shader {
    public:
        Shader();
        ~Shader();
        Shader &SetVariable(const std::string &varId, float value);
        Shader &SetImage(const std::string &varId, GPU_Image *image);
        Shader &SetVariable(const std::string &varId, std::vector<float> values, int elementsPerValue);
        uint32_t GetVarLocation(const std::string &varId) const;
        bool Compile(const std::string &vertexPath, const std::string &fragPath);
        void Close();
        void Activate();
    private:
        uint32_t program;
        GPU_ShaderBlock block;
    };
}
