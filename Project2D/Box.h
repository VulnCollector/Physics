#pragma once
#include "RigidBody.h"
#include "glm/glm.hpp"
#include "Gizmos.h"

class Box : public RigidBody
{
public:
    
    Box(glm::vec2 position, glm::vec2 velocity, float mass, glm::vec2 extents, glm::vec4 colour,
        float orientation, float elasticity);
    ~Box();
    void fixedUpdate(glm::vec2 gravity, float timeStep);
    void draw();
    float getWidth() const;
    float getHeight() const;
    glm::vec2 getExtents() const { return m_extents; }
    glm::vec2 getLocalX() const { return m_localX; }
    glm::vec2 getLocalY() const { return m_localY; }
    bool checkBoxCorners(const Box& box, glm::vec2& contact, int& numContacts,
        float& pen, glm::vec2& edgeNormal);
    

protected:
    glm::vec2 m_extents; // the halfedge lengths
    glm::vec4 m_colour;

    // store the local x,y axes of the box based on its angle of rotation
    glm::vec2 m_localX;
    glm::vec2 m_localY;
};

