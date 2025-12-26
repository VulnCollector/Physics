#pragma once
#include "glm/vec2.hpp"

enum ShapeType {
    PLANE = 0,
    SPHERE,
    BOX
};

class PhysicsObject {
protected:
    PhysicsObject() : m_shapeID(SPHERE) {}
    PhysicsObject(ShapeType a_shapeID, float elasticity) : m_shapeID(a_shapeID), m_elasticity(elasticity) {}

public:
    virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
    virtual void draw() = 0;
    virtual void resetPosition() {};
    ShapeType getShapeID() { return m_shapeID; }

protected:
    ShapeType m_shapeID;
    float m_elasticity;
};

