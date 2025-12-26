#pragma once
#include <glm/glm.hpp>

class Stick
{
public:
    Stick() {}
    Stick(const glm::vec2 cueBallPosition);

    void Update(float deltaTime);
    void Draw();
   
    float getAngle() { return m_angle; }
    void setAngle(float angle) { m_angle = angle; }
    void setPower(float power) { m_power = power; }

    glm::vec2 GetDirection() const;
    float GetPower() const;

    void SetPosition(const glm::vec2 newPosition);

private:
    glm::vec2 m_cueBallPosition;
    float m_angle;
    float m_power;
    float m_length;
};
