#include "Ball.h"
#include "Pocket.h"

bool Ball::IsInPocket(const Pocket& pocket) const
{
    float dx = m_position.x - pocket.GetPosition().x;
    float dy = m_position.y - pocket.GetPosition().y;
    float distanceSquared = dx * dx + dy * dy;
    float combinedRadius = m_radius + pocket.GetRadius();

    return distanceSquared <= combinedRadius * combinedRadius;
}
