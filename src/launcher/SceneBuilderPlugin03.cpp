#include "SceneBuilderPlugin03.h"
#include "Config.h"

#include "resShaders.h"

#include "ModelLibrary.h"
#include "ModelLetters.h"
#include "sphere.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPlugin03::setSceneProperties(Scene* t_scene) {
    t_scene->setTitle("4 | " + t_scene->getTitle());
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin03::preProcess() {
    // scene size
    this->m_scene->setSize(
        Config::SKYBOX_MIN_VIRTUALWORLD,
        Config::SKYBOX_MAX);

    this->setEnvironment();
}

void SceneBuilderPlugin03::createShaders() {
    // vertex & fragment shaders; shader program
    /*
    this->m_shaderWarehouse->createVertexShader  ("03::vert:normal",     VSHADER_NORMAL);
    this->m_shaderWarehouse->createFragmentShader("03::frag:lambertian", FSHADER_LAMBERTIAN);
    this->m_shaderWarehouse->createFragmentShader("03::frag:phong",      FSHADER_PHONG);
    
    this->m_shaderWarehouse->createShaderProgram("03::shader:lambertian",
        *this->m_shaderWarehouse->getShader("03::vert:normal"),
        *this->m_shaderWarehouse->getShader("03::frag:lambertian"));
    
    this->m_shaderWarehouse->createShaderProgram("03::shader:phong",
        *this->m_shaderWarehouse->getShader("03::vert:normal"),
        *this->m_shaderWarehouse->getShader("03::frag:phong"));

    //this->m_shaderWarehouse->createShaderProgram("03::shader:lambertian", (this->m_shaderResourcesPath + "03/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "03/lambertian-multiple-lights.frag.glsl").c_str());
    //this->m_shaderWarehouse->createShaderProgram("03::shader:phong",      (this->m_shaderResourcesPath + "03/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "03/phong-multiple-lights.frag.glsl"     ).c_str());
	*/

	// replaced by current versions supported by shader program code
    this->m_shaderWarehouse->createShaderProgram("03::shader:lambertian", (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/lambertian.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("03::shader:phong",      (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/phong.frag.glsl"     ).c_str());
}

void SceneBuilderPlugin03::createLights() {
	Light* light = this->m_lightWarehouse->createLight("03::center_light", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f));
	//light->setDiffuseColor(glm::vec3(0.f, 0.f, 1.f));  // blue
	light->setDiffuseColor(glm::vec3(1.f, 0.f, 0.f));  // red
	//light->setSpecularColor(glm::vec3(1.f, 0.f, 0.f)); // red
	light->setSpecularColor(glm::vec3(1.f, 1.f, 0.f)); // yellow

	this->m_lightWarehouse->createLight("03::side_light", Light::lightTypeE::POINT_LIGHT, glm::vec3(-10.f, 10.f, 10.f));
}

void SceneBuilderPlugin03::createModels() {
    // skybox
    this->m_modelWarehouse->createModel(
        "03::skybox",
        //"03::shader:lambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        "03::shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(this->m_size.x, this->m_size.y, this->m_size.z),
        glm::vec3(0.f),
        glm::vec3(this->m_min.x, this->m_min.y, this->m_min.z));

    // spheres
    this->m_modelWarehouse->createVertexResources("res:sphere", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    this->m_modelWarehouse->createModel("03::sphere01", "03::shader:lambertian", "res:sphere", 0, 2880, glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 2.f,  0.f, 0.f));
    this->m_modelWarehouse->createModel("03::sphere02", "03::shader:lambertian", "res:sphere", 0, 2880, glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 0.f,  2.f, 0.f));
    this->m_modelWarehouse->createModel("03::sphere03", "03::shader:phong",      "res:sphere", 0, 2880, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-2.f,  0.f, 0.f));
    this->m_modelWarehouse->createModel("03::sphere04", "03::shader:phong",      "res:sphere", 0, 2880, glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 0.f, -2.f, 0.f));

    // letters
    this->m_modelWarehouse->createVertexResources("res:letter_L", ModelLetters::getLetter(ModelLetters::LETTER_L), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_P", ModelLetters::getLetter(ModelLetters::LETTER_P), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_a", ModelLetters::getLetter(ModelLetters::LETTER_a), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_b", ModelLetters::getLetter(ModelLetters::LETTER_b), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_e", ModelLetters::getLetter(ModelLetters::LETTER_e), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_h", ModelLetters::getLetter(ModelLetters::LETTER_h), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_i", ModelLetters::getLetter(ModelLetters::LETTER_i), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_o", ModelLetters::getLetter(ModelLetters::LETTER_o), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_m", ModelLetters::getLetter(ModelLetters::LETTER_m), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_n", ModelLetters::getLetter(ModelLetters::LETTER_n), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_g", ModelLetters::getLetter(ModelLetters::LETTER_g), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_r", ModelLetters::getLetter(ModelLetters::LETTER_r), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:letter_t", ModelLetters::getLetter(ModelLetters::LETTER_t), ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    float size = 0.1f;
    float offsetX = 13.f;
    float offsetY = 13.f;
    this->m_modelWarehouse->createModel("03::letter_L01", "03::shader:lambertian", "res:letter_L", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_L), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX),                                         size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_a01", "03::shader:lambertian", "res:letter_a", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_a), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1)),     size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_m01", "03::shader:lambertian", "res:letter_m", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_m), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 2), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_b01", "03::shader:lambertian", "res:letter_b", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_b), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 3), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_e01", "03::shader:lambertian", "res:letter_e", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_e), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 4), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_r01", "03::shader:lambertian", "res:letter_r", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_r), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 5), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_t01", "03::shader:lambertian", "res:letter_t", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_t), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 6), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_i01", "03::shader:lambertian", "res:letter_i", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_i), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 7), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_a02", "03::shader:lambertian", "res:letter_a", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_a), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 8), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_n01", "03::shader:lambertian", "res:letter_n", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_n), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 9), size * offsetY, 0.f));

    offsetX = -43.f;
    offsetY = -19.f;
    this->m_modelWarehouse->createModel("03::letter_P11", "03::shader:phong", "res:letter_P", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX),                                         size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_h11", "03::shader:phong", "res:letter_h", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1)),     size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_o11", "03::shader:phong", "res:letter_o", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 2), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_n11", "03::shader:phong", "res:letter_n", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 3), size * offsetY, 0.f));
    this->m_modelWarehouse->createModel("03::letter_g11", "03::shader:phong", "res:letter_g", 0, ModelLetters::getLetterSize(ModelLetters::LETTER_P), glm::vec3(size), glm::vec3(0.f), glm::vec3(size * (offsetX + (ModelLetters::LETTER_SIZE.x + 1) * 4), size * offsetY, 0.f));
}

