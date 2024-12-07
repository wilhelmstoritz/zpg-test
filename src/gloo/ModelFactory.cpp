#include "ModelFactory.h"
#include "ShaderWarehouse.h"
#include "TransformationStepTranslate.h"
#include "TransformationStepRotate.h"
#include "TransformationStepScale.h"

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
const VAO::BufferInfo ModelFactory::BUFFERINFO_DEFAULT = { 0, 3, 0, nullptr };
const VAO::BufferInfo ModelFactory::BUFFERINFO_POSITION = { 0, 3, 6 * sizeof(float), (GLvoid*)0 };
const VAO::BufferInfo ModelFactory::BUFFERINFO_COLOR = { 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)) };
const VAO::BufferInfo ModelFactory::BUFFERINFO_NORMAL = { 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)) };

const std::vector<VAO::BufferInfo> ModelFactory::BUFFERINFOLIST_DEFAULT = { ModelFactory::BUFFERINFO_DEFAULT };
const std::vector<VAO::BufferInfo> ModelFactory::BUFFERINFOLIST_POSITION_COLOR = {
    ModelFactory::BUFFERINFO_POSITION,
    ModelFactory::BUFFERINFO_COLOR };
const std::vector<VAO::BufferInfo> ModelFactory::BUFFERINFOLIST_POSITION_NORMAL = {
    ModelFactory::BUFFERINFO_POSITION,
    ModelFactory::BUFFERINFO_NORMAL };
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
