#include "ModelFactory.h"
#include "ShaderWarehouse.h"
#include "TransformationStepTranslate.h"
#include "TransformationStepRotate.h"
#include "TransformationStepScale.h"

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
const VAO::bufferInfoT ModelFactory::BUFFERINFO3_POSITION  = { 0, 3, 0, nullptr };

const VAO::bufferInfoT ModelFactory::BUFFERINFO6_POSITION  = { 0, 3, 6 * sizeof(float), (GLvoid*)0 };
const VAO::bufferInfoT ModelFactory::BUFFERINFO6_COLOR     = { 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)) };
const VAO::bufferInfoT ModelFactory::BUFFERINFO6_NORMAL    = { 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)) };

const VAO::bufferInfoT ModelFactory::BUFFERINFO8_POSITION  = { 0, 3, 8 * sizeof(float), (GLvoid*)0 };
const VAO::bufferInfoT ModelFactory::BUFFERINFO8_NORMAL    = { 1, 3, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)) };
const VAO::bufferInfoT ModelFactory::BUFFERINFO8_TEXTUREUV = { 2, 2, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)) };

const std::vector<VAO::bufferInfoT> ModelFactory::BUFFERINFOLIST_POSITION = {
	ModelFactory::BUFFERINFO3_POSITION };
const std::vector<VAO::bufferInfoT> ModelFactory::BUFFERINFOLIST_POSITION_COLOR = {
    ModelFactory::BUFFERINFO6_POSITION,
    ModelFactory::BUFFERINFO6_COLOR };
const std::vector<VAO::bufferInfoT> ModelFactory::BUFFERINFOLIST_POSITION_NORMAL = {
    ModelFactory::BUFFERINFO6_POSITION,
    ModelFactory::BUFFERINFO6_NORMAL };
const std::vector<VAO::bufferInfoT> ModelFactory::BUFFERINFOLIST_POSITION_NORMAL_TEXTURE = {
	ModelFactory::BUFFERINFO8_POSITION,
	ModelFactory::BUFFERINFO8_NORMAL,
	ModelFactory::BUFFERINFO8_TEXTUREUV };
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
std::unique_ptr<VBO> ModelFactory::createVBO(const size_t t_size, const float* t_data) {
	return std::make_unique<VBO>(t_size, t_data);
}

std::unique_ptr<VBO> ModelFactory::createVBO(const std::vector<float>& t_data) {
	//return this->createVBO(t_data.size() * sizeof(float), t_data.data());
	return std::make_unique<VBO>(t_data);
}

std::unique_ptr<VAO> ModelFactory::createVAO(const VBO& t_vbo, const std::vector<VAO::bufferInfoT>& t_bufferInfoList) {
	auto vao = std::make_unique<VAO>();
	vao->addBuffer(t_vbo, t_bufferInfoList);

    return vao;
}

std::unique_ptr<IBO> ModelFactory::createIBO(const size_t t_size, const unsigned int* t_data) {
	return std::make_unique<IBO>(t_size, t_data);
}

std::unique_ptr<IBO> ModelFactory::createIBO(const std::vector<unsigned int>& t_data) {
	//return this->createIBO(t_data.size() * sizeof(unsigned int), t_data.data());
	return std::make_unique<IBO>(t_data);
}
