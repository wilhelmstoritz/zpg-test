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

void ModelVault::addShader(const std::string t_name, ZPGShader* t_shader) { this->m_shaders[t_name] = t_shader; }
void ModelVault::addShaderProgram(const std::string t_name, ZPGShaderProgram* t_shaderProgram) { this->m_shaderPrograms[t_name] = t_shaderProgram; }
void ModelVault::addVBO(const std::string t_name, ZPGVBO* t_VBO) { this->m_VBOs[t_name] = t_VBO; }
void ModelVault::addVAO(const std::string t_name, ZPGVAO* t_VAO) { this->m_VAOs[t_name] = t_VAO; }
void ModelVault::addRenderingData(ZPGShaderProgram* t_shaderProgram, ZPGVAO* t_VAO, GLint t_first, GLsizei t_count) {
	this->m_renderingData.push_back(renderingDataT(t_shaderProgram, t_VAO, t_first, t_count));
}

ZPGShader* ModelVault::getShader(const std::string t_name) { return this->m_shaders[t_name]; }
ZPGShaderProgram* ModelVault::getShaderProgram(const std::string t_name) { return this->m_shaderPrograms[t_name]; }
ZPGVBO* ModelVault::getVBO(const std::string t_name) { return this->m_VBOs[t_name]; }
ZPGVAO* ModelVault::getVAO(const std::string t_name) { return this->m_VAOs[t_name]; }
std::vector<ModelVault::renderingDataT>* ModelVault::getRenderingData() { return &this->m_renderingData; }

/*
void ModelVault::addVertexShader(const std::string t_name, const char* t_source) {
	ZPGShader* shader = new ZPGVertexShader(t_source);
	//this->m_shaders[t_name] = shader;
	this->addShader(t_name, shader);
}

void ModelVault::addFragmentShader(const std::string t_name, const char* t_source) {
	ZPGShader* shader = new ZPGFragmentShader(t_source);
	//this->m_shaders[t_name] = shader;
	this->addShader(t_name, shader);
}
*/

// --- private -----------------------------------------------------------------
ModelVault::ModelVault() {
	this->createShaders();
	this->createModels();
	this->createRenderingData();
}

ModelVault::~ModelVault() {
	// cleanup
	for (const auto& item : this->m_VAOs) delete(item.second);
	for (const auto& item : this->m_VBOs) delete(item.second);
	for (const auto& item : this->m_shaderPrograms) delete(item.second);
	for (const auto& item : this->m_shaders) delete(item.second);
}

void ModelVault::createShaders() {
	// vertex shaders
	// --- default
	ZPGVertexShader* zpgVertexShader = new ZPGVertexShader(DEFAULT_VERTEX_SHADER);
	this->addShader("v_default", zpgVertexShader);

	zpgVertexShader = new ZPGVertexShader(DEFAULT_VERTEX_SHADER_COLORFROMPOSITION);
	this->addShader("v_defaultColorFromPosition", zpgVertexShader);

	zpgVertexShader = new ZPGVertexShader(DEFAULT_VERTEX_SHADER_COLORDATA);
	this->addShader("v_defaultColorData", zpgVertexShader);

	// --- transforming
	zpgVertexShader = new ZPGVertexShader(TRANSFORMING_VERTEX_SHADER_COLORDATA);
	this->addShader("v_transformingColorData", zpgVertexShader);

	// fragment shaders
	// --- default
	ZPGFragmentShader* zpgFragmentShader = new ZPGFragmentShader(DEFAULT_FRAGMENT_SHADER);
	this->addShader("f_default", zpgFragmentShader);

	zpgFragmentShader = new ZPGFragmentShader(DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION);
	this->addShader("f_defaultColorFromPosition", zpgFragmentShader);

	zpgFragmentShader = new ZPGFragmentShader(DEFAULT_FRAGMENT_SHADER_COLORDATA);
	this->addShader("f_defaultColorData", zpgFragmentShader);

	zpgFragmentShader = new ZPGFragmentShader(YELLOW_FRAGMENT_SHADER);
	this->addShader("f_yellow", zpgFragmentShader);

	// --- transforming
	zpgFragmentShader = new ZPGFragmentShader(TRANSFORMING_FRAGMENT_SHADER_COLORDATA);
	this->addShader("f_transformingColorData", zpgFragmentShader);

	// shader programs
	// --- default
	ZPGShaderProgram* zpgShaderProgram = new ZPGShaderProgram(*this->getShader("v_default"), *this->getShader("f_default"));
	this->addShaderProgram("default", zpgShaderProgram);

	zpgShaderProgram = new ZPGShaderProgram(*this->getShader("v_defaultColorFromPosition"), *this->getShader("f_defaultColorFromPosition"));
	this->addShaderProgram("defaultColorFromPosition", zpgShaderProgram);

	zpgShaderProgram = new ZPGShaderProgram(*this->getShader("v_defaultColorData"), *this->getShader("f_defaultColorData"));
	this->addShaderProgram("defaultColorData", zpgShaderProgram);

	zpgShaderProgram = new ZPGShaderProgram(*this->getShader("v_default"), *this->getShader("f_yellow"));
	this->addShaderProgram("yellow", zpgShaderProgram);

	// --- transforming
	zpgShaderProgram = new ZPGShaderProgram(*this->getShader("v_transformingColorData"), *this->getShader("f_transformingColorData"));
	this->addShaderProgram("transformingColorData", zpgShaderProgram);
}

