#include "Pocket.h"
#include "Gizmos.h"

void Pocket::Update(float deltaTime)
{

}

void Pocket::Draw()
{
    aie::Gizmos::add2DCircle(m_position, m_radius, 20, glm::vec4(0, 0, 0, 1));
}

bool Pocket::ContainsBall(const glm::vec2& ballPosition) const
{
    return glm::distance(ballPosition, m_position) < m_radius;
}