void SceneBuilderPlugin03::postProcess() {
    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 0.f, 11.f),
        glm::vec3(0.f, 0.f, -1.f));
}

void SceneBuilderPlugin03::addContextToScene() {
	// add lights to the scene
	this->m_scene->addLight("center_light", this->m_lightWarehouse->getLight("03::center_light"));
	this->m_scene->addLight("side_light",   this->m_lightWarehouse->getLight("03::side_light"));

	// add models to the scene
	this->m_scene->addModel("skybox", this->m_modelWarehouse->getModel("03::skybox"));

    this->m_scene->addModel("sphere01", this->m_modelWarehouse->getModel("03::sphere01"));
	this->m_scene->addModel("sphere02", this->m_modelWarehouse->getModel("03::sphere02"));
	this->m_scene->addModel("sphere03", this->m_modelWarehouse->getModel("03::sphere03"));
	this->m_scene->addModel("sphere04", this->m_modelWarehouse->getModel("03::sphere04"));
	
    this->m_scene->addModel("letter_L01", this->m_modelWarehouse->getModel("03::letter_L01"));
	this->m_scene->addModel("letter_a01", this->m_modelWarehouse->getModel("03::letter_a01"));
	this->m_scene->addModel("letter_m01", this->m_modelWarehouse->getModel("03::letter_m01"));
	this->m_scene->addModel("letter_b01", this->m_modelWarehouse->getModel("03::letter_b01"));
	this->m_scene->addModel("letter_e01", this->m_modelWarehouse->getModel("03::letter_e01"));
	this->m_scene->addModel("letter_r01", this->m_modelWarehouse->getModel("03::letter_r01"));
	this->m_scene->addModel("letter_t01", this->m_modelWarehouse->getModel("03::letter_t01"));
	this->m_scene->addModel("letter_i01", this->m_modelWarehouse->getModel("03::letter_i01"));
	this->m_scene->addModel("letter_a02", this->m_modelWarehouse->getModel("03::letter_a02"));
	this->m_scene->addModel("letter_n01", this->m_modelWarehouse->getModel("03::letter_n01"));

    this->m_scene->addModel("letter_P11", this->m_modelWarehouse->getModel("03::letter_P11"));
	this->m_scene->addModel("letter_h11", this->m_modelWarehouse->getModel("03::letter_h11"));
	this->m_scene->addModel("letter_o11", this->m_modelWarehouse->getModel("03::letter_o11"));
	this->m_scene->addModel("letter_n11", this->m_modelWarehouse->getModel("03::letter_n11"));
	this->m_scene->addModel("letter_g11", this->m_modelWarehouse->getModel("03::letter_g11"));
}
