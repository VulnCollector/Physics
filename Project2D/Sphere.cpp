#include "Sphere.h"
#include "Gizmos.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, float elasticity) :
    RigidBody(SPHERE, position, velocity, 0.0f, mass, 0.0f, elasticity)
{
    m_radius = radius;
    m_colour = colour;
    m_moment = 0.5f * mass * radius * radius;
}

Sphere::~Sphere()
{
}

void Sphere::draw()
{
   // glm::vec2 end = glm::vec2(std::cos(m_orientation), std::sin(m_orientation)) * m_radius;
    aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
  //  aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(0, 0, 0, 0));
}
