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
        *this->m_shaderFactory->getShader("v_default"), *this->m_shaderFactory->getShader("f_default"));
    
    this->m_shaderFactory->createShaderProgram("defaultColorFromPosition",
		*this->m_shaderFactory->getShader("v_defaultColorFromPosition"), *this->m_shaderFactory->getShader("f_defaultColorFromPosition"));

    this->m_shaderFactory->createShaderProgram("defaultColorData",
        *this->m_shaderFactory->getShader("v_defaultColorData"), *this->m_shaderFactory->getShader("f_defaultColorData"));

    this->m_shaderFactory->createShaderProgram("yellow",
        *this->m_shaderFactory->getShader("v_default"), *this->m_shaderFactory->getShader("f_yellow"));
}

void ModelVault::createTransformingShaders() {
    // vertex & fragment shaders
    this->m_shaderFactory->createVertexShader("v_transformingColorData", TRANSFORMING_VERTEX_SHADER_COLORDATA);
    this->m_shaderFactory->createFragmentShader("f_transformingColorData", TRANSFORMING_FRAGMENT_SHADER_COLORDATA);

    // shader programs
    this->m_shaderFactory->createShaderProgram("transformingColorData",
        *this->m_shaderFactory->getShader("v_transformingColorData"), *this->m_shaderFactory->getShader("f_transformingColorData"));
}

// --- private -----------------------------------------------------------------
ModelVault::ModelVault() {
	this->m_shaderFactory = new ShaderFactory();
	this->m_modelFactory = new ModelFactory(this->m_shaderFactory);
}

ModelVault::~ModelVault() {
	// cleanup
	delete this->m_modelFactory;
	delete this->m_shaderFactory;
}
