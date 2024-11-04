#include "ModelVault.h"
#include "data.h"

#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// include the standard C++ headers
#include <format>

// initialization of static class members
//ModelVault* ModelVault::_instance = nullptr;
std::unique_ptr<ModelVault> ModelVault::_instance = nullptr;
std::mutex ModelVault::_mtx;

// --- public ------------------------------------------------------------------
ModelVault* ModelVault::getInstance() {
	std::lock_guard<std::mutex> lock(_mtx);
	if (_instance == nullptr) {
		//_instance = new ModelVault();
		_instance.reset(new ModelVault());
	}

	//return _instance;
	return _instance.get();
}

void ModelVault::addShader(const std::string t_name, Shader* t_shader) { this->m_shaders[t_name] = t_shader; }
void ModelVault::addShaderProgram(const std::string t_name, ShaderProgram* t_shaderProgram) { this->m_shaderPrograms[t_name] = t_shaderProgram; }
void ModelVault::addVBO(const std::string t_name, VBO* t_vbo) { this->m_vbos[t_name] = t_vbo; }
void ModelVault::addVAO(const std::string t_name, VAO* t_vao) { this->m_vaos[t_name] = t_vao; }
void ModelVault::addModel(Model* t_model) { this->m_models.push_back(t_model); }
void ModelVault::addModel(ShaderProgram* t_shaderProgram, VAO* t_vao, GLint t_first, GLsizei t_count) {
	this->m_models.push_back(new Model(t_shaderProgram, t_vao, t_first, t_count));
}

Shader* ModelVault::getShader(const std::string t_name) { return this->m_shaders[t_name]; }
ShaderProgram* ModelVault::getShaderProgram(const std::string t_name) { return this->m_shaderPrograms[t_name]; }
VBO* ModelVault::getVBO(const std::string t_name) { return this->m_vbos[t_name]; }
VAO* ModelVault::getVAO(const std::string t_name) { return this->m_vaos[t_name]; }
std::vector<Model*>* ModelVault::getModels(Camera* t_camera) {
	// set camera to shader program; register shader program observer(s) to camera subject
	this->getShaderProgram("transformingColorData")->update(t_camera);
	t_camera->getObserverSubject()->addObserver(this->getShaderProgram("transformingColorData"));

	return &this->m_models;
}

/*
void ModelVault::addVertexShader(const std::string t_name, const char* t_source) {
	Shader* shader = new VertexShader(t_source);
	//this->m_shaders[t_name] = shader;
	this->addShader(t_name, shader);
}

void ModelVault::addFragmentShader(const std::string t_name, const char* t_source) {
	Shader* shader = new FragmentShader(t_source);
	//this->m_shaders[t_name] = shader;
	this->addShader(t_name, shader);
}
*/

// --- private -----------------------------------------------------------------
ModelVault::ModelVault() {
	this->createShaders();
	this->createModels();
	this->createScene();
}

ModelVault::~ModelVault() {
	// cleanup
	for (const auto& item : this->m_models) delete(item);

	for (const auto& item : this->m_vaos) delete(item.second);
	for (const auto& item : this->m_vbos) delete(item.second);
	for (const auto& item : this->m_shaderPrograms) delete(item.second);
	for (const auto& item : this->m_shaders) delete(item.second);
}

