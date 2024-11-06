#include "ModelFactory.h"

// --- public ------------------------------------------------------------------
ModelFactory::ModelFactory(ShaderFactory* t_shaderFactory) : m_shaderFactory(t_shaderFactory) { }

void ModelFactory::addVBO(const std::string& t_name, std::unique_ptr<VBO> t_vbo) {
    this->m_vbos[t_name] = std::move(t_vbo);
}

void ModelFactory::addVAO(const std::string& t_name, std::unique_ptr<VAO> t_vao) {
    this->m_vaos[t_name] = std::move(t_vao);
}

VAO* ModelFactory::getVertexResources(const std::string& t_name) const {
    auto it = this->m_vaos.find(t_name);
    return (it != this->m_vaos.end()) ? it->second.get() : nullptr;
}

VAO* ModelFactory::createVertexResources(const std::string& t_name, const std::vector<float>& dataVBO) {
//VAO* ModelFactory::createVertexResources(const std::vector<float>& dataVBO) {
    // vbo
    auto vbo = std::make_unique<VBO>(dataVBO);

    // vao
    auto vao = std::make_unique<VAO>();
    //vao->addBuffer(*vbo, 0, 3, 0, nullptr);
    vao->addBuffer(*vbo, 0, 3, 6 * sizeof(float), (GLvoid*)0);
    vao->addBuffer(*vbo, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

    this->m_vbos[t_name] = std::move(vbo);
    this->m_vaos[t_name] = std::move(vao);
    //this->m_vbos.push_back(std::move(vbo));
    //this->m_vaos.push_back(std::move(vao));

    return this->getVertexResources(t_name);
    //return this->m_vaos.back().get();
}

std::unique_ptr<Model> ModelFactory::createModel(
    const std::string& t_name,
    const std::string& t_shaderProgramName,
    const std::vector<float>& dataVBO,
    GLint t_first,
    GLsizei t_count,
    const glm::vec3& t_position = glm::vec3(0.0f),
    float t_angleX = 0.0f, float t_angleY = 0.0f, float t_angleZ = 0.0f,
    const glm::vec3& t_scale = glm::vec3(1.0f))
{
    // vertex resources (vbo & vao) + shader program = model
    auto vao = this->createVertexResources(t_name, dataVBO);
    //auto vao = this->createVertexResources(dataVBO);
    auto shaderProgram = this->m_shaderFactory->getShaderProgram(t_shaderProgramName);

    auto model = std::make_unique<Model>(shaderProgram, vao, t_first, t_count);
    model->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(t_position));
    model->getTransformation()->addStep(std::make_shared<TransformationStepRotate>(t_angleX, t_angleY, t_angleZ));
    model->getTransformation()->addStep(std::make_shared<TransformationStepScale>(t_scale));

    return model;
}
