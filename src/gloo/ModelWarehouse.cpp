#include "ModelWarehouse.h"

// assimp; open asset import library
#include<assimp/Importer.hpp> // c++ importer interface
#include<assimp/scene.h> // aiSceneoutputdata structure
#include<assimp/postprocess.h> // postprocessing flags

// - - static class properties - - - - - - - - - - - - - - - - - - - - - - - - -
// initialization of static class members
//ModelWarehouse* ModelWarehouse::_instance = nullptr;
std::unique_ptr<ModelWarehouse> ModelWarehouse::_instance = nullptr;
std::mutex ModelWarehouse::_mtx;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// --- public ------------------------------------------------------------------
ModelWarehouse* ModelWarehouse::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr)
		//_instance = new ModelWarehouse();
		_instance.reset(new ModelWarehouse());

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

void ModelWarehouse::addIBO(const std::string& t_name, std::unique_ptr<IBO> t_ibo) {
	this->m_ibos[t_name] = std::move(t_ibo);
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

void ModelWarehouse::removeIBO(const std::string& t_name) {
	this->m_ibos.erase(t_name);
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

VAO* ModelWarehouse::createVAO(const std::string& t_name, const VBO& t_vbo, const std::vector<VAO::bufferInfoT>& t_bufferInfoList) {
	auto vao = this->getVAO(t_name);
	if (vao == nullptr) {
		this->addVAO(t_name, this->m_modelFactory->createVAO(t_vbo, t_bufferInfoList));

		vao = this->getVAO(t_name);
	}

	return vao;
}

VAO* ModelWarehouse::createVAO(const std::string& t_name, const std::string& t_vboName, const std::vector<VAO::bufferInfoT>& t_bufferInfoList) {
	return this->createVAO(t_name, *this->getVBO(t_vboName), t_bufferInfoList);
}

IBO* ModelWarehouse::getIBO(const std::string& t_name) const {
	auto it = this->m_ibos.find(t_name);

	return (it != this->m_ibos.end()) ? it->second.get() : nullptr;
}

IBO* ModelWarehouse::createIBO(const std::string& t_name, const size_t t_size, const unsigned int* t_data) {
	auto ibo = this->getIBO(t_name);
	if (ibo == nullptr) {
		this->addIBO(t_name, this->m_modelFactory->createIBO(t_size, t_data));

		ibo = this->getIBO(t_name);
	}

	return ibo;
}

IBO* ModelWarehouse::createIBO(const std::string& t_name, const std::vector<unsigned int>& t_data) {
	return this->createIBO(t_name, t_data.size() * sizeof(unsigned int), t_data.data());
	/*
	auto ibo = this->getIBO(t_name);
	if (ibo == nullptr) {
		this->addIBO(t_name, this->m_modelFactory->createIBO(t_data));

		ibo = this->getIBO(t_name);
	}

	return ibo;
	*/
}

VAO* ModelWarehouse::createVertexResources(const std::string& t_name, const size_t t_size, const float* t_data, const std::vector<VAO::bufferInfoT>& t_bufferInfoList) {
	auto vao = this->getVAO(t_name);
	if (vao == nullptr) {
		auto vbo = this->createVBO(t_name, t_size, t_data);
		vao = this->createVAO(t_name, *vbo, t_bufferInfoList);
	}

	return vao;
}

VAO* ModelWarehouse::createVertexResources(const std::string& t_name, const std::vector<float>& t_data, const std::vector<VAO::bufferInfoT>& t_bufferInfoList) {
	return this->createVertexResources(t_name, t_data.size() * sizeof(float), t_data.data(), t_bufferInfoList);
	/*
	auto vao = this->getVAO(t_name);
	if (vao == nullptr) {
		auto vbo = this->createVBO(t_name, t_data);
		vao = this->createVAO(t_name, *vbo, t_bufferInfoList);
	}

	return vao;
	*/
}

std::vector<GLsizei> ModelWarehouse::createBufferResources(const std::string& t_name, const std::string& t_objFilename) {
	//std::vector<VAO*> vaos;
	std::vector<GLsizei> numVerticesList;

	/*auto vao = this->getVAO(t_name + std::to_string(0)); // look for the first vao/face; if it exists, then all vaos/faces exist; no need to load and parse the obj file again
	if (vao != nullptr) {
		numVerticesList = this->m_numVerticesLists[t_name]; // at this point, number of vertices list must exist already
		... rest of the code
	}*/
	auto it = this->m_numVerticesLists.find(t_name); // look for number of vertices list; if it exists, no need to load and parse the obj file again
	if (it != this->m_numVerticesLists.end()) {
		//printf("[model warehouse] info : vertex resources '%s' already exist; returning previously created vaos/faces\n", t_name.c_str());

		numVerticesList = it->second;

		return numVerticesList;
	}

	Assimp::Importer importer;
	unsigned int importOptions =
		aiProcess_Triangulate           | // converts polygons to triangles
		aiProcess_OptimizeMeshes        | // reduces the number of submeshes
		//aiProcess_JoinIdenticalVertices | // removes duplicate vertices
		aiProcess_CalcTangentSpace      | // computes tangents and bitangents
		//aiProcess_GenNormals            | // generates flat normals
		aiProcess_GenSmoothNormals        // generates smooth normals
		;

	const aiScene* scene = importer.ReadFile(t_objFilename, importOptions);

	if (scene) { // in case the loading was successful
		//printf("[model warehouse] info : scene mNumMeshes = %d\n", scene->mNumMeshes);
		//printf("[model warehouse] info : scene mNumMaterials = %d\n", scene->mNumMaterials);

		// materials
		for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
			const aiMaterial* mat = scene->mMaterials[i];

			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			//printf("[model warehouse] info : material [%d] name %s\n", i, name.C_Str());

			glm::vec4 diffuse = glm::vec4(.8f, .8f, .8f, 1.f);
			aiColor4D d;
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				diffuse = glm::vec4(d.r, d.g, d.b, d.a);
		}

		// objects
		for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
			auto vao = this->getVAO(t_name + std::to_string(i));
			if (vao == nullptr) {
				aiMesh* mesh = scene->mMeshes[i];
				vertexT* pVertices = new vertexT[mesh->mNumVertices];
				std::memset(pVertices, 0, sizeof(vertexT) * mesh->mNumVertices);

				for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
					// position
					if (mesh->HasPositions()) {
						pVertices[i].position.x = mesh->mVertices[i].x;
						pVertices[i].position.y = mesh->mVertices[i].y;
						pVertices[i].position.z = mesh->mVertices[i].z;
					}

					// normal
					if (mesh->HasNormals()) {
						pVertices[i].normal.x = mesh->mNormals[i].x;
						pVertices[i].normal.y = mesh->mNormals[i].y;
						pVertices[i].normal.z = mesh->mNormals[i].z;
					}

					// texture coords
					if (mesh->HasTextureCoords(0)) {
						pVertices[i].texture.x = mesh->mTextureCoords[0][i].x;
						pVertices[i].texture.y = mesh->mTextureCoords[0][i].y;
					}

					// tangent
					if (mesh->HasTangentsAndBitangents()) {
						pVertices[i].tangent.x = mesh->mTangents[i].x;
						pVertices[i].tangent.y = mesh->mTangents[i].y;
						pVertices[i].tangent.z = mesh->mTangents[i].z;
					}
				}

				// faces
				unsigned int* pIndices = nullptr;
				if (mesh->HasFaces()) {
					pIndices = new unsigned int[mesh->mNumFaces * 3];
					for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
						pIndices[i * 3]     = mesh->mFaces[i].mIndices[0];
						pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
						pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
					}
				}

				// create vertex resources; vbo & vao
				auto vbo = this->createVBO(t_name + std::to_string(i), sizeof(vertexT) * mesh->mNumVertices, (float*)pVertices);
				vao = this->createVAO(t_name + std::to_string(i), *vbo, { // bufferInfoList
					{ 0, 3, sizeof(vertexT), (GLvoid*)offsetof(vertexT, position) },
					{ 1, 3, sizeof(vertexT), (GLvoid*)offsetof(vertexT, normal) },
					{ 2, 2, sizeof(vertexT), (GLvoid*)offsetof(vertexT, texture) },
					{ 3, 3, sizeof(vertexT), (GLvoid*)offsetof(vertexT, tangent) } }); // tangent for normal map

				// create index buffer
				auto ibo = this->createIBO(t_name + std::to_string(i), sizeof(GLuint) * mesh->mNumFaces * 3, pIndices);

				//vao->bind();

				// cleanup
				GLuint err = glGetError();
				if (err != GL_NO_ERROR)
					fprintf(stderr, "error >> gl error: %d\n", err);

				GLsizei numVertices = mesh->mNumFaces * 3;
				numVerticesList.push_back(numVertices);

				delete[] pVertices;
				delete[] pIndices;
			}

			//vaos.push_back(vao);
		}
	} else {
		//throw std::runtime_error("error >> while parsing mesh : obj filename " + t_objFilename + "; " + importer.GetErrorString());
		fprintf(stderr, "error >> while parsing mesh : obj filename %s; %s\n", t_objFilename.c_str(), importer.GetErrorString());

		exit(EXIT_FAILURE);
	}

	this->m_numVerticesLists[t_name] = numVerticesList;

	//return vaos;
	return numVerticesList;
}

const std::unordered_map<std::string, std::unique_ptr<Model>>* ModelWarehouse::getModels() const {
	return &this->m_models;
}

// --- private -----------------------------------------------------------------
ModelWarehouse::ModelWarehouse() {
	this->m_modelFactory = new ModelFactory();
}