void ModelVault::createShaders() {
	// vertex shaders
	// --- default
	VertexShader* tmpVertexShader = new VertexShader(DEFAULT_VERTEX_SHADER);
	this->addShader("v_default", tmpVertexShader);

	tmpVertexShader = new VertexShader(DEFAULT_VERTEX_SHADER_COLORFROMPOSITION);
	this->addShader("v_defaultColorFromPosition", tmpVertexShader);

	tmpVertexShader = new VertexShader(DEFAULT_VERTEX_SHADER_COLORDATA);
	this->addShader("v_defaultColorData", tmpVertexShader);

	// --- transforming
	tmpVertexShader = new VertexShader(TRANSFORMING_VERTEX_SHADER_COLORDATA);
	this->addShader("v_transformingColorData", tmpVertexShader);

	// fragment shaders
	// --- default
	FragmentShader* tmpFragmentShader = new FragmentShader(DEFAULT_FRAGMENT_SHADER);
	this->addShader("f_default", tmpFragmentShader);

	tmpFragmentShader = new FragmentShader(DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION);
	this->addShader("f_defaultColorFromPosition", tmpFragmentShader);

	tmpFragmentShader = new FragmentShader(DEFAULT_FRAGMENT_SHADER_COLORDATA);
	this->addShader("f_defaultColorData", tmpFragmentShader);

	tmpFragmentShader = new FragmentShader(YELLOW_FRAGMENT_SHADER);
	this->addShader("f_yellow", tmpFragmentShader);

	// --- transforming
	tmpFragmentShader = new FragmentShader(TRANSFORMING_FRAGMENT_SHADER_COLORDATA);
	this->addShader("f_transformingColorData", tmpFragmentShader);

	// shader programs
	// --- default
	ShaderProgram* tmpShaderProgram = new ShaderProgram(*this->getShader("v_default"), *this->getShader("f_default"));
	this->addShaderProgram("default", tmpShaderProgram);

	tmpShaderProgram = new ShaderProgram(*this->getShader("v_defaultColorFromPosition"), *this->getShader("f_defaultColorFromPosition"));
	this->addShaderProgram("defaultColorFromPosition", tmpShaderProgram);

	tmpShaderProgram = new ShaderProgram(*this->getShader("v_defaultColorData"), *this->getShader("f_defaultColorData"));
	this->addShaderProgram("defaultColorData", tmpShaderProgram);

	tmpShaderProgram = new ShaderProgram(*this->getShader("v_default"), *this->getShader("f_yellow"));
	this->addShaderProgram("yellow", tmpShaderProgram);

	// --- transforming
	tmpShaderProgram = new ShaderProgram(*this->getShader("v_transformingColorData"), *this->getShader("f_transformingColorData"));
	this->addShaderProgram("transformingColorData", tmpShaderProgram);
}

void ModelVault::createModels() {
	// --- 1st task models --------------------------------------------------------
	// VBOs
	VBO* tmpVBO = new VBO(TRIANGLE_POINTS);
	this->addVBO("triangle", tmpVBO);

	tmpVBO = new VBO(TRIANGLE_POINTS_COLORDATA);
	this->addVBO("triangleColorData", tmpVBO);

	tmpVBO = new VBO(SQUARE_POINTS);
	this->addVBO("square", tmpVBO);

	// VAOs
	VAO* tmpVAO = new VAO();
	tmpVAO->addBuffer(*this->getVBO("triangle"), 0, 3, 0, NULL);
	this->addVAO("triangle", tmpVAO);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*this->getVBO("triangleColorData"), 0, 3, 6 * sizeof(float), (void*)0);
	tmpVAO->addBuffer(*this->getVBO("triangleColorData"), 1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	this->addVAO("triangleColorData", tmpVAO);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*this->getVBO("square"), 0, 3, 0, NULL);
	this->addVAO("square", tmpVAO);

	// --- zpg models -------------------------------------------------------------
	// bushes
	tmpVBO = new VBO(sizeof(bushes), bushes);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgBushes", tmpVAO);

	// gift
	tmpVBO = new VBO(sizeof(gift), gift);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgGift", tmpVAO);

	// plain
	tmpVBO = new VBO(sizeof(plain), plain);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgPlain", tmpVAO);

	// sphere
	tmpVBO = new VBO(sizeof(sphere), sphere);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSphere", tmpVAO);

	// suziFlat
	tmpVBO = new VBO(sizeof(suziFlat), suziFlat);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSuziFlat", tmpVAO);

	// suziSmooth
	tmpVBO = new VBO(sizeof(suziSmooth), suziSmooth);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSuziSmooth", tmpVAO);

	// tree
	tmpVBO = new VBO(sizeof(tree), tree);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgTree", tmpVAO);

	// --- tmp models -------------------------------------------------------------
	float PENTAGON[] = {
		// 1st triangle
		 0.0f,     0.0f,    0.0f, // centre
		 1.0f,     0.0f,    0.0f, // apex #1
		 0.3090f,  0.9511f, 0.0f, // apex #2
		// 2nd triangle
		 0.0f,     0.0f,    0.0f, // centre
		 0.3090f,  0.9511f, 0.0f, // apex #2
		-0.8090f,  0.5878f, 0.0f, // apex #3
		// 3rd triangle
		 0.0f,     0.0f,    0.0f, // centre
		-0.8090f,  0.5878f, 0.0f, // apex #3
		-0.8090f, -0.5878f, 0.0f, // apex #4
		// 4th triangle
		 0.0f,     0.0f,    0.0f, // centre
		-0.8090f, -0.5878f, 0.0f, // apex #4
		 0.3090f, -0.9511f, 0.0f, // apex #5
		// 5th triangle
		 0.0f,     0.0f,    0.0f, // centre
		 0.3090f, -0.9511f, 0.0f, // apex #5
		 1.0f,     0.0f,    0.0f  // apex #1
	};

	tmpVBO = new VBO(sizeof(PENTAGON), PENTAGON);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 0, NULL);
	this->addVAO("pentagram", tmpVAO);
}

