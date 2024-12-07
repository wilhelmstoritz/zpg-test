#include "ModelFactory.h"
#include "ShaderWarehouse.h"
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
std::unique_ptr<VBO> ModelFactory::createVBO(const size_t t_size, const float* t_data) {
	return std::make_unique<VBO>(t_size, t_data);
}

std::unique_ptr<VBO> ModelFactory::createVBO(const std::vector<float>& t_data) {
	//return this->createVBO(t_data.size() * sizeof(float), t_data.data());
	return std::make_unique<VBO>(t_data);
}

std::unique_ptr<VAO> ModelFactory::createVAO(const VBO& t_vbo, const std::vector<VAO::BufferInfo>& t_bufferInfoList) {
	auto vao = std::make_unique<VAO>();
	vao->addBuffer(t_vbo, t_bufferInfoList);

    return vao;
}

std::unique_ptr<Model> ModelFactory::createModel(
	ShaderProgram* t_shaderProgram,
	VAO* t_vao,
	const GLint t_first, const GLsizei t_count,
	const glm::vec3& t_scale,
	const glm::vec3& t_rotation,
	const glm::vec3& t_position)
{
    // shader program + vertex resources (vbo & vao) = model
	auto model = std::make_unique<Model>(t_shaderProgram, t_vao, t_first, t_count);
	model->getTransformation()->setTranslation(t_position);
	model->getTransformation()->setRotationEulerAngles(t_rotation);
	model->getTransformation()->setScale(t_scale);

    return model;
}