void ModelVault::createModels() {
	// --- 1st task models --------------------------------------------------------
	// VBOs
	ZPGVBO* zpgVBO = new ZPGVBO(TRIANGLE_POINTS);
	this->addVBO("triangle", zpgVBO);

	zpgVBO = new ZPGVBO(TRIANGLE_POINTS_COLORDATA);
	this->addVBO("triangleColorData", zpgVBO);

	zpgVBO = new ZPGVBO(SQUARE_POINTS);
	this->addVBO("square", zpgVBO);

	// VAOs
	ZPGVAO* zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*this->getVBO("triangle"), 0, 3, 0, NULL);
	this->addVAO("triangle", zpgVAO);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*this->getVBO("triangleColorData"), 0, 3, 6 * sizeof(float), (void*)0);
	zpgVAO->addBuffer(*this->getVBO("triangleColorData"), 1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	this->addVAO("triangleColorData", zpgVAO);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*this->getVBO("square"), 0, 3, 0, NULL);
	this->addVAO("square", zpgVAO);

	// --- zpg models -------------------------------------------------------------
	// bushes
	zpgVBO = new ZPGVBO(sizeof(bushes), bushes);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgBushes", zpgVAO);

	// gift
	zpgVBO = new ZPGVBO(sizeof(gift), gift);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgGift", zpgVAO);

	// plain
	zpgVBO = new ZPGVBO(sizeof(plain), plain);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgPlain", zpgVAO);

	// sphere
	zpgVBO = new ZPGVBO(sizeof(sphere), sphere);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSphere", zpgVAO);

	// suziFlat
	zpgVBO = new ZPGVBO(sizeof(suziFlat), suziFlat);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSuziFlat", zpgVAO);

	// suziSmooth
	zpgVBO = new ZPGVBO(sizeof(suziSmooth), suziSmooth);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSuziSmooth", zpgVAO);

	// tree
	zpgVBO = new ZPGVBO(sizeof(tree), tree);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgTree", zpgVAO);

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

	ZPGVBO* tmpVBO = new ZPGVBO(sizeof(PENTAGON), PENTAGON);

	ZPGVAO* tmpVAO = new ZPGVAO();
	tmpVAO->addBuffer(*tmpVBO, 0, 3, 0, NULL);
	this->addVAO("pentagram", tmpVAO);
}

void ModelVault::createRenderingData() {
	// shader program + VAO = data to render
	// --- 1st task data ----------------------------------------------------------
	//this->addRenderingData(this->getShaderProgram("default"), this->getVAO("triangle"), 0, 3);
	//this->addRenderingData(this->getShaderProgram("defaultColorFromPosition"), this->getVAO("triangle"), 0, 3);
	//this->addRenderingData(this->getShaderProgram("defaultColorData"), this->getVAO("triangleColorData"), 0, 3);
	//this->addRenderingData(this->getShaderProgram("yellow"), this->getVAO("square"), 0, 6);

	// --- zpg data ---------------------------------------------------------------
	// --- default
	//this->addRenderingData(this->getShaderProgram("defaultColorData"), this->getVAO("zpgBushes"), 0, 8730);
	//this->addRenderingData(this->getShaderProgram("defaultColorData"), this->getVAO("zpgGift"), 0, 66624);
	//this->addRenderingData(this->getShaderProgram("defaultColorData"), this->getVAO("zpgPlain"), 0, 36);
	//this->addRenderingData(this->getShaderProgram("defaultColorData"), this->getVAO("zpgSphere"), 0, 17280);
	//this->addRenderingData(this->getShaderProgram("defaultColorData"), this->getVAO("zpgSuziFlat"), 0, 17424);
	//this->addRenderingData(this->getShaderProgram("defaultColorData"), this->getVAO("zpgSuziSmooth"), 0, 17424);
	//this->addRenderingData(this->getShaderProgram("defaultColorData"), this->getVAO("zpgTree"), 0, 92814);

	// --- transforming
	//this->addRenderingData(this->getShaderProgram("transformingColorData"), this->getVAO("zpgSphere"), 0, 17280);
	//this->addRenderingData(this->getShaderProgram("transformingColorData"), this->getVAO("zpgTree"), 0, 92814);

	// --- tmp data ---------------------------------------------------------------
	//this->addRenderingData(this->getShaderProgram("default"), this->getVAO("pentagram"), 0, 15);

	// --- scenes -----------------------------------------------------------------
	this->createSceneMagicForest(20, 30);
}

