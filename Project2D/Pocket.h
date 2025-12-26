#pragma once
#include <glm/glm.hpp>
#include <vector>

class Pocket
{
    public:
        Pocket() {};
        Pocket(const glm::vec2& pos, float r) : m_position(pos), m_radius(r) {}

        ~Pocket() {};
        void Update(float deltaTime);
        void Draw();

        glm::vec2 GetPosition() const { return m_position; }
        float GetRadius() const { return m_radius; }

    protected:
        glm::vec2 m_position;
        float m_radius;

        bool ContainsBall(const glm::vec2& ballPosition) const;

};