void ModelVault::createScene() {
	this->m_models.clear();

	// shader program + VAO = data to render
	// --- 1st task data ----------------------------------------------------------
	//this->addModel(this->getShaderProgram("default"), this->getVAO("triangle"), 0, 3);
	//this->addModel(this->getShaderProgram("defaultColorFromPosition"), this->getVAO("triangle"), 0, 3);
	//this->addModel(this->getShaderProgram("defaultColorData"), this->getVAO("triangleColorData"), 0, 3);
	//this->addModel(this->getShaderProgram("yellow"), this->getVAO("square"), 0, 6);

	// --- zpg data ---------------------------------------------------------------
	// --- default
	//this->addModel(this->getShaderProgram("defaultColorData"), this->getVAO("zpgBushes"), 0, 8730);
	//this->addModel(this->getShaderProgram("defaultColorData"), this->getVAO("zpgGift"), 0, 66624);
	//this->addModel(this->getShaderProgram("defaultColorData"), this->getVAO("zpgPlain"), 0, 36);
	//this->addModel(this->getShaderProgram("defaultColorData"), this->getVAO("zpgSphere"), 0, 17280);
	//this->addModel(this->getShaderProgram("defaultColorData"), this->getVAO("zpgSuziFlat"), 0, 17424);
	//this->addModel(this->getShaderProgram("defaultColorData"), this->getVAO("zpgSuziSmooth"), 0, 17424);
	//this->addModel(this->getShaderProgram("defaultColorData"), this->getVAO("zpgTree"), 0, 92814);

	// --- transforming
	//this->addModel(this->getShaderProgram("transformingColorData"), this->getVAO("zpgSphere"), 0, 17280);
	//this->addModel(this->getShaderProgram("transformingColorData"), this->getVAO("zpgTree"), 0, 92814);

	// --- tmp data ---------------------------------------------------------------
	//this->addModel(this->getShaderProgram("default"), this->getVAO("pentagram"), 0, 15);

	// --- scenes -----------------------------------------------------------------
	this->createSceneMagicForest(100, 50); // 100 trees and bushes; area 30x30
}

