#include "SceneBuilder.h"

#include "resShaders.h"

void SceneBuilder::createBasicShaders() {

}

void SceneBuilder::createShaders() {





}

void SceneBuilder::createTemporaryShaders() {
    // vertex & fragment shaders; shader program
    /*
    this->m_shaderFactory->createVertexShader("vshaderTMP", VSHADER_TMP);
    this->m_shaderFactory->createFragmentShader("fshaderTMP", FSHADER_TMP);

    this->m_shaderFactory->createShaderProgram("shaderTMP",
        *this->m_shaderFactory->getShader("vshaderTMP"),
        *this->m_shaderFactory->getShader("fshaderTMP"));
    */
    this->m_shaderFactory->createShaderProgram("shaderTMP", (this->m_shaderResourcesPath + "tmp.vert.glsl").c_str(), (this->m_shaderResourcesPath + "tmp.frag.glsl").c_str());
}
