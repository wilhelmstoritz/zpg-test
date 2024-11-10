#pragma once

#include "ShaderProgram.h"

class Light {
public:
    Light(const glm::vec3& position, const glm::vec3& color);

    void applyToShader(const ShaderProgram& shaderProgram) const;

    void setPosition(const glm::vec3& position);
    void setColor(const glm::vec3& color);

    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_color;
};
