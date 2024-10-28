#include "ModelVault.h"
#include "data.h"

#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

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
	// --- 1st task models --------------------------------------------------------

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
	// --- zpg models -------------------------------------------------------------

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
	// --- tmp models -------------------------------------------------------------
}

void ModelVault::createRenderingData() {
	// shader program + VAO = data to render
	//this->addRenderingData(this->getShaderProgram("default"), this->getVAO("pentagram"), 0, 15);
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
	this->addRenderingData(this->getShaderProgram("transformingColorData"), this->getVAO("zpgTree"), 0, 92814);
	// --- zpg data ---------------------------------------------------------------
}



/*
void ModelVault::addVertexShader(const std::string t_name, const char* t_source) {
	MyShader* shader = new MyVertexShader(t_source);
	this->m_shaders[t_name] = shader;
}

void ModelVault::addFragmentShader(const std::string t_name, const char* t_source) {
	MyShader* shader = new MyFragmentShader(t_source);
	this->m_shaders[t_name] = shader;
}
*/
