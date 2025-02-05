#pragma once

#include "VBO.h"
#include "VAO.h"
#include "IBO.h"
#include "Model.h"
#include "ModelFactory.h"

// standard c++ libraries
#include <mutex>
#include <memory>
#include <unordered_map>

class ModelWarehouse {
public:
	static ModelWarehouse* getInstance();
	~ModelWarehouse();

	void clearAll();

	/* likely to become private after the end of development/debugging */
	void addVBO(const std::string& t_name, std::unique_ptr<VBO> t_vbo);
	void addVAO(const std::string& t_name, std::unique_ptr<VAO> t_vao);
	void addIBO(const std::string& t_name, std::unique_ptr<IBO> t_ibo);
	void addModel(const std::string& t_name, std::unique_ptr<Model> t_model);
	/* likely to become private after the end of development/debugging */

	void removeVBO(const std::string& t_name);
	void removeVAO(const std::string& t_name);
	void removeIBO(const std::string& t_name);
	void removeModel(const std::string& t_name);

	VBO* getVBO(const std::string& t_name) const;
	VBO* createVBO(const std::string& t_name, const size_t t_size, const float* t_data);
	VBO* createVBO(const std::string& t_name, const std::vector<float>& t_data);

	VAO* getVAO(const std::string& t_name) const;
	VAO* createVAO(const std::string& t_name, const VBO& t_vbo, const std::vector<VAO::bufferInfoT>& t_bufferInfoList);
	VAO* createVAO(const std::string& t_name, const std::string& t_vboName, const std::vector<VAO::bufferInfoT>& t_bufferInfoList);

	IBO* getIBO(const std::string& t_name) const;
	IBO* createIBO(const std::string& t_name, const size_t t_size, const unsigned int* t_data);
	IBO* createIBO(const std::string& t_name, const std::vector<unsigned int>& t_data);

	VAO* createVertexResources(const std::string& t_name, const size_t t_size, const float* t_data, const std::vector<VAO::bufferInfoT>& t_bufferInfoList);
	VAO* createVertexResources(const std::string& t_name, const std::vector<float>& t_data, const std::vector<VAO::bufferInfoT>& t_bufferInfoList);
	std::vector<GLsizei> createBufferResources(const std::string& t_name, const std::string& t_objFilename); // for .obj loaded data only; VAOs and IBOs are created here

	template <typename T = Model, typename = typename std::enable_if<std::is_base_of<Model, T>::value>::type>
	T* getModel(const std::string& t_name) const;
	template <typename T = Model, typename = typename std::enable_if<std::is_base_of<Model, T>::value>::type>
	T* createModel(
		const std::string& t_name,
		const std::string& t_shaderProgramName,
		const std::string& t_vaoName, const std::string& t_iboName,
		const GLint t_first, const GLsizei t_count,
		const glm::vec3& t_scale = glm::vec3(1.0f),
		const glm::vec3& t_rotation = glm::vec3(0.0f),
		const glm::vec3& t_position = glm::vec3(0.0f));
	template <typename T = Model, typename = typename std::enable_if<std::is_base_of<Model, T>::value>::type>
	T* createModel(
		const std::string& t_name,
		const std::string& t_shaderProgramName,
		const std::string& t_vaoName,
		const GLint t_first, const GLsizei t_count,
		const glm::vec3& t_scale = glm::vec3(1.0f),
		const glm::vec3& t_rotation = glm::vec3(0.0f),
		const glm::vec3& t_position = glm::vec3(0.0f));
	template <typename T = Model, typename = typename std::enable_if<std::is_base_of<Model, T>::value>::type>
	T* createModel(
		const std::string& t_name,
		const std::string& t_shaderProgramName,
		const size_t t_vboSize, const float* t_vboData, const std::vector<VAO::bufferInfoT>& t_bufferInfoList,
		const GLint t_first, const GLsizei t_count,
		const glm::vec3& t_scale = glm::vec3(1.0f),
		const glm::vec3& t_rotation = glm::vec3(0.0f),
		const glm::vec3& t_position = glm::vec3(0.0f));
	template <typename T = Model, typename = typename std::enable_if<std::is_base_of<Model, T>::value>::type>
	T* createModel(
		const std::string& t_name,
		const std::string& t_shaderProgramName,
		const std::vector<float>& t_vboData, const std::vector<VAO::bufferInfoT>& t_bufferInfoList,
		const GLint t_first, const GLsizei t_count,
		const glm::vec3& t_scale = glm::vec3(1.0f),
		const glm::vec3& t_rotation = glm::vec3(0.0f),
		const glm::vec3& t_position = glm::vec3(0.0f));
	const std::unordered_map<std::string, std::unique_ptr<Model>>* getModels() const;

private:
	// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - -
	// private constructor to avoid creating multiple instances
	ModelWarehouse();

	// disable copy constructor and assignment operator
	ModelWarehouse(const ModelWarehouse&) = delete;
	ModelWarehouse& operator=(const ModelWarehouse&) = delete;

	// a singleton instance pointer
	//static ModelWarehouse* _instance;
	static std::unique_ptr<ModelWarehouse> _instance; // managed by smart pointer; this approach ensures that the singleton destructor is called correctly
	static std::mutex _mtx;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	struct vertexT {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture;
		glm::vec3 tangent;
	};

	std::unordered_map<std::string, std::unique_ptr<VBO>> m_vbos; // also retention for lifetime management
	std::unordered_map<std::string, std::unique_ptr<VAO>> m_vaos;
	std::unordered_map<std::string, std::unique_ptr<IBO>> m_ibos;
	std::unordered_map<std::string, std::unique_ptr<Model>> m_models;

	std::unordered_map<std::string, std::vector<GLsizei>> m_numVerticesLists; // number of vertices per face lists; vertex resources for .obj loaded vertices only

	ModelFactory* m_modelFactory;
};

// === templates implementation ================================================
#include "ModelWarehouse.tpp"
