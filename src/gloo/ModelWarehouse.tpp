#include "ModelWarehouse.h"
#include "ShaderWarehouse.h"

// === templates implementation ================================================
// --- public ------------------------------------------------------------------
template <typename T, typename>
T* ModelWarehouse::getModel(const std::string& t_name) const {
	auto it = this->m_models.find(t_name);

	return (it != this->m_models.end()) ? dynamic_cast<T*>(it->second.get()) : nullptr;
}

template <typename T, typename>
T* ModelWarehouse::createModel(
	const std::string& t_name,
	const std::string& t_shaderProgramName,
	const std::string& t_vaoName, const std::string& t_iboName,
	const GLint t_first, const GLsizei t_count,
	const glm::vec3& t_scale,
	const glm::vec3& t_rotation,
	const glm::vec3& t_position)
{
	auto model = this->getModel<T>(t_name);
	if (model == nullptr) {
		// shader program + vertex resources (vbo & vao & ibo) = model
		auto shaderProgram = ShaderWarehouse::getInstance()->getShaderProgram(t_shaderProgramName);
		auto vao = this->getVAO(t_vaoName);
		auto ibo = this->getIBO(t_iboName);

		this->addModel(t_name, this->m_modelFactory->createModel<T>(t_name, shaderProgram, vao, ibo, t_first, t_count, t_scale, t_rotation, t_position));

		model = this->getModel<T>(t_name);
	}

	return model;
}

template <typename T, typename>
T* ModelWarehouse::createModel(
	const std::string& t_name,
	const std::string& t_shaderProgramName,
	const std::string& t_vaoName,
	const GLint t_first, const GLsizei t_count,
	const glm::vec3& t_scale,
	const glm::vec3& t_rotation,
	const glm::vec3& t_position)
{
	auto model = this->getModel<T>(t_name);
	if (model == nullptr) {
		// shader program + vertex resources (vbo & vao) = model
		auto shaderProgram = ShaderWarehouse::getInstance()->getShaderProgram(t_shaderProgramName);
		auto vao = this->getVAO(t_vaoName);

		this->addModel(t_name, this->m_modelFactory->createModel<T>(t_name, shaderProgram, vao, t_first, t_count, t_scale, t_rotation, t_position));

		model = this->getModel<T>(t_name);
	}

	return model;
}

template <typename T, typename>
T* ModelWarehouse::createModel(
	const std::string& t_name,
	const std::string& t_shaderProgramName,
	const size_t t_vboSize, const float* t_vboData, const std::vector<VAO::bufferInfoT>& t_bufferInfoList,
	const GLint t_first, const GLsizei t_count,
	const glm::vec3& t_scale,
	const glm::vec3& t_rotation,
	const glm::vec3& t_position)
{
	// create vertex resources (vbo & vao)
	auto vao = this->createVertexResources(t_name, t_vboSize, t_vboData, t_bufferInfoList);

	return this->createModel<T>(
		t_name,
		t_shaderProgramName,
		t_name, // that's vao name too now
		t_first, t_count,
		t_scale, t_rotation, t_position);
}

template <typename T, typename>
T* ModelWarehouse::createModel(
	const std::string& t_name,
	const std::string& t_shaderProgramName,
	const std::vector<float>& t_vboData, const std::vector<VAO::bufferInfoT>& t_bufferInfoList,
	const GLint t_first, const GLsizei t_count,
	const glm::vec3& t_scale,
	const glm::vec3& t_rotation,
	const glm::vec3& t_position)
{
	return this->createModel<T>(
		t_name,
		t_shaderProgramName,
		t_vboData.size() * sizeof(float), t_vboData.data(), t_bufferInfoList,
		t_first, t_count,
		t_scale, t_rotation, t_position);
	/*
	// create vertex resources (vbo & vao)
	auto vao = this->createVertexResources(t_name, t_vboData, t_bufferInfoList);

	return this->createModel<T>(
		t_name,
		t_shaderProgramName,
		t_name, // that's vao name too now
		t_first, t_count,
		t_scale, t_rotation, t_position);
	*/
}
