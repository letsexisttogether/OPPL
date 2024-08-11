#include "Boundable.hpp"

#include <GLEW/glew.h>

Boundable::Boundable(const Type type)
    : m_Type{ type }
{}

Boundable::Boundable(Boundable&& boundable)
    : m_ID{ boundable.m_ID }, m_Type{ boundable.m_Type }
{
    boundable.m_ID = BoundableID{}; 
}

Boundable::BoundableID Boundable::GetID() const noexcept
{
    return m_ID;
}

Boundable& Boundable::operator = (Boundable&& boundable) noexcept
{
    m_ID = boundable.m_ID;
    m_Type = boundable.m_Type;

    boundable.m_ID = BoundableID{};

    return *this;
};

