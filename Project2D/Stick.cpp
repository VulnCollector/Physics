#include "Stick.h"
#include "Gizmos.h"
#include "imgui.h"
#include <glm/ext.hpp>

Stick::Stick(const glm::vec2 cueBallPosition)
    : m_cueBallPosition({ -25,0 }), m_angle(0), m_power(0), m_length(10.0f) {}

void Stick::Update(float deltaTime)
{
}

void Stick::Draw()
{
    glm::vec2 dir = glm::vec2(glm::cos(m_angle), glm::sin(m_angle));
    glm::vec2 end = m_cueBallPosition - dir * m_length;

    aie::Gizmos::add2DLine(m_cueBallPosition, end, glm::vec4(0.6f, 0.3f, 0.1f, 1));
}



glm::vec2 Stick::GetDirection() const
{
    return glm::vec2(glm::cos(m_angle), glm::sin(m_angle));
}

float Stick::GetPower() const
{
    return m_power;
}

void Stick::SetPosition(const glm::vec2 newPosition)
{
    m_cueBallPosition = newPosition;
}

