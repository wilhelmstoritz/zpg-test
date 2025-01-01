#include "SceneBuilderPlugin05a.h"
#include "AppUtils.h"
#include "Config.h"
#include "Light.h"
#include "LightFlashlight.h"
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

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin05a::preProcess() {
    // scene size
    this->m_scene->setSize(
        glm::vec3(Config::SKYBOX_XMIN, Config::SKYBOX_YMIN_VIRTUALWORLDSCENE, Config::SKYBOX_ZMIN),
        glm::vec3(Config::SKYBOX_XMAX, Config::SKYBOX_YMAX, Config::SKYBOX_ZMAX));

    this->setEnvironment();
}

void SceneBuilderPlugin05a::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("05:a:shader:texture", (this->m_shaderResourcesPath + "05/texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/texture.frag.glsl").c_str());

    this->m_shaderWarehouse->createShaderProgram("05:a:shader:phong",         (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/phong.frag.glsl"        ).c_str());
    this->m_shaderWarehouse->createShaderProgram("05:a:shader:phong_texture", (this->m_shaderResourcesPath + "05/normals-texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/phong-texture.frag.glsl").c_str());
    //this->m_shaderWarehouse->createShaderProgram("05:a:shader:single_color",  (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/single-color.frag.glsl" ).c_str());
}

void SceneBuilderPlugin05a::createLights() {
    Light* light;

    // moonlight
    glm::vec3 moonlight = glm::vec3(.827f, .871f, 1.f); // pale moonlight
    moonlight *= 0.001f; // dimmed moonlight

    /*light = this->m_lightWarehouse->createLight("05:a:moonlight", Light::LightTypeE::DIRECTIONAL, glm::vec3(0.f, 90.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(moonlight);
    light->setSpecularColor(moonlight);*/

    light = this->m_lightWarehouse->createLight("05:a:default_light", Light::LightTypeE::POINT, glm::vec3(0.f, 99.f, 0.f));
    //light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(30.f);
    //light->setDiffuseColor(moonlight);
    //light->setDiffuseColor(glm::vec3(0.f, .3f, 0.f));
        light->setDiffuseColor(glm::vec3(1.f, 1.f, 1.f));
    light->setSpecularColor(moonlight);
    //light->setAttenuation(glm::vec3(.1f, .01f, .001f));
        light->setAttenuation(glm::vec3(.1f, .001f, .0001f));

    /*// gift spotlight
    light = this->m_lightWarehouse->createLight("05:a:gift_light", Light::LightTypeE::SPOT, glm::vec3(-50.f, 10.f, -50.f));
    light->setDirection(glm::vec3(-2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(1.f, 0.5f, 1.f));
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    light->setAttenuation(glm::vec3(1.f, .01f, .001f));*/
}

void SceneBuilderPlugin05a::createModels() {
	Model* model;

    // skybox
    this->m_modelWarehouse->createModel(
        "05:a:skybox",
        "05:a:shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(this->m_size.x, this->m_size.y, this->m_size.z),
        glm::vec3(0.f),
        glm::vec3(this->m_min.x, this->m_min.y, this->m_min.z));

    /*this->m_modelWarehouse->createVertexResources("res:surface_texture", ModelLibrary::MODEL_SURFACE_TEXTURE, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL_TEXTURE);

    model = this->m_modelWarehouse->createModel(
        "05:a:surface",
        "05:a:shader:phong_texture", "res:surface_texture", 0, 6,
        glm::vec3(this->m_size.x / 2.f, this->m_size.z / 2.f, 1.f), glm::vec3(-90.f, 0.f, 0.f), glm::vec3(0.f, .1f, 0.f));
    model->setTextureID(0); // texture unit 0; grass*/

    /*// trees
    this->m_modelWarehouse->createVertexResources("res:tree", sizeof(tree), tree, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (uint32_t i = 0; i < Config::ENVIRONMENT_TREES; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = AppUtils::getInstance()->randomNumber(.5f, 1.5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppUtils::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float x = AppUtils::getInstance()->randomNumber(this->m_min.x + this->m_size.x / 4.f, this->m_max.x - this->m_size.x / 4.f);
        float z = AppUtils::getInstance()->randomNumber(this->m_min.z + this->m_size.z / 4.f, this->m_max.z - this->m_size.z / 4.f);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        model = this->m_modelWarehouse->createModel(
            "05:a:tree" + std::to_string(i),
            "05:a:shader:phong", "res:tree", 0, 92814,
            scale, rotation, position);
    }*/

    /*// bushes
    this->m_modelWarehouse->createVertexResources("res:bushes", sizeof(bushes), bushes, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (uint32_t i = 0; i < Config::ENVIRONMENT_BUSHES; ++i) {
        // random scale; between 0.5 and 1.5
        float rnd = AppUtils::getInstance()->randomNumber(.5f, 1.5f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppUtils::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        //float x = AppUtils::getInstance()->randomNumber(this->m_min.x, this->m_max.x);
        //float z = AppUtils::getInstance()->randomNumber(this->m_min.z, this->m_max.z);
        float x = AppUtils::getInstance()->randomNumber(this->m_min.x + this->m_size.x / 4.f, this->m_max.x - this->m_size.x / 4.f);
        float z = AppUtils::getInstance()->randomNumber(this->m_min.z + this->m_size.z / 4.f, this->m_max.z - this->m_size.z / 4.f);
        glm::vec3 position = glm::vec3(x, 0.f, z);

        model = this->m_modelWarehouse->createModel(
            "05:a:bushes" + std::to_string(i),
            "05:a:shader:phong", "res:bushes", 0, 8730,
            scale, rotation, position);
    }*/

    /*// fireflies
    this->m_modelWarehouse->createVertexResources("res:sphere", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    for (uint32_t i = 0; i < Config::ENVIRONMENT_FIREFLIES; ++i) {
        // --- firefly model
        // random scale; between 0.01 and 0.03
        float rnd = AppUtils::getInstance()->randomNumber(.01f, .03f);
        glm::vec3 scale = glm::vec3(rnd);

        // random position in the area
        float x = AppUtils::getInstance()->randomNumber(this->m_min.x + this->m_size.x / 4.f, this->m_max.x - this->m_size.x / 4.f);
        float y = AppUtils::getInstance()->randomNumber(0.1f, 3.f);
        float z = AppUtils::getInstance()->randomNumber(this->m_min.z + this->m_size.z / 4.f, this->m_max.z - this->m_size.z / 4.f);
        glm::vec3 position = glm::vec3(x, y, z);
        //position = glm::vec3(this->m_center.x, 2.f, this->m_center.z + this->m_size.z / 4.f + 6.f); // testing purposes

        auto shaderProgram = this->m_shaderWarehouse->getShaderProgram("05:a:shader:single_color");
        auto vao = this->m_modelWarehouse->getVAO("res:sphere");

        auto modelFf = std::make_unique<ModelFirefly>(shaderProgram, vao, 0, 2880);
        modelFf->getTransformation()->setTranslation(position);
        modelFf->getTransformation()->setRotationEulerAngles(glm::vec3(0.f));
        modelFf->getTransformation()->setScale(scale);
        this->m_modelWarehouse->addModel("05:a:firefly" + std::to_string(i), std::move(modelFf));

        //ModelFirefly* model = static_cast<ModelFirefly*>(this->m_modelWarehouse->getModel("05:a:firefly" + std::to_string(i)));
        model = this->m_modelWarehouse->getModel("05:a:firefly" + std::to_string(i));

        /*model = this->m_modelWarehouse->createModel(
            "05:a:firefly" + std::to_string(i),
            "05:a:shader:single_color", "res:sphere", 0, 2880,
            scale, glm::vec3(0.f), position);*/

        /*model->getTransformation()->updateTranslateStep(std::make_shared<TransformationAnimationRandomMove>(position));

        // --- firefly light source
        Light* light = this->m_lightWarehouse->createLight("05:a:firefly_light" + std::to_string(i), Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
        light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
        light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

        model->addObserver(light); // light source now follows the model
	}*/

    /*// gift
    this->m_modelWarehouse->createModel(
        "05:a:gift",
        "05:a:shader:phong", sizeof(gift), gift, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(this->m_min.x + 30.f, 4.f, this->m_min.z + 30.f));

    this->m_modelWarehouse->getModel("05:a:gift")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(.05f, .1f, .15f))); // all axis rotation*/

    /*// suzi
    this->m_modelWarehouse->createModel(
        "05:a:suziFlat",
        "05:a:shader:phong", sizeof(suziFlat), suziFlat, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x - 3.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));

    this->m_modelWarehouse->createModel(
        "05:a:suziSmooth",
        "05:a:shader:phong", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x + 3.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));

    this->m_modelWarehouse->getModel("05:a:suziFlat")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation
    this->m_modelWarehouse->getModel("05:a:suziSmooth")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation*/

    // cubes
    float zCoord = this->m_center.z + this->m_size.z / 4.f;

    this->m_modelWarehouse->createVertexResources("res:cube_texture", ModelLibrary::MODEL_CUBE_TEXTURE, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL_TEXTURE);

    model = this->m_modelWarehouse->createModel(
        "05:a:cube01",
        //"05:a:shader:phong_texture", "res:cube_texture", 0, 36,
        "05:a:shader:texture", "res:cube_texture", 0, 36,
        glm::vec3(3.f), glm::vec3(0.f), glm::vec3(this->m_center.x - 11.5f, this->m_center.y, zCoord));
    model->setTextureID(1); // texture unit 1; wood

    model = this->m_modelWarehouse->createModel(
        "05:a:cube02",
        //"05:a:shader:phong_texture", "res:cube_texture", 0, 36,
        "05:a:shader:texture", "res:cube_texture", 0, 36,
        glm::vec3(3.f), glm::vec3(0.f), glm::vec3(this->m_center.x + 8.5f, this->m_center.y, zCoord));
    model->setTextureID(2); // texture unit 2; woodstone

    /*// torches
    // --- torch01
    model = this->m_modelWarehouse->createModel(
        "05:a:torch01",
        "05:a:shader:single_color", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(this->m_center.x - 10.f, 4.5f, zCoord));
    model->setDiffuseColor(glm::vec3(.6f));

    Light* light = this->m_lightWarehouse->createLight("05:a:torchlight01", Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

    model->addObserver(light); // light source now follows the model

    // --- torch02
    model = this->m_modelWarehouse->createModel(
        "05:a:torch02",
        "05:a:shader:single_color", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(this->m_center.x + 10.f, 4.5f, zCoord));
    model->setDiffuseColor(glm::vec3(.6f));

    light = this->m_lightWarehouse->createLight("05:a:torchlight02", Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

    model->addObserver(light); // light source now follows the model*/
}

void SceneBuilderPlugin05a::loadTextures() {
	//this->m_textureWarehouse->loadTexture("tex:grass",     (this->m_textureResourcesPath + "grass.png"        ).c_str(), GL_TEXTURE0);
	this->m_textureWarehouse->loadTexture("tex:wood",      (this->m_textureResourcesPath + "test.png"         ).c_str(), GL_TEXTURE1);
    this->m_textureWarehouse->loadTexture("tex:woodstone", (this->m_textureResourcesPath + "woodstone.3rd.jpg").c_str(), GL_TEXTURE2);

    this->m_textureWarehouse->loadTexture("tex:cubemap",
        (this->m_textureResourcesPath + "cubemap/posx.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/negx.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/posy.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/negy.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/posz.jpg").c_str(),
        (this->m_textureResourcesPath + "cubemap/negz.jpg").c_str(),
        GL_TEXTURE3);
}

void SceneBuilderPlugin05a::postProcess() {
    // camera position & flashlight
    this->m_scene->getCamera()->setPosition(
        glm::vec3(this->m_center.x, Config::CAMERA_HEIGHT, this->m_center.z + this->m_size.z / 4.f + 11.f),
        glm::vec3(0.f, 0.f, -1.f));

    this->m_lightWarehouse->createFlashlight("05:a:flashlight", this->m_scene->getCamera());
}

void SceneBuilderPlugin05a::addContextToScene() {
    // add lights to the scene
    //this->m_scene->addLight("moonlight",     this->m_lightWarehouse->getLight("05:a:moonlight"));
    this->m_scene->addLight("default_light", this->m_lightWarehouse->getLight("05:a:default_light"));
    //this->m_scene->addLight("gift_light",    this->m_lightWarehouse->getLight("05:a:gift_light"));

    this->m_scene->addLight("flashlight",    this->m_lightWarehouse->getLight("05:a:flashlight"));

    // add models and lights to the scene
	this->m_scene->addModel("skybox", this->m_modelWarehouse->getModel("05:a:skybox"));
	//this->m_scene->addModel("surface", this->m_modelWarehouse->getModel("05:a:surface"));

    /*for (uint32_t i = 0; i < Config::ENVIRONMENT_TREES; ++i)
		this->m_scene->addModel("tree"   + std::to_string(i), this->m_modelWarehouse->getModel("05:a:tree"   + std::to_string(i)));*/
	/*for (uint32_t i = 0; i < Config::ENVIRONMENT_BUSHES; ++i)
		this->m_scene->addModel("bushes" + std::to_string(i), this->m_modelWarehouse->getModel("05:a:bushes" + std::to_string(i)));*/
	/*for (uint32_t i = 0; i < Config::ENVIRONMENT_FIREFLIES; ++i) {
		this->m_scene->addModel("firefly"       + std::to_string(i), this->m_modelWarehouse->getModel("05:a:firefly"       + std::to_string(i)));
		this->m_scene->addLight("firefly_light" + std::to_string(i), this->m_lightWarehouse->getLight("05:a:firefly_light" + std::to_string(i)));
	}*/

    //this->m_scene->addModel("gift",       this->m_modelWarehouse->getModel("05:a:gift"));
	//this->m_scene->addModel("suziFlat",   this->m_modelWarehouse->getModel("05:a:suziFlat"));
	//this->m_scene->addModel("suziSmooth", this->m_modelWarehouse->getModel("05:a:suziSmooth"));
	this->m_scene->addModel("cube01",     this->m_modelWarehouse->getModel("05:a:cube01"));
	this->m_scene->addModel("cube02",     this->m_modelWarehouse->getModel("05:a:cube02"));

    //this->m_scene->addModel("torch01",      this->m_modelWarehouse->getModel("05:a:torch01"));
	//this->m_scene->addModel("torch02",      this->m_modelWarehouse->getModel("05:a:torch02"));
	//this->m_scene->addLight("torchlight01", this->m_lightWarehouse->getLight("05:a:torchlight01"));
	//this->m_scene->addLight("torchlight02", this->m_lightWarehouse->getLight("05:a:torchlight02"));
}
