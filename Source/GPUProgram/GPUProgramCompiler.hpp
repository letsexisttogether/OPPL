#pragma once

#include <memory>

#include "Boundable/Boundable.hpp"
#include "Shaders/ShaderSpawner.hpp"


class GPUProgram : Boundable
{
public:
    GPUProgram() = delete;
    GPUProgram(const GPUProgram&) = delete;
    GPUProgram(GPUProgram&&) = default;

    GPUProgram(Shader&& vertexSpawner, 
        Shader&& fragmentSpawner);

    ~GPUProgram() = default;

    void Bind() noexcept override;
    void UnBind() noexcept override;

    GPUProgram& operator = (const GPUProgram&) noexcept
        = delete;
    GPUProgram& operator = (GPUProgram&&) noexcept
        = delete;

protected:
    void Generate() noexcept override;

private:
    Shader m_VertextSpawner{};
    Shader m_FragmentSpawner{};
};
