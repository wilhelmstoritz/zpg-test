#include "SceneBuilderPlugin04.h"
#include "AppMath.h"
#include "Config.h"
#include "Light.h"
#include "LightFlashlight.h"
#include "Model.h"
#include "ModelLightEmitting.h"
#include "ModelFirefly.h"
#include "TransformationAnimationRandomMove.h"
#include "TransformationAnimationRotate.h"

#include "ModelLibrary.h"
#include "tree.h"
#include "bushes.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "gift.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPlugin04::setSceneProperties(Scene* t_scene) {
    t_scene->setTitle("5 | " + t_scene->getTitle());
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin04::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("04::shader:lambertian",   (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/lambertian.frag.glsl"  ).c_str());
    this->m_shaderWarehouse->createShaderProgram("04::shader:phong",        (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/phong.frag.glsl"       ).c_str());
    this->m_shaderWarehouse->createShaderProgram("04::shader:single_color", (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/single-color.frag.glsl").c_str());
}

void SceneBuilderPlugin04::createLights() {
    Light* light;

    // moonlight
	glm::vec3 moonlight = glm::vec3(.827f, .871f, 1.f); // pale moonlight
	moonlight *= 0.001f; // dimmed moonlight

    light = this->m_lightWarehouse->createLight("04::moonlight", Light::lightTypeE::DIRECTIONAL_LIGHT, glm::vec3(0.f, 90.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(moonlight);
    light->setSpecularColor(moonlight);

	light = this->m_lightWarehouse->createLight("04::default_light", Light::lightTypeE::SPOT_LIGHT, glm::vec3(0.f, 90.f, 90.f));
    light->setDirection(glm::vec3(0.f, -1.f, -1.f));
    light->setSpotCutoffDegrees(30.f);
	//light->setDiffuseColor(moonlight);
	light->setDiffuseColor(glm::vec3(0.f, .3f, 0.f));
    light->setSpecularColor(moonlight);
    light->setAttenuation(glm::vec3(.1f, .01f, .001f));

	// gift spotlight
	light = this->m_lightWarehouse->createLight("04::gift_light", Light::lightTypeE::SPOT_LIGHT, glm::vec3(-50.f, 10.f, -50.f));
    light->setDirection(glm::vec3(-2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(1.f, 0.5f, 1.f));
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    light->setAttenuation(glm::vec3(1.f, .01f, .001f));
}

void SceneBuilderPlugin04::createModels() {
    // skybox
    this->m_modelWarehouse->createModel(
        "04::skybox",
        //"04::shader:lambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        "04::shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(this->m_size.x, this->m_size.y, this->m_size.z),
        glm::vec3(0.f),
        glm::vec3(this->m_min.x, this->m_min.y, this->m_min.z));

    // trees
    this->m_modelWarehouse->createVertexResources("res:tree", sizeof(tree), tree, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (size_t i = 0; i < Config::ENVIRONMENT_TREES; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = AppMath::getInstance()->randomNumber(.5f, 1.5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppMath::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float x = AppMath::getInstance()->randomNumber(this->m_min.x + this->m_size.x / 4.f, this->m_max.x - this->m_size.x / 4.f);
        float z = AppMath::getInstance()->randomNumber(this->m_min.z + this->m_size.z / 4.f, this->m_max.z - this->m_size.z / 4.f);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        this->m_modelWarehouse->createModel(
            "04::tree" + std::to_string(i),
            "04::shader:phong", "res:tree", 0, 92814,
            scale, rotation, position);
    }

    // bushes
    this->m_modelWarehouse->createVertexResources("res:bushes", sizeof(bushes), bushes, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (size_t i = 0; i < Config::ENVIRONMENT_BUSHES; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = AppMath::getInstance()->randomNumber(.5f, 1.5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppMath::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        //float x = AppMath::getInstance()->randomNumber(this->m_min.x, this->m_max.x);
        //float z = AppMath::getInstance()->randomNumber(this->m_min.z, this->m_max.z);
        float x = AppMath::getInstance()->randomNumber(this->m_min.x + this->m_size.x / 4.f, this->m_max.x - this->m_size.x / 4.f);
        float z = AppMath::getInstance()->randomNumber(this->m_min.z + this->m_size.z / 4.f, this->m_max.z - this->m_size.z / 4.f);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        this->m_modelWarehouse->createModel(
            "04::bushes" + std::to_string(i),
            "04::shader:phong", "res:bushes", 0, 8730,
            scale, rotation, position);
    }

    // fireflies
    this->m_modelWarehouse->createVertexResources("res:sphere", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (size_t i = 0; i < Config::ENVIRONMENT_FIREFLIES; ++i) {
        // --- firefly model
        // random scale; between 0.01 and 0.03
        float rnd = AppMath::getInstance()->randomNumber(.01f, .03f);
        glm::vec3 scale = glm::vec3(rnd);

        // random position in the area
        float x = AppMath::getInstance()->randomNumber(this->m_min.x + this->m_size.x / 4.f, this->m_max.x - this->m_size.x / 4.f);
        float y = AppMath::getInstance()->randomNumber(0.1f, 3.f);
        float z = AppMath::getInstance()->randomNumber(this->m_min.z + this->m_size.z / 4.f, this->m_max.z - this->m_size.z / 4.f);
        glm::vec3 position = glm::vec3(x, y, z);
        //position = glm::vec3(this->m_center.x, 2.f, this->m_center.z + this->m_size.z / 4.f + 6.f); // testing purposes

		// obsolete approach; replaced by ModelWarehouse::createModel specialization
        auto shaderProgram = this->m_shaderWarehouse->getShaderProgram("04::shader:single_color");
        auto vao = this->m_modelWarehouse->getVAO("res:sphere");

        auto modelFf = std::make_unique<ModelFirefly>(shaderProgram, vao, 0, 2880);
        this->m_modelWarehouse->addModel("04::firefly" + std::to_string(i), std::move(modelFf));

        ModelFirefly* model = static_cast<ModelFirefly*>(this->m_modelWarehouse->getModel("04::firefly" + std::to_string(i)));
        //model->getTransformation()->setTranslation(position);
        model->getTransformation()->setScale(scale);

		/* new approach using specialized ModelWarehouse::createModel
        auto model = this->m_modelWarehouse->createModel<ModelFirefly>(
            "04::firefly" + std::to_string(i),
            "04::shader:single_color", "res:sphere", 0, 2880,
            scale, glm::vec3(0.f), position);*/
        model->getTransformation()->updateTranslateStep(std::make_shared<TransformationAnimationRandomMove>(position));

        // --- firefly light source
		Light* light = this->m_lightWarehouse->createLight("04::firefly_light" + std::to_string(i), Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f)); // no need to set position; it will follow the model
        light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

        model->addObserver(light); // light source now follows the model
    }

    // gift
    this->m_modelWarehouse->createModel(
        "04::gift",
        "04::shader:phong", sizeof(gift), gift, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(this->m_min.x + 30.f, 4.f, this->m_min.z + 30.f));

    this->m_modelWarehouse->getModel("04::gift")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(.05f, .1f, .15f))); // all axis rotation

    // suzi
    this->m_modelWarehouse->createModel(
        "04::suziFlat",
        "04::shader:phong", sizeof(suziFlat), suziFlat, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x - 3.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));

    this->m_modelWarehouse->createModel(
        "04::suziSmooth",
        "04::shader:phong", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x + 3.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));

    this->m_modelWarehouse->getModel("04::suziFlat")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f,  .05f, 0.f))); // 20 seconds for a full rotation
    this->m_modelWarehouse->getModel("04::suziSmooth")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation

    // torches
    // --- torch 01
    auto model = this->m_modelWarehouse->createModel<ModelLightEmitting>(
        "04::torch01",
        "04::shader:single_color", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(this->m_center.x - 6.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));
    model->setDiffuseColor(glm::vec3(.6f));
    model->setSpecularColor(glm::vec3(.6f, .6f, .6f));

	Light* light = this->m_lightWarehouse->createLight("04::torchlight01", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setAttenuation(glm::vec3(1.f, .1f, .01f));

    model->addObserver(light); // light source now follows the model

    // --- torch 02
    model = this->m_modelWarehouse->createModel<ModelLightEmitting>(
        "04::torch02",
        "04::shader:single_color", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(this->m_center.x + 6.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));
    model->setDiffuseColor(glm::vec3(.6f));
    model->setSpecularColor(glm::vec3(.6f, .6f, .6f));

	light = this->m_lightWarehouse->createLight("04::torchlight02", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setAttenuation(glm::vec3(1.f, .1f, .01f));

    model->addObserver(light); // light source now follows the model
}

void SceneBuilderPlugin04::postProcess() {
    // camera position & flashlight
    this->m_scene->getCamera()->setPosition(
        glm::vec3(this->m_center.x, Config::CAMERA_HEIGHT, this->m_center.z + this->m_size.z / 4.f + 11.f),
        glm::vec3(0.f, 0.f, -1.f));

	this->m_lightWarehouse->createFlashlight("04::flashlight", this->m_scene->getCamera());
}

void SceneBuilderPlugin04::addContextToScene() {
	// add lights to the scene
	this->m_scene->addLight("moonlight",     this->m_lightWarehouse->getLight("04::moonlight"));
	this->m_scene->addLight("default_light", this->m_lightWarehouse->getLight("04::default_light"));
	this->m_scene->addLight("gift_light",    this->m_lightWarehouse->getLight("04::gift_light"));

	this->m_scene->addLight("flashlight",    this->m_lightWarehouse->getLight("04::flashlight"));

    // add models and lights to the scene
	this->m_scene->addModel("skybox", this->m_modelWarehouse->getModel("04::skybox"));

    for (size_t i = 0; i < Config::ENVIRONMENT_TREES;  ++i)
		this->m_scene->addModel("tree"   + std::to_string(i), this->m_modelWarehouse->getModel("04::tree"   + std::to_string(i)));
	for (size_t i = 0; i < Config::ENVIRONMENT_BUSHES; ++i)
		this->m_scene->addModel("bushes" + std::to_string(i), this->m_modelWarehouse->getModel("04::bushes" + std::to_string(i)));
	for (size_t i = 0; i < Config::ENVIRONMENT_FIREFLIES; ++i) {
		this->m_scene->addModel("firefly"       + std::to_string(i), this->m_modelWarehouse->getModel("04::firefly"       + std::to_string(i)));
		this->m_scene->addLight("firefly_light" + std::to_string(i), this->m_lightWarehouse->getLight("04::firefly_light" + std::to_string(i)));
	}

    this->m_scene->addModel("gift",       this->m_modelWarehouse->getModel("04::gift"));
    this->m_scene->addModel("suziFlat",   this->m_modelWarehouse->getModel("04::suziFlat"));
	this->m_scene->addModel("suziSmooth", this->m_modelWarehouse->getModel("04::suziSmooth"));

    this->m_scene->addModel("torch01",      this->m_modelWarehouse->getModel("04::torch01"));
    this->m_scene->addModel("torch02",      this->m_modelWarehouse->getModel("04::torch02"));
    this->m_scene->addLight("torchlight01", this->m_lightWarehouse->getLight("04::torchlight01"));
    this->m_scene->addLight("torchlight02", this->m_lightWarehouse->getLight("04::torchlight02"));
}
