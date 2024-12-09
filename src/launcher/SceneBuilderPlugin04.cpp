#include "SceneBuilderPlugin04.h"
//#include "AppUtils.h"
//#include "Config.h"

//#include "resShaders.h"

//#include "ModelLibrary.h"
//#include "ModelLetters.h"
//#include "tree.h"
//#include "bushes.h"
//#include "sphere.h"
//#include "suzi_flat.h"
//#include "suzi_smooth.h"
//#include "gift.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin04::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("shader:lambertian",   (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/lambertian.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("shader:phong",        (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/phong.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("shader:single_color", (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/single-color.frag.glsl").c_str());
}

void SceneBuilderPlugin04::createLights() {
}

void SceneBuilderPlugin04::createModels() {
}

void SceneBuilderPlugin04::postProcess() {
}
