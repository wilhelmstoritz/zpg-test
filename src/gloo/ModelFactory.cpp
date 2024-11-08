#include "ModelFactory.h"

// --- public ------------------------------------------------------------------
ModelFactory::ModelFactory(ShaderFactory* t_shaderFactory) : m_shaderFactory(t_shaderFactory) { }

void ModelFactory::addVBO(const std::string& t_name, std::unique_ptr<VBO> t_vbo) {
    this->m_vbos[t_name] = std::move(t_vbo);
}

void ModelFactory::addVAO(const std::string& t_name, std::unique_ptr<VAO> t_vao) {
    this->m_vaos[t_name] = std::move(t_vao);
}

void ModelFactory::addModel(const std::string& t_name, std::unique_ptr<Model> t_model) {
    this->m_models[t_name] = std::move(t_model);
}

VBO* ModelFactory::getVBO(const std::string& t_name) const {
    auto it = this->m_vbos.find(t_name);

    return (it != this->m_vbos.end()) ? it->second.get() : nullptr;
}

VAO* ModelFactory::getVAO(const std::string& t_name) const {
    auto it = this->m_vaos.find(t_name);

    return (it != this->m_vaos.end()) ? it->second.get() : nullptr;
}

Model* ModelFactory::getModel(const std::string& t_name) const {
    auto it = this->m_models.find(t_name);

    return (it != this->m_models.end()) ? it->second.get() : nullptr;
}

VBO* ModelFactory::createVBO(const std::string& t_name, const std::vector<float>& t_data) {
    auto vbo = std::make_unique<VBO>(t_data);
    this->addVBO(t_name, std::move(vbo));

    return this->getVBO(t_name);
}

VAO* ModelFactory::createVAO(const std::string& t_name, const VBO& t_VBO) {
    auto vao = std::make_unique<VAO>();
    //vao->addBuffer(t_VBO, 0, 3, 0, nullptr);
    vao->addBuffer(t_VBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
    vao->addBuffer(t_VBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    this->addVAO(t_name, std::move(vao));

    return this->getVAO(t_name);
}

VAO* ModelFactory::createVertexResources(const std::string& t_name, const std::vector<float>& t_data) {
    auto vbo = this->createVBO(t_name, t_data);
    auto vao = this->createVAO(t_name, *vbo);
    //auto vao = this->createVAO(t_name, *this->getVBO(t_name));

    return this->getVAO(t_name);
}

Model* ModelFactory::createModel(
    const std::string& t_name,
    const std::string& t_shaderProgramName,
    const std::string& t_VAOName,
    GLint t_first, GLsizei t_count)
{
    // vertex resources (vbo & vao) + shader program = model
    auto vao = this->getVAO(t_VAOName);
    auto shaderProgram = this->m_shaderFactory->getShaderProgram(t_shaderProgramName);

    auto model = std::make_unique<Model>(shaderProgram, vao, t_first, t_count);
    this->addModel(t_name, std::move(model));

    return this->getModel(t_name);
}

Model* ModelFactory::createModel(
    const std::string& t_name,
    const std::string& t_shaderProgramName,
    const std::string& t_VAOName,
    GLint t_first, GLsizei t_count,
    const glm::vec3& t_position,
    float t_angleX, float t_angleY, float t_angleZ,
    const glm::vec3& t_scale)
{
    auto model = this->createModel(t_name, t_shaderProgramName, t_VAOName, t_first, t_count);
    model->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(t_position));
    model->getTransformation()->addStep(std::make_shared<TransformationStepRotate>(t_angleX, t_angleY, t_angleZ));
    model->getTransformation()->addStep(std::make_shared<TransformationStepScale>(t_scale));

    return model;
}

Model* ModelFactory::createModel(
    const std::string& t_name,
    const std::string& t_shaderProgramName,
    const std::vector<float>& dataVBO,
    GLint t_first, GLsizei t_count,
    const glm::vec3& t_position = glm::vec3(0.0f),
    float t_angleX = 0.0f, float t_angleY = 0.0f, float t_angleZ = 0.0f,
    const glm::vec3& t_scale = glm::vec3(1.0f))
{
    // create vertex resources (vbo & vao)
    auto vao = this->createVertexResources(t_name, dataVBO);

    return this->createModel(
        t_name,
        t_shaderProgramName,
        t_name, // vao name
        t_first, t_count,
        t_position,
        t_angleX, t_angleY, t_angleZ,
        t_scale
    );
}
