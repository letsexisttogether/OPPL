#pragma once

#include "Boundable/Boundable.hpp"

class VertexArray : public Boundable 
{
public:
    VertexArray();
    VertexArray(const VertexArray&) = default;
    VertexArray(VertexArray&&) = default;

    ~VertexArray();

    void Bind() noexcept override;
    void UnBind() noexcept override;

    VertexArray& operator = (const VertexArray&) noexcept = default;
    VertexArray& operator = (VertexArray&&) noexcept = default;

protected:
    void Generate() noexcept override;
};
