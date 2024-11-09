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

ModelVault* ModelVault::getInstance(Camera* t_camera) {
    ModelVault* instance = ModelVault::getInstance();
    instance->setCamera(t_camera);

    return instance;
}

void ModelVault::setCamera(Camera* t_camera) {
    std::lock_guard<std::mutex> lock(_mtx);
    t_camera->getObserverSubject()->removeAllObservers();

    for (const auto& pair : *this->m_shaderFactory->getShaderPrograms()) {
        pair.second->updateObserver(t_camera);
        t_camera->getObserverSubject()->addObserver(pair.second.get());
    }
}

const std::vector<Model*>& ModelVault::getModels() const {
	return this->m_models;
}

/*
const std::vector<Model*>* ModelVault::getModels() const {
	return &this->m_models;
}
*/

// --- private -----------------------------------------------------------------
ModelVault::ModelVault() {
	this->m_shaderFactory = new ShaderFactory();
	this->m_modelFactory = new ModelFactory(this->m_shaderFactory);

    this->createContext();
}

ModelVault::~ModelVault() {
	// cleanup
	delete this->m_modelFactory;
	delete this->m_shaderFactory;
}

void ModelVault::createContext() {
    // create shaders and shader programs
	this->createDefaultShaders();
	this->createTransformingShaders();

    // create models
	this->createDefaultModels();

	// get all models
	for (const auto& pair : *this->m_modelFactory->getModels()) {
		this->m_models.push_back(pair.second.get());
	}
    //this->m_models = this->m_modelFactory->getModels();
}

// === shader factory ==========================================================
void ModelVault::createDefaultShaders() {
    // vertex & fragment shaders
    this->m_shaderFactory->createVertexShader("v_default", DEFAULT_VERTEX_SHADER);
    this->m_shaderFactory->createFragmentShader("f_default", DEFAULT_FRAGMENT_SHADER);

    this->m_shaderFactory->createVertexShader("v_defaultColorFromPosition", DEFAULT_VERTEX_SHADER_COLORFROMPOSITION);
    this->m_shaderFactory->createFragmentShader("f_defaultColorFromPosition", DEFAULT_FRAGMENT_SHADER_COLORFROMPOSITION);

    this->m_shaderFactory->createVertexShader("v_defaultColorData", DEFAULT_VERTEX_SHADER_COLORDATA);
    this->m_shaderFactory->createFragmentShader("f_defaultColorData", DEFAULT_FRAGMENT_SHADER_COLORDATA);

    this->m_shaderFactory->createFragmentShader("f_yellow", YELLOW_FRAGMENT_SHADER);

    // shader programs
    this->m_shaderFactory->createShaderProgram("default",
        *this->m_shaderFactory->getShader("v_default"),
        *this->m_shaderFactory->getShader("f_default"));

    this->m_shaderFactory->createShaderProgram("defaultColorFromPosition",
        *this->m_shaderFactory->getShader("v_defaultColorFromPosition"),
        *this->m_shaderFactory->getShader("f_defaultColorFromPosition"));

    this->m_shaderFactory->createShaderProgram("defaultColorData",
        *this->m_shaderFactory->getShader("v_defaultColorData"),
        *this->m_shaderFactory->getShader("f_defaultColorData"));

    this->m_shaderFactory->createShaderProgram("yellow",
        *this->m_shaderFactory->getShader("v_default"),
        *this->m_shaderFactory->getShader("f_yellow"));
}

void ModelVault::createTransformingShaders() {
    // vertex & fragment shaders
    this->m_shaderFactory->createVertexShader("v_transformingNormalData", TRANSFORMING_VERTEX_SHADER_NORMALDATA);
    this->m_shaderFactory->createFragmentShader("f_transformingNormalData", TRANSFORMING_FRAGMENT_SHADER_NORMALDATA);

    // shader programs
    this->m_shaderFactory->createShaderProgram("transformingNormalData",
        *this->m_shaderFactory->getShader("v_transformingNormalData"),
        *this->m_shaderFactory->getShader("f_transformingNormalData"));
}

// === model factory ===========================================================
void ModelVault::createDefaultModels() {
    // 1st task models
    //this->m_modelFactory->createVertexResources("triangle", TRIANGLE_POINTS, ModelFactory::s_defaultBufferList);
    //this->m_modelFactory->createVertexResources("triangleColorData", TRIANGLE_POINTS_COLORDATA, ModelFactory::s_defaultPositionColorBufferList);
    //this->m_modelFactory->createVertexResources("square", SQUARE_POINTS, ModelFactory::s_defaultBufferList);

    //this->m_modelFactory->createModel("triangle", "default", "triangle", 0, 3);
    //this->m_modelFactory->createModel("triangleColorFromPosition", "defaultColorFromPosition", "triangle", 0, 3);
    //this->m_modelFactory->createModel("triangleColorData", "defaultColorData", "triangleColorData", 0, 3);
    //this->m_modelFactory->createModel("square", "yellow", "square", 0, 6);
    // all at once
    //this->m_modelFactory->createModel("triangle", "default", TRIANGLE_POINTS, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("triangleColorFromPosition", "defaultColorFromPosition", TRIANGLE_POINTS, ModelFactory::s_defaultBufferList, 0, 3);
    //this->m_modelFactory->createModel("triangleColorData", "defaultColorData", TRIANGLE_POINTS_COLORDATA, ModelFactory::s_defaultPositionColorBufferList, 0, 3);
    //this->m_modelFactory->createModel("square", "yellow", SQUARE_POINTS, ModelFactory::s_defaultBufferList, 0, 6);

    // 2nd task models
    //this->m_modelFactory->createModel("zpgBushes", "transformingNormalData", sizeof(bushes), bushes, ModelFactory::s_defaultPositionNormalBufferList, 0, 8730);
    //this->m_modelFactory->createModel("zpgGift", "transformingNormalData", sizeof(gift), gift, ModelFactory::s_defaultPositionNormalBufferList, 0, 66624);
    //this->m_modelFactory->createModel("zpgPlain", "transformingNormalData", sizeof(plain), plain, ModelFactory::s_defaultPositionNormalBufferList, 0, 36);
    //this->m_modelFactory->createModel("zpgSphere", "transformingNormalData", sizeof(sphere), sphere, ModelFactory::s_defaultPositionNormalBufferList, 0, 17280);
    this->m_modelFactory->createModel("zpgSuziFlat", "transformingNormalData", sizeof(suziFlat), suziFlat, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424);
    //this->m_modelFactory->createModel("zpgSuziSmooth", "transformingNormalData", sizeof(suziSmooth), suziSmooth, ModelFactory::s_defaultPositionNormalBufferList, 0, 17424);
    //this->m_modelFactory->createModel("zpgTree", "transformingNormalData", sizeof(tree), tree, ModelFactory::s_defaultPositionNormalBufferList, 0, 92814);
}
