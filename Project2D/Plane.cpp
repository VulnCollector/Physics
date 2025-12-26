#include "Plane.h"
#include "PhysicsScene.h"
using namespace glm;

Plane::Plane() : PhysicsObject(ShapeType::PLANE, 1) {
    m_distanceToOrigin = 0;
    m_normal = vec2(0, 1);
}

Plane::Plane(glm::vec2 normal, float distance, float elasticity) : PhysicsObject(ShapeType::PLANE, elasticity)
{
	m_normal = normal;
	m_distanceToOrigin = distance;
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::draw()
{
    float lineSegmentLength = 300;
    vec2 centerPoint = m_normal * m_distanceToOrigin;
    // easy to rotate normal through 90 degrees around z
    vec2 parallel(m_normal.y, -m_normal.x);
    vec4 colourFade = m_colour;
    colourFade.a = 0;
    vec2 start = centerPoint + (parallel * lineSegmentLength);
    vec2 end = centerPoint - (parallel * lineSegmentLength);
    //aie::Gizmos::add2DLine(start, end, colour);
    aie::Gizmos::add2DTri(start, end, start - m_normal * 10.0f, m_colour, m_colour, colourFade);
    aie::Gizmos::add2DTri(end, end - m_normal * 10.0f, start - m_normal * 10.0f, m_colour, colourFade, colourFade);
}

void Plane::resetPosition()
{
    //m_distanceToOrigin = 0;
}

void Plane::resolveCollision(RigidBody* actor2, glm::vec2 contact)
{
    // the position at which we'll apply the force relative to the object's COM
    glm::vec2 localContact = contact - actor2->getPosition();
    // the plane isn't moving, so the relative velocity is just actor2's velocity
    //at the contact point
        glm::vec2 vRel = actor2->getVelocity() + actor2->getAngularVelocity() * vec2(-
            localContact.y, localContact.x);
    float velocityIntoPlane = glm::dot(vRel, m_normal);
    // perfectly elasticity collisions for now
    float e = (getElasticity() + actor2->getElasticity());

    // this is the perpendicular distance we apply the force at relative to the
    //COM, so Torque = F * r
        float r = glm::dot(localContact, glm::vec2(m_normal.y, -m_normal.x));
    // work out the "effective mass" - this is a combination of moment of
    // inertia and mass, and tells us how much the contact point velocity
    // will change with the force we're applying
    float mass0 = 1.0f / (1.0f / actor2->getMass() + (r * r) / actor2 -> getMoment());
    float j = -(1 + e) * velocityIntoPlane * mass0;
    vec2 force = m_normal * j;
    float kePre = actor2->getKineticEnergy();
    actor2->applyForce(force, contact - actor2->getPosition());
    float pen = glm::dot(contact, m_normal) - m_distanceToOrigin;
    PhysicsScene::ApplyContactForces(actor2, nullptr, m_normal, pen);
    float kePost = actor2->getKineticEnergy();
    float deltaKE = kePost - kePre;
    if (deltaKE > kePost * 0.01f)
        std::cout << "Kinetic Energy discrepancy greater than 1% detected!!";
}
