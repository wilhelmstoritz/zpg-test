#include "ModelFactory.h"
#include "TransformationStepTranslate.h"
#include "TransformationStepRotate.h"
#include "TransformationStepScale.h"

// initialization of static class members
const VAO::BufferInfo ModelFactory::s_defaultBuffer = { 0, 3, 0, nullptr };
const VAO::BufferInfo ModelFactory::s_defaultPositionBuffer = { 0, 3, 6 * sizeof(float), (GLvoid*)0 };
const VAO::BufferInfo ModelFactory::s_defaultColorBuffer = { 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)) };
const VAO::BufferInfo ModelFactory::s_defaultNormalBuffer = { 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)) };

const std::vector<VAO::BufferInfo> ModelFactory::s_defaultBufferList = { ModelFactory::s_defaultBuffer };
const std::vector<VAO::BufferInfo> ModelFactory::s_defaultPositionColorBufferList = {
    ModelFactory::s_defaultPositionBuffer,
    ModelFactory::s_defaultColorBuffer };
const std::vector<VAO::BufferInfo> ModelFactory::s_defaultPositionNormalBufferList = {
    ModelFactory::s_defaultPositionBuffer,
    ModelFactory::s_defaultNormalBuffer };

// --- public ------------------------------------------------------------------
ModelFactory::ModelFactory(ShaderFactory* t_shaderFactory) : m_shaderFactory(t_shaderFactory) { }

void ModelFactory::clearAll() {
    this->m_models.clear();
    this->m_vaos.clear();
	this->m_vbos.clear();
}

void ModelFactory::addVBO(const std::string& t_name, std::unique_ptr<VBO> t_vbo) {
    this->m_vbos[t_name] = std::move(t_vbo);
}

void ModelFactory::addVAO(const std::string& t_name, std::unique_ptr<VAO> t_vao) {
    this->m_vaos[t_name] = std::move(t_vao);
}

void ModelFactory::addModel(const std::string& t_name, std::unique_ptr<Model> t_model) {
    this->m_models[t_name] = std::move(t_model);
}

void ModelFactory::removeVBO(const std::string& t_name) {
	this->m_vbos.erase(t_name);
}

void ModelFactory::removeVAO(const std::string& t_name) {
	this->m_vaos.erase(t_name);
}