void ModelVault::createSceneMagicForest(int t_numberOfTrees, float t_areaSize) {
	srand(static_cast<unsigned int>(time(0))); // seed random number generator

	VBO* tmpVBO;
	VAO* tmpVAO;
	Model* tmpModel;

	// surrounding world
	tmpVBO = new VBO(SURROUNDING_WORLD);
	this->addVBO("xtraSurroundingWorld", tmpVBO);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("xtraSurroundingWorld", tmpVAO);

	this->addModel(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 216);

	// trees
	for (int i = 0; i < t_numberOfTrees; ++i) {
		// generate a random scale (size) between 0.5 and 1.5
		float scale = 0.5f + static_cast<float>(rand()) / RAND_MAX;

		// generate a random rotation around the y-axis
		float rotationAngle = static_cast<float>(rand()) / RAND_MAX * 360.0f;

		// generate a random position in the area
		float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize - t_areaSize / 2;
		float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize - t_areaSize / 2;
		glm::vec3 position = glm::vec3(x, 0.0f, z);

		// tree
		tmpVBO = new VBO(sizeof(tree), tree);
		//tmpVBO->transform(scale, 0.f, rotationAngle, 0.f, position, true);
		this->addVBO("zpgTree{i}", tmpVBO);

		tmpVAO = new VAO();
		tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
		tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		this->addVAO("zpgTree{i}", tmpVAO);

		// BLA
		glm::mat4 vertexTransformation = glm::mat4(1.0f);

		// vertices transformation matrix
		vertexTransformation = glm::translate(vertexTransformation, position);
		vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation around X-axis
		vertexTransformation = glm::rotate(vertexTransformation, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // rotation around Y-axis
		vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f)); // rotation around Z-axis
		vertexTransformation = glm::scale(vertexTransformation, glm::vec3(scale));

		//this->addModel(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 92814);
		tmpModel = new Model(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 92814);
		tmpModel->getTransformation()->addTransformation(vertexTransformation);
		this->addModel(tmpModel);
	}

	// bushes
	for (int i = 0; i < t_numberOfTrees; ++i) {
		// generate a random scale (size) between 0.5 and 1.5
		float scale = 0.5f + static_cast<float>(rand()) / RAND_MAX;

		// generate a random rotation around the y-axis
		float rotationAngle = static_cast<float>(rand()) / RAND_MAX * 360.0f;

		// generate a random position in the area
		float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize - t_areaSize / 2;
		float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize - t_areaSize / 2;
		glm::vec3 position = glm::vec3(x, 0.0f, z);

		// bushes
		tmpVBO = new VBO(sizeof(bushes), bushes);
		//tmpVBO->transform(scale, 0.f, rotationAngle, 0.f, position, true);
		this->addVBO("zpgBushes{i}", tmpVBO);

		tmpVAO = new VAO();
		tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
		tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		this->addVAO("zpgBushes{i}", tmpVAO);

		// BLA
		glm::mat4 vertexTransformation = glm::mat4(1.0f);

		// vertices transformation matrix
		vertexTransformation = glm::translate(vertexTransformation, position);
		vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation around X-axis
		vertexTransformation = glm::rotate(vertexTransformation, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // rotation around Y-axis
		vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f)); // rotation around Z-axis
		vertexTransformation = glm::scale(vertexTransformation, glm::vec3(scale));

		//this->addModel(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 8730);
		tmpModel = new Model(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 8730);
		tmpModel->getTransformation()->addTransformation(vertexTransformation);
		this->addModel(tmpModel);
	}

	// suziFlat
	tmpVBO = new VBO(sizeof(suziFlat), suziFlat);
	//tmpVBO->transform(1.f, 0.f, 0.f, 0.f, glm::vec3(-3.f, 1.f, 33.f), true);
	//tmpVBO->transform(2.f, 0.f, 180.f, 0.f, glm::vec3(0.f, 1.f, 33.f), true);
	this->addVBO("zpgSuziFlat", tmpVBO);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSuziFlat", tmpVAO);

	// BLA
	glm::mat4 vertexTransformation = glm::mat4(1.0f);

	// vertices transformation matrix
	vertexTransformation = glm::translate(vertexTransformation, glm::vec3(-3.f, 1.f, 33.f));
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation around X-axis
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotation around Y-axis
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f)); // rotation around Z-axis
	vertexTransformation = glm::scale(vertexTransformation, glm::vec3(1.f));
	
	//vertexTransformation = glm::translate(vertexTransformation, glm::vec3(0.f, 1.f, 33.f));
	//vertexTransformation = glm::rotate(vertexTransformation, glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotation around Y-axis

	//this->addModel(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 17424);
	tmpModel = new Model(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 17424);
	tmpModel->getTransformation()->addTransformation(vertexTransformation);
	this->addModel(tmpModel);

	// suziSmooth
	tmpVBO = new VBO(sizeof(suziSmooth), suziSmooth);
	//tmpVBO->transform(1.f, 0.f, 0.f, 0.f, glm::vec3(3.f, 1.f, 33.f), true);
	this->addVBO("zpgSuziSmooth", tmpVBO);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSuziSmooth", tmpVAO);

	// BLA
	vertexTransformation = glm::mat4(1.0f);

	// vertices transformation matrix
	vertexTransformation = glm::translate(vertexTransformation, glm::vec3(3.f, 1.f, 33.f));
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation around X-axis
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotation around Y-axis
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f)); // rotation around Z-axis
	vertexTransformation = glm::scale(vertexTransformation, glm::vec3(1.f));

	//this->addModel(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 17424);
	tmpModel = new Model(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 17424);
	tmpModel->getTransformation()->addTransformation(vertexTransformation);
	this->addModel(tmpModel);

	// gift
	tmpVBO = new VBO(sizeof(gift), gift);
	//tmpVBO->transform(6.f, 0.f, 0.f, 0.f, glm::vec3(0.f, 0.f, 0.f), true);
	this->addVBO("zpgGift", tmpVBO);

	tmpVAO = new VAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	tmpVAO->addBuffer(*tmpVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgGift", tmpVAO);

	// BLA
	vertexTransformation = glm::mat4(1.0f);

	// vertices transformation matrix
	vertexTransformation = glm::translate(vertexTransformation, glm::vec3(0.f, 0.f, 0.f));
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation around X-axis
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotation around Y-axis
	vertexTransformation = glm::rotate(vertexTransformation, glm::radians(0.f), glm::vec3(0.0f, 0.0f, 1.0f)); // rotation around Z-axis
	vertexTransformation = glm::scale(vertexTransformation, glm::vec3(6.f));

	//this->addModel(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 66624);
	tmpModel = new Model(this->getShaderProgram("transformingColorData"), tmpVAO, 0, 66624);
	tmpModel->getTransformation()->addTransformation(vertexTransformation);
	this->addModel(tmpModel);
}
