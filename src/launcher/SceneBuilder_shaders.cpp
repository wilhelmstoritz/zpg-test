#include "SceneBuilder.h"

#include "resShaders.h"

void SceneBuilder::createBasicShaders() {

}

void SceneBuilder::createShaders() {




    /* 4th task shaders */
    this->m_shaderFactory->createShaderProgram("shaderLambertian", (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/lambertian.frag.glsl").c_str());
    this->m_shaderFactory->createShaderProgram("shaderPhong", (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/phong.frag.glsl").c_str());
    this->m_shaderFactory->createShaderProgram("shaderSingleColor", (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/single-color.frag.glsl").c_str());
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