void ModelFactory::removeModel(const std::string& t_name) {
	this->m_models.erase(t_name);
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

const std::unordered_map<std::string, std::unique_ptr<Model>>* ModelFactory::getModels() const {
	return &this->m_models;
}

/*
const std::unordered_map<std::string, Model*> ModelFactory::getModels() const {
    std::unordered_map<std::string, Model*> models;
    for (const auto& pair : this->m_models) {
        models[pair.first] = pair.second.get();
    }

    return models;
}
*/

/*
const std::vector<Model*> ModelFactory::getModels() const {
	std::vector<Model*> models;
	for (const auto& pair : this->m_models) {
		models.push_back(pair.second.get());
	}

	return models;
}
*/

VBO* ModelFactory::createVBO(const std::string& t_name, const size_t t_size, const float* t_data) {
	auto vbo = std::make_unique<VBO>(t_size, t_data);
	this->addVBO(t_name, std::move(vbo));

	return this->getVBO(t_name);
}

VBO* ModelFactory::createVBO(const std::string& t_name, const std::vector<float>& t_data) {
    return this->createVBO(t_name, t_data.size() * sizeof(float), t_data.data());
    /*
    auto vbo = std::make_unique<VBO>(t_data);
    this->addVBO(t_name, std::move(vbo));

    return this->getVBO(t_name);
    */
}

VAO* ModelFactory::createVAO(const std::string& t_name, const VBO& t_vbo, const std::vector<VAO::BufferInfo>& t_bufferInfoList) {
    auto vao = std::make_unique<VAO>();
    vao->addBuffer(t_vbo, t_bufferInfoList);
    this->addVAO(t_name, std::move(vao));

    return this->getVAO(t_name);
}

VAO* ModelFactory::createVAO(const std::string& t_name, const std::string& t_vboName, const std::vector<VAO::BufferInfo>& t_bufferInfoList) {
	return this->createVAO(t_name, *this->getVBO(t_vboName), t_bufferInfoList);
	/*
	auto vao = std::make_unique<VAO>();
	vao->addBuffer(*this->getVBO(t_vboName), t_bufferInfoList);
	this->addVAO(t_name, std::move(vao));

	return this->getVAO(t_name);
	*/
}

VAO* ModelFactory::createVertexResources(const std::string& t_name, const size_t t_size, const float* t_data, const std::vector<VAO::BufferInfo>& t_bufferInfoList) {
	auto vbo = this->createVBO(t_name, t_size, t_data);
	auto vao = this->createVAO(t_name, *vbo, t_bufferInfoList);
    //auto vao = this->createVAO(t_name, *this->getVBO(t_name), t_bufferInfoList);

	return this->getVAO(t_name);
}

VAO* ModelFactory::createVertexResources(const std::string& t_name, const std::vector<float>& t_data, const std::vector<VAO::BufferInfo>& t_bufferInfoList) {
    return this->createVertexResources(t_name, t_data.size() * sizeof(float), t_data.data(), t_bufferInfoList);
    /*
    auto vbo = this->createVBO(t_name, t_data);
    auto vao = this->createVAO(t_name, *vbo, t_bufferInfoList);
    //auto vao = this->createVAO(t_name, *this->getVBO(t_name), t_bufferInfoList);

    return this->getVAO(t_name);
    */
}

/*
Model* ModelFactory::createModel(
    const std::string& t_name,
    const std::string& t_shaderProgramName,
    const std::string& t_vaoName,
    const GLint t_first, const GLsizei t_count)
{
    // shader program + vertex resources (vbo & vao) = model
    auto shaderProgram = this->m_shaderFactory->getShaderProgram(t_shaderProgramName);
    auto vao = this->getVAO(t_vaoName);

    auto model = std::make_unique<Model>(shaderProgram, vao, t_first, t_count);
    this->addModel(t_name, std::move(model));

    return this->getModel(t_name);
}

Model* ModelFactory::createModel(
	const std::string& t_name,
	const std::string& t_shaderProgramName,
	const size_t t_vboSize, const float* t_vboData, const std::vector<VAO::BufferInfo>& t_bufferInfoList,
	const GLint t_first, const GLsizei t_count)
{
	// create vertex resources (vbo & vao)
	auto vao = this->createVertexResources(t_name, t_vboSize, t_vboData, t_bufferInfoList);

	return this->createModel(
		t_name,
		t_shaderProgramName,
		t_name, // vao name
		t_first, t_count);
}

Model* ModelFactory::createModel(
    const std::string& t_name,
    const std::string& t_shaderProgramName,
    const std::vector<float>& t_vboData, const std::vector<VAO::BufferInfo>& t_bufferInfoList,
    const GLint t_first, const GLsizei t_count)
{
    return this->createModel(
        t_name,
        t_shaderProgramName,
        t_vboData.size() * sizeof(float), t_vboData.data(), t_bufferInfoList,
        t_first, t_count);
    / *
	// create vertex resources (vbo & vao)
	auto vao = this->createVertexResources(t_name, t_vboData, t_bufferInfoList);

	return this->createModel(
		t_name,
		t_shaderProgramName,
		t_name, // vao name
		t_first, t_count);
    * /
}
*/

Model* ModelFactory::createModel(
    const std::string& t_name,
    const std::string& t_shaderProgramName,
    const std::string& t_vaoName,
    const GLint t_first, const GLsizei t_count,
    const glm::vec3& t_scale,
    const glm::vec3& t_rotation,
    const glm::vec3& t_position)
{
    /*
    auto model = this->createModel(
        t_name,
        t_shaderProgramName,
        t_vaoName,
        t_first, t_count);
    model->getTransformation()->setTranslation(t_position); //->addStep(std::make_shared<TransformationStepTranslate>(t_position));
    model->getTransformation()->setRotationEulerAngles(t_rotation); //->addStep(std::make_shared<TransformationStepRotate>(t_rotation));
    model->getTransformation()->setScale(t_scale); //->addStep(std::make_shared<TransformationStepScale>(t_scale));

    return model;
    */
    // shader program + vertex resources (vbo & vao) = model
    auto shaderProgram = this->m_shaderFactory->getShaderProgram(t_shaderProgramName);
    auto vao = this->getVAO(t_vaoName);

    auto model = std::make_unique<Model>(shaderProgram, vao, t_first, t_count);
    model->getTransformation()->setTranslation(t_position); //->addStep(std::make_shared<TransformationStepTranslate>(t_position));
    model->getTransformation()->setRotationEulerAngles(t_rotation); //->addStep(std::make_shared<TransformationStepRotate>(t_rotation));
    model->getTransformation()->setScale(t_scale); //->addStep(std::make_shared<TransformationStepScale>(t_scale));
    this->addModel(t_name, std::move(model));

    return this->getModel(t_name);
}

Model* ModelFactory::createModel(
	const std::string& t_name,
	const std::string& t_shaderProgramName,
	const size_t t_vboSize, const float* t_vboData, const std::vector<VAO::BufferInfo>& t_bufferInfoList,
	const GLint t_first, const GLsizei t_count,
    const glm::vec3& t_scale,
    const glm::vec3& t_rotation,
    const glm::vec3& t_position)
{
	// create vertex resources (vbo & vao)
	auto vao = this->createVertexResources(t_name, t_vboSize, t_vboData, t_bufferInfoList);

	return this->createModel(
		t_name,
		t_shaderProgramName,
		t_name, // vao name
		t_first, t_count,
        t_scale, t_rotation, t_position);
}

Model* ModelFactory::createModel(
    const std::string& t_name,
    const std::string& t_shaderProgramName,
    const std::vector<float>& t_vboData, const std::vector<VAO::BufferInfo>& t_bufferInfoList,
    const GLint t_first, const GLsizei t_count,
    const glm::vec3& t_scale,
    const glm::vec3& t_rotation,
    const glm::vec3& t_position)
{
    return this->createModel(
        t_name,
        t_shaderProgramName,
        t_vboData.size() * sizeof(float), t_vboData.data(), t_bufferInfoList,
        t_first, t_count,
        t_scale, t_rotation, t_position);
    /*
    // create vertex resources (vbo & vao)
    auto vao = this->createVertexResources(t_name, t_vboData, t_bufferInfoList);

    return this->createModel(
        t_name,
        t_shaderProgramName,
        t_name, // vao name
        t_first, t_count,
        t_scale, t_rotation, t_position);
    */
}
