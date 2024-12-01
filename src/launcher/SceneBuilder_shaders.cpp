#include "SceneBuilder.h"

#include "resShaders.h"

void SceneBuilder::createBasicShaders() {
    /* 1st task shaders */
    // vertex & fragment shaders
    this->m_shaderFactory->createVertexShader("basic_vshader", BASIC_VSHADER);
    this->m_shaderFactory->createFragmentShader("basic_fshader", BASIC_FSHADER);

    this->m_shaderFactory->createVertexShader("basic_vshaderColorFromPosition", BASIC_VSHADER_COLORFROMPOSITION);
    this->m_shaderFactory->createFragmentShader("basic_fshaderColorFromPosition", BASIC_FSHADER_COLORFROMPOSITION);

    this->m_shaderFactory->createVertexShader("basic_vshaderColorData", BASIC_VSHADER_COLORDATA);
    this->m_shaderFactory->createFragmentShader("basic_fshaderColorData", BASIC_FSHADER_COLORDATA);

    this->m_shaderFactory->createFragmentShader("basic_fshaderYellow", BASIC_FSHADER_YELLOW);

    // shader programs
    this->m_shaderFactory->createShaderProgram("basic_shader",
        *this->m_shaderFactory->getShader("basic_vshader"),
        *this->m_shaderFactory->getShader("basic_fshader"));

    this->m_shaderFactory->createShaderProgram("basic_shaderColorFromPosition",
        *this->m_shaderFactory->getShader("basic_vshaderColorFromPosition"),
        *this->m_shaderFactory->getShader("basic_fshaderColorFromPosition"));

    this->m_shaderFactory->createShaderProgram("basic_shaderColorData",
        *this->m_shaderFactory->getShader("basic_vshaderColorData"),
        *this->m_shaderFactory->getShader("basic_fshaderColorData"));

    this->m_shaderFactory->createShaderProgram("basic_shaderYellow",
        *this->m_shaderFactory->getShader("basic_vshader"),
        *this->m_shaderFactory->getShader("basic_fshaderYellow"));
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
    //this->m_shaderFactory->createShaderProgram("shaderLambertian", (this->m_resourcesPath + "03-normals.vert.glsl").c_str(), (this->m_resourcesPath + "03b-lambertian-multiple-lights.frag.glsl").c_str());
    //this->m_shaderFactory->createShaderProgram("shaderPhong", (this->m_resourcesPath + "03-normals.vert.glsl").c_str(), (this->m_resourcesPath + "03b-phong-multiple-lights.frag.glsl").c_str());

    /* 4th task shaders */
    this->m_shaderFactory->createShaderProgram("shaderLambertian", (this->m_resourcesPath + "04-normals.vert.glsl").c_str(), (this->m_resourcesPath + "04-lambertian.frag.glsl").c_str());
    this->m_shaderFactory->createShaderProgram("shaderPhong", (this->m_resourcesPath + "04-normals.vert.glsl").c_str(), (this->m_resourcesPath + "04-phong.frag.glsl").c_str());
    this->m_shaderFactory->createShaderProgram("shaderSingleColor", (this->m_resourcesPath + "04-normals.vert.glsl").c_str(), (this->m_resourcesPath + "04-single-color.frag.glsl").c_str());
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
    this->m_shaderFactory->createShaderProgram("shaderTMP", (this->m_resourcesPath + "tmp.vert.glsl").c_str(), (this->m_resourcesPath + "tmp.frag.glsl").c_str());
}
