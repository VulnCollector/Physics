#pragma once
#include "PhysicsObject.h"
#include "glm/glm.hpp"


#define MIN_LINEAR_THRESHOLD 0.5f
#define MIN_ANGULAR_THRESHOLD 0.3f

class RigidBody : public PhysicsObject {
public:
    
    RigidBody(ShapeType shapeID, glm::vec2 position,
        glm::vec2 velocity, float orientation, float mass, float angularVelocity, float elasticity);
    ~RigidBody();

    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
    void applyForce(glm::vec2 force, glm::vec2 pos = glm::vec2(0, 0));
    

    glm::vec2 getPosition() const { return m_position; }
    float getOrientatation() const { return m_orientation; }
    glm::vec2 getVelocity() const { return m_velocity; }
    float getMass() const { return m_isKinematic ? INT_MAX : m_mass; }
    float getMoment() const { return m_isKinematic ? INT_MAX : m_moment; }
    float getAngularVelocity() const { return m_angularVelocity; }
    float getLinearDrag() const { return m_linearDrag; }
    float getAngularDrag() const { return m_angularDrag; }
    float getElasticity() const { return m_elasticity; }
    void setLinearDrag(float linearDrag);
    void setAngularDrag(float angularDrag);
    void setPosition(glm::vec2 position);
    void setKinematic(bool state) { m_isKinematic = state; }
    bool isKinematic() { return m_isKinematic; }

    void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }

    void resolveCollision(RigidBody* actor2, glm::vec2 contact, glm::vec2* collisionNormal=nullptr, float pen = 0);

    float getKineticEnergy();

    //float getPotentialEnergy();

protected:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    float m_mass;
    float m_orientation;    //2D so we only need a single float to represent our orientation
    float m_angularVelocity;
    float m_moment = 0;
    float m_linearDrag = 0.3f;
    float m_angularDrag = 0.3f;
    bool m_isKinematic = false;
   
};
