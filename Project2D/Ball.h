#pragma once
#include <glm/glm.hpp>
#include "Sphere.h"

class Pocket;

class Ball : public Sphere
{
public:
    Ball(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color, float elasticity)
        : Sphere(position, velocity, mass, radius, color, elasticity), m_pocketed(false) {}

    bool IsInPocket(const Pocket& pocket) const;
    bool IsPocketed() const { return m_pocketed; }
    void SetPocketed(bool pocketed) { m_pocketed = pocketed; }

    void SetColour(glm::vec4 colour) { m_colour = colour; }

private:
    bool m_pocketed;
};
