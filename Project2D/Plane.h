#pragma once
#include "PhysicsObject.h"
#include "glm/glm.hpp"
#include "Gizmos.h"
#include "RigidBody.h"
#include <iostream>

class Plane : public PhysicsObject
{
public:
    Plane();
    Plane(glm::vec2 normal, float distance, float elasticity);
    ~Plane();

    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
    virtual void draw();
    virtual void resetPosition();

    glm::vec2 getNormal() { return m_normal; }
    float getDistance() { return m_distanceToOrigin; }
    float getElasticity() const { return m_elasticity; }
    void resolveCollision(RigidBody* actor2, glm::vec2 contact);

protected:
    glm::vec2 m_normal;
    float m_distanceToOrigin;
    glm::vec4 m_colour = glm::vec4(1, 0, 0, 1);
};

