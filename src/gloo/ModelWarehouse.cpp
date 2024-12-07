#include "ModelWarehouse.h"

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//ModelWarehouse* ModelWarehouse::_instance = nullptr;
std::unique_ptr<ModelWarehouse> ModelWarehouse::_instance = nullptr;
std::mutex ModelWarehouse::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
ModelWarehouse* ModelWarehouse::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr) {
		//_instance = new ModelWarehouse();
		_instance.reset(new ModelWarehouse());
	}

	//return _instance;
	return _instance.get();
}

ModelWarehouse::~ModelWarehouse() {
	// cleanup
	delete this->m_modelFactory;
}

void ModelWarehouse::clearAll() {
	this->m_models.clear();
	this->m_vaos.clear();
	this->m_vbos.clear();
}

void ModelWarehouse::addVBO(const std::string& t_name, std::unique_ptr<VBO> t_vbo) {
	this->m_vbos[t_name] = std::move(t_vbo);
}

void ModelWarehouse::addVAO(const std::string& t_name, std::unique_ptr<VAO> t_vao) {
	this->m_vaos[t_name] = std::move(t_vao);
}

void ModelWarehouse::addModel(const std::string& t_name, std::unique_ptr<Model> t_model) {
	this->m_models[t_name] = std::move(t_model);
}

void ModelWarehouse::removeVBO(const std::string& t_name) {
	this->m_vbos.erase(t_name);
}

void ModelWarehouse::removeVAO(const std::string& t_name) {
	this->m_vaos.erase(t_name);
}

void ModelWarehouse::removeModel(const std::string& t_name) {
	this->m_models.erase(t_name);
}

VBO* ModelWarehouse::getVBO(const std::string& t_name) const {
	auto it = this->m_vbos.find(t_name);

	return (it != this->m_vbos.end()) ? it->second.get() : nullptr;
}

VBO* ModelWarehouse::createVBO(const std::string& t_name, const size_t t_size, const float* t_data) {
	auto vbo = this->getVBO(t_name);
	if (vbo == nullptr) {
		this->addVBO(t_name, this->m_modelFactory->createVBO(t_size, t_data));
		vbo = this->getVBO(t_name);
	}

	return vbo;
}

VBO* ModelWarehouse::createVBO(const std::string& t_name, const std::vector<float>& t_data) {
	return this->createVBO(t_name, t_data.size() * sizeof(float), t_data.data());
	/*
	auto vbo = this->getVBO(t_name);
	if (vbo == nullptr) {
		this->addVBO(t_name, this->m_modelFactory->createVBO(t_data));
		vbo = this->getVBO(t_name);
	}

	return vbo;
	*/
}

VAO* ModelWarehouse::getVAO(const std::string& t_name) const {
	auto it = this->m_vaos.find(t_name);

	return (it != this->m_vaos.end()) ? it->second.get() : nullptr;
}

VAO* ModelWarehouse::createVAO(const std::string& t_name, const VBO& t_vbo, const std::vector<VAO::BufferInfo>& t_bufferInfoList) {
	auto vao = this->getVAO(t_name);
	if (vao == nullptr) {
		this->addVAO(t_name, this->m_modelFactory->createVAO(t_vbo, t_bufferInfoList));
		vao = this->getVAO(t_name);
	}

	return vao;
}

VAO* ModelWarehouse::createVAO(const std::string& t_name, const std::string& t_vboName, const std::vector<VAO::BufferInfo>& t_bufferInfoList) {
	return this->createVAO(t_name, *this->getVBO(t_vboName), t_bufferInfoList);
}

VAO* ModelWarehouse::createVertexResources(const std::string& t_name, const size_t t_size, const float* t_data, const std::vector<VAO::BufferInfo>& t_bufferInfoList) {
	auto vao = this->getVAO(t_name);
	if (vao == nullptr) {
		auto vbo = this->createVBO(t_name, t_size, t_data);
		vao = this->createVAO(t_name, *vbo, t_bufferInfoList);

		vao = this->getVAO(t_name);
	}

	return vao;
}

VAO* ModelWarehouse::createVertexResources(const std::string& t_name, const std::vector<float>& t_data, const std::vector<VAO::BufferInfo>& t_bufferInfoList) {
	return this->createVertexResources(t_name, t_data.size() * sizeof(float), t_data.data(), t_bufferInfoList);
	/*
	auto vao = this->getVAO(t_name);
	if (vao == nullptr) {
		auto vbo = this->createVBO(t_name, t_data);
		vao = this->createVAO(t_name, *vbo, t_bufferInfoList);

		vao = this->getVAO(t_name);
	}

	return vao;
	*/
}

Model* ModelWarehouse::getModel(const std::string& t_name) const {
	auto it = this->m_models.find(t_name);

	return (it != this->m_models.end()) ? it->second.get() : nullptr;
}

const std::unordered_map<std::string, std::unique_ptr<Model>>* ModelWarehouse::getModels() const {
	return &this->m_models;
}

// --- private -----------------------------------------------------------------
ModelWarehouse::ModelWarehouse() {
	this->m_modelFactory = new ModelFactory();
}
