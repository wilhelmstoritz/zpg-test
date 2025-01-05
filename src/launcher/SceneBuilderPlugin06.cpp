#include "SceneBuilderPlugin06.h"
#include "AppUtils.h"
#include "Config.h"
#include "Light.h"
#include "LightFlashlight.h"
#include "ModelFirefly.h"
#include "TransformationAnimationBezierCurve.h"
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
void SceneBuilderPlugin06::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("06::shader:texture", (this->m_shaderResourcesPath + "05/texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/texture.frag.glsl").c_str());

    this->m_shaderWarehouse->createShaderProgram("06::shader:phong",         (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/phong.frag.glsl"        ).c_str());
    this->m_shaderWarehouse->createShaderProgram("06::shader:phong_texture", (this->m_shaderResourcesPath + "05/normals-texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/phong-texture.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("06::shader:single_color",  (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/single-color.frag.glsl" ).c_str());
}

void SceneBuilderPlugin06::createLights() {
    Light* light;

    // moonlight
    glm::vec3 moonlight = glm::vec3(.827f, .871f, 1.f); // pale moonlight
    moonlight *= 0.001f; // dimmed moonlight

    light = this->m_lightWarehouse->createLight("06::moonlight", Light::LightTypeE::DIRECTIONAL, glm::vec3(0.f, 90.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(moonlight);
    light->setSpecularColor(moonlight);

    light = this->m_lightWarehouse->createLight("06::default_light", Light::LightTypeE::SPOT, glm::vec3(0.f, 90.f, 90.f));
    light->setDirection(glm::vec3(0.f, -1.f, -1.f));
    light->setSpotCutoffDegrees(30.f);
    //light->setDiffuseColor(moonlight);
    light->setDiffuseColor(glm::vec3(0.f, .3f, 0.f));
    light->setSpecularColor(moonlight);
    light->setAttenuation(glm::vec3(.1f, .01f, .001f));

    // gift spotlight
    light = this->m_lightWarehouse->createLight("06::gift_light", Light::LightTypeE::SPOT, glm::vec3(-50.f, 10.f, -50.f));
    light->setDirection(glm::vec3(-2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(1.f, 0.5f, 1.f));
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    light->setAttenuation(glm::vec3(1.f, .01f, .001f));

	// login spotlight
	light = this->m_lightWarehouse->createLight("06::login_light", Light::LightTypeE::SPOT, glm::vec3(30.f, 50.f, 30.f));
	light->setDirection(glm::vec3(-1.f, 0.f, -1.f));
	light->setSpotCutoffDegrees(30.f);
	light->setDiffuseColor(glm::vec3(1.f, 0.5f, 0.3f));
	light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
	light->setAttenuation(glm::vec3(.1f, .01f, .001f));
}

void SceneBuilderPlugin06::createModels() {
    Model* model;
    std::vector<GLsizei> numVerticesList;

    // skybox
    this->m_modelWarehouse->createModel(
        "06::skybox",
        "06::shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(this->m_size.x, this->m_size.y, this->m_size.z),
        glm::vec3(0.f),
        glm::vec3(this->m_min.x, this->m_min.y, this->m_min.z));

    this->m_modelWarehouse->createVertexResources("res:surface_texture", ModelLibrary::MODEL_SURFACE_TEXTURE, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL_TEXTURE);

    model = this->m_modelWarehouse->createModel(
        "06::surface",
        "06::shader:phong_texture", "res:surface_texture", 0, 6,
        glm::vec3(this->m_size.x / 2.f, this->m_size.z / 2.f, 1.f), glm::vec3(-90.f, 0.f, 0.f), glm::vec3(0.f, .1f, 0.f));
    model->setTextureID(0); // texture unit 0; grass

    /*// trees
	//this->m_modelWarehouse->createVertexResources("res:tree", sizeof(tree), tree, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); // old tree
	numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:tree", (this->m_modelResourcesPath + "tree.obj").c_str());
    //numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:tree", (this->m_modelResourcesPath + "tree.triangulated.obj").c_str());

    for (uint32_t i = 0; i < Config::ENVIRONMENT_TREES; ++i) {
        // random scale; between 0.5 and 1.5
		//float rnd = AppUtils::getInstance()->randomNumber(.5f, 1.5f); // old tree
        float rnd = AppUtils::getInstance()->randomNumber(.1f, .4f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppUtils::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float xRadius = 10.f;
		float zRadius = 20.f;

        float x = this->m_center.x, z = this->m_center.z;
        while (std::abs(this->m_center.x - x) < xRadius && std::abs(this->m_center.z - z) < zRadius) {
            x = AppUtils::getInstance()->randomNumber(this->m_min.x + this->m_size.x / 4.f, this->m_max.x - this->m_size.x / 4.f);
            z = AppUtils::getInstance()->randomNumber(this->m_min.z + this->m_size.z / 4.f, this->m_max.z - this->m_size.z / 4.f);
        }
        glm::vec3 position = glm::vec3(x, 0.f, z);

        model = this->m_modelWarehouse->createModel(
            "05:c:tree" + std::to_string(i),
			//"05:c:shader:phong", "res:tree", 0, 92814, // old tree
            "05:c:shader:phong_texture",
			"resobj:tree0", // vao
			"resobj:tree0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
            0, numVerticesList[0],
            scale, rotation, position);
        model->setTextureID(2); // texture unit 2; tree
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
            "05:c:bushes" + std::to_string(i),
            "05:c:shader:phong", "res:bushes", 0, 8730,
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

        auto shaderProgram = this->m_shaderWarehouse->getShaderProgram("05:c:shader:single_color");
        auto vao = this->m_modelWarehouse->getVAO("res:sphere");

        auto modelFf = std::make_unique<ModelFirefly>(shaderProgram, vao, 0, 2880);
        modelFf->getTransformation()->setTranslation(position);
        modelFf->getTransformation()->setRotationEulerAngles(glm::vec3(0.f));
        modelFf->getTransformation()->setScale(scale);
        this->m_modelWarehouse->addModel("05:c:firefly" + std::to_string(i), std::move(modelFf));

        //ModelFirefly* model = static_cast<ModelFirefly*>(this->m_modelWarehouse->getModel("05:c:firefly" + std::to_string(i)));
        model = this->m_modelWarehouse->getModel("05:c:firefly" + std::to_string(i));

        /*model = this->m_modelWarehouse->createModel(
            "05:c:firefly" + std::to_string(i),
            "05:c:shader:single_color", "res:sphere", 0, 2880,
            scale, glm::vec3(0.f), position);*/

        /*model->getTransformation()->updateTranslateStep(std::make_shared<TransformationAnimationRandomMove>(position));

        // --- firefly light source
        Light* light = this->m_lightWarehouse->createLight("05:c:firefly_light" + std::to_string(i), Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
        light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
        light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

        model->addObserver(light); // light source now follows the model
    }*/

    /*// gift
    this->m_modelWarehouse->createModel(
        "05:c:gift",
        "05:c:shader:phong", sizeof(gift), gift, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(this->m_min.x + 30.f, 4.f, this->m_min.z + 30.f));

    this->m_modelWarehouse->getModel("05:c:gift")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(.05f, .1f, .15f))); // all axis rotation*/

    /*// suzi
    this->m_modelWarehouse->createModel(
        "05:c:suziFlat",
        "05:c:shader:phong", sizeof(suziFlat), suziFlat, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x - 3.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));

    this->m_modelWarehouse->createModel(
        "05:c:suziSmooth",
        "05:c:shader:phong", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904,
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x + 3.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));

    this->m_modelWarehouse->getModel("05:c:suziFlat")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation
    this->m_modelWarehouse->getModel("05:c:suziSmooth")->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation*/

    /*// cubes
    float zCoord = this->m_center.z + this->m_size.z / 4.f + 3.f;

    this->m_modelWarehouse->createVertexResources("res:cube_texture", ModelLibrary::MODEL_CUBE_TEXTURE, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL_TEXTURE);

    model = this->m_modelWarehouse->createModel(
        "05:c:cube01",
        "05:c:shader:phong_texture", "res:cube_texture", 0, 36,
        glm::vec3(3.f), glm::vec3(0.f), glm::vec3(this->m_center.x - 11.5f, this->m_min.y, zCoord - 1.5f));
    model->setTextureID(1); // texture unit 1; wood

    model = this->m_modelWarehouse->createModel(
        "05:c:cube02",
        "05:c:shader:phong_texture", "res:cube_texture", 0, 36,
        glm::vec3(3.f), glm::vec3(0.f), glm::vec3(this->m_center.x + 8.5f, this->m_min.y, zCoord - 1.5f));
    model->setTextureID(1); // texture unit 1; wood*/

    /*// torches
    // --- torch01
    model = this->m_modelWarehouse->createModel(
        "05:c:torch01",
        "05:c:shader:single_color", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(this->m_center.x - 10.f, 4.5f, zCoord));
    model->setDiffuseColor(glm::vec3(.6f));

    Light* light = this->m_lightWarehouse->createLight("05:c:torchlight01", Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

    model->addObserver(light); // light source now follows the model

    // --- torch02
    model = this->m_modelWarehouse->createModel(
        "05:c:torch02",
        "05:c:shader:single_color", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880,
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(this->m_center.x + 10.f, 4.5f, zCoord));
    model->setDiffuseColor(glm::vec3(.6f));

    light = this->m_lightWarehouse->createLight("05:c:torchlight02", Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

    model->addObserver(light); // light source now follows the model*/

    /*// house
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:house", (this->m_modelResourcesPath + "house.obj").c_str());
    //numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:house", (this->m_modelResourcesPath + "house.triangulated.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "05:c:house",
		"05:c:shader:phong_texture",
		"resobj:house0", // vao
		"resobj:house0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(1.5f), glm::vec3(0.f, 10.f, 0.f), glm::vec3(this->m_center.x, this->m_min.y, this->m_center.z));
    model->setTextureID(3); // texture unit 3; house*/

	/*// zombie
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:zombie", (this->m_modelResourcesPath + "zombie.obj").c_str());
    //numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:zombie", (this->m_modelResourcesPath + "zombie.triangulated.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "05:c:zombie",
		"05:c:shader:phong_texture",
		"resobj:zombie0", // vao
		"resobj:zombie0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(1.5f), glm::vec3(0.f, -20.f, 0.f), glm::vec3(this->m_center.x - 4.f, this->m_min.y, this->m_center.z + 16.f));
    model->setTextureID(4); // texture unit 4; zombie

	//std::shared_ptr<TransformationAnimationRandomMove> animation = std::make_shared<TransformationAnimationRandomMove>(model->getTransformation()->getTranslateStep()->getTranslation());
    //model->getTransformation()->updateTranslateStep(animation);*/

    /*// login
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:login", (this->m_modelResourcesPath + "login.my.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "05:c:login",
		"05:c:shader:phong_texture",
		"resobj:login0", // vao
		//"resobj:login0", // ibo; if no ibo specified, the vao will be used for rendering
        0, numVerticesList[0],
        glm::vec3(10.f), glm::vec3(0.f), glm::vec3(this->m_center.x, 50.f, this->m_center.z));
    model->setTextureID(5); // texture unit 5; wooden fence

    model->getTransformation()->updateRotateStep(
        //std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.01f, .05f, 0.01f))); // all axis rotation
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, .05f, 0.f))); // y axis rotation*/

    // fireball
    // --- fireball model
    this->m_modelWarehouse->createVertexResources("res:sphere", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    auto shaderProgram = this->m_shaderWarehouse->getShaderProgram("06::shader:single_color");
    auto vao = this->m_modelWarehouse->getVAO("res:sphere");

    auto modelFb = std::make_unique<ModelFirefly>(shaderProgram, vao, 0, 2880);
    //modelFb->getTransformation()->setTranslation(position);
    //modelFb->getTransformation()->setRotationEulerAngles(glm::vec3(0.f));
    //modelFb->getTransformation()->setScale(scale);
    this->m_modelWarehouse->addModel("06::fireball", std::move(modelFb));

    //ModelFirefly* model = static_cast<ModelFirefly*>(this->m_modelWarehouse->getModel("06::fireball"));
    model = this->m_modelWarehouse->getModel("06::fireball");

    glm::vec3 bezierStart = glm::vec3(0.f);
	std::vector<glm::vec3> bezierControlPoints = { glm::vec3(25.f) };
	std::vector<glm::vec3> bezierControlVectors = { glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 1.f, 0.f) };
    //std::vector<glm::vec3> bezierControlPoints;
	glm::vec3 bezierEnd = glm::vec3(50.f, 0.f, 50.f);

    model->getTransformation()->updateTranslateStep(
        std::make_shared<TransformationAnimationBezierCurve>(
            bezierStart, bezierEnd,
            bezierControlPoints,
			//bezierControlVectors,
            5.f));

    // --- fireball light source
    Light* light = this->m_lightWarehouse->createLight("06::fireball_light", Light::LightTypeE::POINT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    //light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));
    light->setAttenuation(glm::vec3(1.f, .0f, .0f));

    model->addObserver(light); // light source now follows the model
}

void SceneBuilderPlugin06::loadTextures() {
    this->m_textureWarehouse->loadTexture("tex:grass",        (this->m_textureResourcesPath + "grass.png"        ).c_str(), GL_TEXTURE0);
    this->m_textureWarehouse->loadTexture("tex:wood",         (this->m_textureResourcesPath + "test.png"         ).c_str(), GL_TEXTURE1);
    this->m_textureWarehouse->loadTexture("tex:tree",         (this->m_textureResourcesPath + "tree.png"         ).c_str(), GL_TEXTURE2);
    this->m_textureWarehouse->loadTexture("tex:house",        (this->m_textureResourcesPath + "house.png"        ).c_str(), GL_TEXTURE3);
    this->m_textureWarehouse->loadTexture("tex:zombie",       (this->m_textureResourcesPath + "zombie.png"       ).c_str(), GL_TEXTURE4);
    this->m_textureWarehouse->loadTexture("tex:wooden_fence", (this->m_textureResourcesPath + "wooden_fence.png" ).c_str(), GL_TEXTURE5);
}

void SceneBuilderPlugin06::postProcess() {
    // camera position & flashlight
    this->m_scene->getCamera()->setPosition(
        glm::vec3(this->m_center.x, Config::CAMERA_HEIGHT, this->m_center.z + this->m_size.z / 4.f + 11.f),
        glm::vec3(0.f, 0.f, -1.f));

    this->m_lightWarehouse->createFlashlight("06::flashlight", this->m_scene->getCamera());
}

void SceneBuilderPlugin06::addContextToScene() {
    // add lights to the scene
    this->m_scene->addLight("moonlight",     this->m_lightWarehouse->getLight("06::moonlight"));
    this->m_scene->addLight("default_light", this->m_lightWarehouse->getLight("06::default_light"));
    this->m_scene->addLight("gift_light",    this->m_lightWarehouse->getLight("06::gift_light"));
	this->m_scene->addLight("login_light",   this->m_lightWarehouse->getLight("06::login_light"));

    this->m_scene->addLight("flashlight",    this->m_lightWarehouse->getLight("06::flashlight"));

    // add models and lights to the scene
	this->m_scene->addModel("skybox",  this->m_modelWarehouse->getModel("06::skybox"));
	this->m_scene->addModel("surface", this->m_modelWarehouse->getModel("06::surface"));

	/*for (uint32_t i = 0; i < Config::ENVIRONMENT_TREES; ++i)
		this->m_scene->addModel("tree"   + std::to_string(i), this->m_modelWarehouse->getModel("05:c:tree"   + std::to_string(i)));*/
	/*for (uint32_t i = 0; i < Config::ENVIRONMENT_BUSHES; ++i)
		this->m_scene->addModel("bushes" + std::to_string(i), this->m_modelWarehouse->getModel("05:c:bushes" + std::to_string(i)));*/
	/*for (uint32_t i = 0; i < Config::ENVIRONMENT_FIREFLIES; ++i) {
		this->m_scene->addModel("firefly"       + std::to_string(i), this->m_modelWarehouse->getModel("05:c:firefly"       + std::to_string(i)));
		this->m_scene->addLight("firefly_light" + std::to_string(i), this->m_lightWarehouse->getLight("05:c:firefly_light" + std::to_string(i)));
	}*/

    //this->m_scene->addModel("gift",       this->m_modelWarehouse->getModel("05:c:gift"));
	//this->m_scene->addModel("suziFlat",   this->m_modelWarehouse->getModel("05:c:suziFlat"));
	//this->m_scene->addModel("suziSmooth", this->m_modelWarehouse->getModel("05:c:suziSmooth"));
	//this->m_scene->addModel("cube01",     this->m_modelWarehouse->getModel("05:c:cube01"));
	//this->m_scene->addModel("cube02",     this->m_modelWarehouse->getModel("05:c:cube02"));

    //this->m_scene->addModel("torch01",      this->m_modelWarehouse->getModel("05:c:torch01"));
	//this->m_scene->addModel("torch02",      this->m_modelWarehouse->getModel("05:c:torch02"));
	//this->m_scene->addLight("torchlight01", this->m_lightWarehouse->getLight("05:c:torchlight01"));
	//this->m_scene->addLight("torchlight02", this->m_lightWarehouse->getLight("05:c:torchlight02"));

    //this->m_scene->addModel("house",  this->m_modelWarehouse->getModel("05:c:house"));
	//this->m_scene->addModel("zombie", this->m_modelWarehouse->getModel("05:c:zombie"));
	//this->m_scene->addModel("login",  this->m_modelWarehouse->getModel("05:c:login"));

    this->m_scene->addModel("fireball",       this->m_modelWarehouse->getModel("06::fireball"));
    this->m_scene->addLight("fireball_light", this->m_lightWarehouse->getLight("06::fireball_light"));
}
