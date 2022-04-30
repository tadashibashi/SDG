//
// Created by Aaron Ishibashi on 4/13/22.
//
#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <SDL_gpu.h>
#include "Texture2D.h"

namespace SDG
{
    class Shader {
        struct Impl;
    public:
        Shader();
        ~Shader();
        Shader &SetUniform(const std::string &varId, float value);
        Shader &SetImage(const std::string &varId, Texture2D texture);

        /// Set a vector of floats to a shader uniform value
        Shader &SetUniform(const std::string &varId, std::vector<float> values, int elementsPerValue);
        uint32_t GetVarLocation(const std::string &varId) const;
        bool Compile(const std::string &vertexPath, const std::string &fragPath);
        void Close();
        void Activate();
        static void Deactivate();
    private:
        uint32_t program;
        GPU_ShaderBlock block;
    };
}
