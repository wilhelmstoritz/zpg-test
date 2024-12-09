#include "SceneBuilderPlugin03.h"
#include "Config.h"

#include "resShaders.h"

#include "ModelLibrary.h"
#include "ModelLetters.h"
#include "sphere.h"

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin03::createShaders() {
    // vertex & fragment shaders; shader program
    /*
    this->m_shaderWarehouse->createVertexShader("03::vert:normal", VSHADER_NORMAL);
    this->m_shaderWarehouse->createFragmentShader("03::frag:lambertian", FSHADER_LAMBERTIAN);
    this->m_shaderWarehouse->createFragmentShader("03::frag:phong", FSHADER_PHONG);
    
    this->m_shaderWarehouse->createShaderProgram("shader:lambertian",
        *this->m_shaderWarehouse->getShader("03::vert:normal"),
        *this->m_shaderWarehouse->getShader("03::frag:lambertian"));
    
    this->m_shaderWarehouse->createShaderProgram("shader:phong",
        *this->m_shaderWarehouse->getShader("03::vert:normal"),
        *this->m_shaderWarehouse->getShader("03::frag:phong"));

    //this->m_shaderWarehouse->createShaderProgram("shader:lambertian", (this->m_shaderResourcesPath + "03/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "03/lambertian-multiple-lights.frag.glsl").c_str());
    //this->m_shaderWarehouse->createShaderProgram("shader:phong",      (this->m_shaderResourcesPath + "03/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "03/phong-multiple-lights.frag.glsl").c_str());
	*/

	// replaced by current versions supported by shader program code
    this->m_shaderWarehouse->createShaderProgram("shader:lambertian", (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/lambertian.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("shader:phong",      (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/phong.frag.glsl").c_str());
}

void SceneBuilderPlugin03::createLights() {
	Light* light = this->m_lightWarehouse->createLight("light01default", Light::LightTypeE::POINT, glm::vec3(0.f, 0.f, 0.f));
    light->setDiffuseColor(glm::vec3(0.f, 0.f, 1.f));
    light->setSpecularColor(glm::vec3(1.f, 0.f, 0.f));

	this->m_lightWarehouse->createLight("light02", Light::LightTypeE::POINT, glm::vec3(-10.f, 10.f, 10.f));
}

void SceneBuilderPlugin03::createModels() {
    // skybox
    this->m_modelWarehouse->createModel(
        "03::skybox",
        //"shader:lambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        "shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(Config::SKYBOX_XSIZE, Config::SKYBOX_YSIZE, Config::SKYBOX_ZSIZE),
        glm::vec3(0.f),
        glm::vec3(Config::SKYBOX_XMIN, Config::SKYBOX_YMIN, Config::SKYBOX_ZMIN));

    // spheres
    this->m_modelWarehouse->createVertexResources("sphere", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    this->m_modelWarehouse->createModel("sphere01", "shader:lambertian", "sphere", 0, 2880, glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 2.f,  0.f, 0.f));
    this->m_modelWarehouse->createModel("sphere02", "shader:lambertian", "sphere", 0, 2880, glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 0.f,  2.f, 0.f));
    this->m_modelWarehouse->createModel("sphere03", "shader:phong",      "sphere", 0, 2880, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-2.f,  0.f, 0.f));
    this->m_modelWarehouse->createModel("sphere04", "shader:phong",      "sphere", 0, 2880, glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 0.f, -2.f, 0.f));

    // letters
    this->m_modelWarehouse->createVertexResources("letter_L", ModelLetters::getLetter(ModelLetters::LETTER_L), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_P", ModelLetters::getLetter(ModelLetters::LETTER_P), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_a", ModelLetters::getLetter(ModelLetters::LETTER_a), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_b", ModelLetters::getLetter(ModelLetters::LETTER_b), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_e", ModelLetters::getLetter(ModelLetters::LETTER_e), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_h", ModelLetters::getLetter(ModelLetters::LETTER_h), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_i", ModelLetters::getLetter(ModelLetters::LETTER_i), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_o", ModelLetters::getLetter(ModelLetters::LETTER_o), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_m", ModelLetters::getLetter(ModelLetters::LETTER_m), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_n", ModelLetters::getLetter(ModelLetters::LETTER_n), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_g", ModelLetters::getLetter(ModelLetters::LETTER_g), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_r", ModelLetters::getLetter(ModelLetters::LETTER_r), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("letter_t", ModelLetters::getLetter(ModelLetters::LETTER_t), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    float size = 0.1f;
    float offsetX = 13.f;
    float offsetY = 13.f;
    this->m_modelWarehouse->createModel("letter_L01", "shader:lambertian", "letter_L", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_L), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX),                                        size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_a01", "shader:lambertian", "letter_a", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_a), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1)),     size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_m01", "shader:lambertian", "letter_m", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_m), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 2), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_b01", "shader:lambertian", "letter_b", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_b), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 3), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_e01", "shader:lambertian", "letter_e", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_e), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 4), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_r01", "shader:lambertian", "letter_r", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_r), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 5), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_t01", "shader:lambertian", "letter_t", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_t), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 6), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_i01", "shader:lambertian", "letter_i", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_i), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 7), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_a02", "shader:lambertian", "letter_a", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_a), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 8), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_n01", "shader:lambertian", "letter_n", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_n), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 9), size * offsetY, 0.f));

    offsetX = -43.f;
    offsetY = -19.f;
    this->m_modelWarehouse->createModel("letter_P11", "shader:phong", "letter_P", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX),                                        size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_h11", "shader:phong", "letter_h", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1)),     size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_o11", "shader:phong", "letter_o", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 2), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_n11", "shader:phong", "letter_n", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 3), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("letter_g11", "shader:phong", "letter_g", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_XSIZE + 1) * 4), size * offsetY, 0.f));
}

void SceneBuilderPlugin03::postProcess() {
    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 0.f, 11.f),
        glm::vec3(0.f, 0.f, -1.f));
}