void ModelVault::createSceneMagicForest(int t_numberOfTrees, float t_areaSize) {
	this->m_renderingData.clear();
	srand(static_cast<unsigned int>(time(0))); // seed random number generator

	ZPGVBO* zpgVBO;
	ZPGVAO* zpgVAO;

	/*
	// plane
	zpgVBO = new ZPGVBO(PLANE_POINTS);
	zpgVBO->transform(glm::vec3(0.f, -3.f, 0.f), 22.f, 0.f, false);
	this->addVBO("xtraPlane", zpgVBO);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("xtraPlane", zpgVAO);

	this->addRenderingData(this->getShaderProgram("transformingColorData"), zpgVAO, 0, 36);
	*/

	// trees
	for (int i = 0; i < t_numberOfTrees; ++i) {
		// generate a random position in the area
		float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize - t_areaSize / 2;
		float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize - t_areaSize / 2;
		glm::vec3 position = glm::vec3(x, 0.0f, z);

		// generate a random scale (size) between 0.5 and 1.5
		float scale = 0.5f + static_cast<float>(rand()) / RAND_MAX;

		// generate a random rotation around the y-axis
		float rotationAngle = static_cast<float>(rand()) / RAND_MAX * 360.0f;

		// tree
		zpgVBO = new ZPGVBO(sizeof(tree), tree);
		zpgVBO->transform(position, scale, rotationAngle, true);
		this->addVBO("zpgTree{i}", zpgVBO);

		zpgVAO = new ZPGVAO();
		zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
		zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		this->addVAO("zpgTree{i}", zpgVAO);

		this->addRenderingData(this->getShaderProgram("transformingColorData"), zpgVAO, 0, 92814);
	}

	// bushes
	for (int i = 0; i < t_numberOfTrees; ++i) {
		// generate a random position in the area
		float x = static_cast<float>(rand()) / RAND_MAX * t_areaSize - t_areaSize / 2;
		float z = static_cast<float>(rand()) / RAND_MAX * t_areaSize - t_areaSize / 2;
		glm::vec3 position = glm::vec3(x, 0.0f, z);

		// generate a random scale (size) between 0.5 and 1.5
		float scale = 0.5f + static_cast<float>(rand()) / RAND_MAX;

		// generate a random rotation around the y-axis
		float rotationAngle = static_cast<float>(rand()) / RAND_MAX * 360.0f;

		// bushes
		zpgVBO = new ZPGVBO(sizeof(bushes), bushes);
		zpgVBO->transform(position, scale, rotationAngle, true);
		this->addVBO("zpgBushes{i}", zpgVBO);

		zpgVAO = new ZPGVAO();
		zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
		zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		this->addVAO("zpgBushes{i}", zpgVAO);

		this->addRenderingData(this->getShaderProgram("transformingColorData"), zpgVAO, 0, 8730);
	}

	// suziFlat
	zpgVBO = new ZPGVBO(sizeof(suziFlat), suziFlat);
	zpgVBO->transform(glm::vec3(-3.f, 0.f, 20.f), 1.f, 0.f, true);
	this->addVBO("zpgSuziFlat", zpgVBO);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSuziFlat", zpgVAO);

	this->addRenderingData(this->getShaderProgram("transformingColorData"), zpgVAO, 0, 17424);

	// suziSmooth
	zpgVBO = new ZPGVBO(sizeof(suziSmooth), suziSmooth);
	zpgVBO->transform(glm::vec3(3.f, 0.f, 20.f), 1.f, 0.f, true);
	this->addVBO("zpgSuziSmooth", zpgVBO);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgSuziSmooth", zpgVAO);

	this->addRenderingData(this->getShaderProgram("transformingColorData"), zpgVAO, 0, 17424);

	// gift
	zpgVBO = new ZPGVBO(sizeof(gift), gift);
	zpgVBO->transform(glm::vec3(0.f, 0.f, 0.f), 6.f, 0.f, true);
	this->addVBO("zpgGift", zpgVBO);

	zpgVAO = new ZPGVAO();
	zpgVAO->addBuffer(*zpgVBO, 0, 3, 6 * sizeof(float), (GLvoid*)0);
	zpgVAO->addBuffer(*zpgVBO, 1, 3, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	this->addVAO("zpgGift", zpgVAO);

	this->addRenderingData(this->getShaderProgram("transformingColorData"), zpgVAO, 0, 66624);
}
