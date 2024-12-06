#include "SceneBuilder.h"

#include "resShaders.h"

void SceneBuilder::createBasicShaders() {

}

void SceneBuilder::createShaders() {
    /* 2nd task shaders */
    // vertex & fragment shaders; shader program
    this->m_shaderFactory->createVertexShader("vshaderViewProjection", VSHADER_VIEW_PROJECTION);
    this->m_shaderFactory->createFragmentShader("fshaderViewProjection", FSHADER_VIEW_PROJECTION);

    this->m_shaderFactory->createShaderProgram("shaderViewProjection",
        *this->m_shaderFactory->getShader("vshaderViewProjection"),
        *this->m_shaderFactory->getShader("fshaderViewProjection"));

    /* 3rd task shaders */
    // vertex & fragment shaders; shader program
    /*
    this->m_shaderFactory->createVertexShader("vshaderNormal", VSHADER_NORMAL);
    this->m_shaderFactory->createFragmentShader("fshaderLambertian", FSHADER_LAMBERTIAN);
    this->m_shaderFactory->createFragmentShader("fshaderPhong", FSHADER_PHONG);

    this->m_shaderFactory->createShaderProgram("shaderLambertian",
        *this->m_shaderFactory->getShader("vshaderNormal"),
        *this->m_shaderFactory->getShader("fshaderLambertian"));

    this->m_shaderFactory->createShaderProgram("shaderPhong",
        *this->m_shaderFactory->getShader("vshaderNormal"),
        *this->m_shaderFactory->getShader("fshaderPhong"));
    */
    //this->m_shaderFactory->createShaderProgram("shaderLambertian", (this->m_shaderResourcesPath + "03/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "03/lambertian-multiple-lights.frag.glsl").c_str());
    //this->m_shaderFactory->createShaderProgram("shaderPhong", (this->m_shaderResourcesPath + "03/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "03/phong-multiple-lights.frag.glsl").c_str());

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
