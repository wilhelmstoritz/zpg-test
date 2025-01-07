#include "ModelFactory.h"

// === templates implementation ================================================
// --- public ------------------------------------------------------------------
template <typename T, typename>
std::unique_ptr<T> ModelFactory::createModel(
    const std::string& t_name,
    ShaderProgram* t_shaderProgram,
    VAO* t_vao, IBO* t_ibo,
    const GLint t_first, const GLsizei t_count,
    const glm::vec3& t_scale,
    const glm::vec3& t_rotation,
    const glm::vec3& t_position)
{
    // shader program + vertex resources (vbo & vao) = model
    auto model = std::make_unique<T>(t_name, t_shaderProgram, t_vao, t_ibo, t_first, t_count);
    model->getTransformation()->setTranslation(t_position);
    model->getTransformation()->setRotationEulerAngles(t_rotation);
    model->getTransformation()->setScale(t_scale);

    return model;
}

template <typename T, typename>
std::unique_ptr<T> ModelFactory::createModel(
    const std::string& t_name,
    ShaderProgram* t_shaderProgram,
    VAO* t_vao,
    const GLint t_first, const GLsizei t_count,
    const glm::vec3& t_scale,
    const glm::vec3& t_rotation,
    const glm::vec3& t_position)
{
    return this->createModel<T>(
        t_name,
        t_shaderProgram,
        t_vao, nullptr,
        t_first, t_count,
        t_scale, t_rotation, t_position);
    /*
    // shader program + vertex resources (vbo & vao) = model
    auto model = std::make_unique<T>(t_name, t_shaderProgram, t_vao, t_first, t_count);
    model->getTransformation()->setTranslation(t_position);
    model->getTransformation()->setRotationEulerAngles(t_rotation);
    model->getTransformation()->setScale(t_scale);

    return model;
    */
}
