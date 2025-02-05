#include "SceneBuilderPlugin06.h"
#include "AppMath.h"
#include "Config.h"
#include "Light.h"
#include "LightFlashlight.h"
#include "Model.h"
#include "ModelLightEmitting.h"
#include "ModelFireball.h"
#include "ModelFirefly.h"
#include "TransformationAnimationBezierCurve.h"
#include "TransformationAnimationRandomMove.h"
#include "TransformationAnimationRotate.h"

#include "ModelLibrary.h"
#include "tree.h"
#include "bushes.h"
#include "sphere.h"
#include "gift.h"

// standard c++ libraries
#include <vector>
#include <utility>

// --- public ------------------------------------------------------------------
void SceneBuilderPlugin06::setSceneProperties(Scene* t_scene) {
    t_scene->setTitle("9 | " + t_scene->getTitle());
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin06::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("06::shader:texture",       (this->m_shaderResourcesPath + "05/texture.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/texture.frag.glsl"      ).c_str());

    this->m_shaderWarehouse->createShaderProgram("06::shader:phong",         (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/phong.frag.glsl"        ).c_str());
    this->m_shaderWarehouse->createShaderProgram("06::shader:phong_texture", (this->m_shaderResourcesPath + "05/normals-texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/phong-texture.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("06::shader:single_color",  (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/single-color.frag.glsl" ).c_str());
}

void SceneBuilderPlugin06::createLights() {
    Light* light;

    // moonlight
    glm::vec3 moonlight = glm::vec3(.827f, .871f, 1.f); // pale moonlight
    moonlight *= 0.001f; // dimmed moonlight

    light = this->m_lightWarehouse->createLight("06::moonlight", Light::lightTypeE::DIRECTIONAL_LIGHT, glm::vec3(0.f, 90.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(moonlight);
    light->setSpecularColor(moonlight);

    light = this->m_lightWarehouse->createLight("06::default_light", Light::lightTypeE::SPOT_LIGHT, glm::vec3(0.f, 90.f, 90.f));
    light->setDirection(glm::vec3(0.f, -1.f, -1.f));
    light->setSpotCutoffDegrees(30.f);
    //light->setDiffuseColor(moonlight);
    light->setDiffuseColor(glm::vec3(0.f, .3f, 0.f));
    light->setSpecularColor(moonlight);
    light->setAttenuation(glm::vec3(.1f, .01f, .001f));

    // gift spotlight
    light = this->m_lightWarehouse->createLight("06::gift_light", Light::lightTypeE::SPOT_LIGHT, glm::vec3(-50.f, 10.f, -50.f));
    light->setDirection(glm::vec3(-2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(1.f, 0.5f, 1.f));
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
    light->setAttenuation(glm::vec3(1.f, .01f, .001f));

	// login spotlight
	light = this->m_lightWarehouse->createLight("06::login_light", Light::lightTypeE::SPOT_LIGHT, glm::vec3(30.f, 50.f, 30.f));
	light->setDirection(glm::vec3(-1.f, 0.f, -1.f));
	light->setSpotCutoffDegrees(30.f);
    light->setDiffuseColor(glm::vec3(.9f, 1.f, .1f));
	light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f));
	light->setAttenuation(glm::vec3(.1f, .01f, .001f));
}

void SceneBuilderPlugin06::createModels() {
	Light* light;
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

    // trees
	//this->m_modelWarehouse->createVertexResources("res:tree", sizeof(tree), tree, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL); // old tree
	numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:tree", (this->m_modelResourcesPath + "tree.obj").c_str());
    //numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:tree", (this->m_modelResourcesPath + "tree.triangulated.obj").c_str());

    for (size_t i = 0; i < Config::ENVIRONMENT_TREES; ++i) {
        // random scale; between 0.5 and 1.5
		//float rnd = AppMath::getInstance()->randomNumber(.5f, 1.5f); // old tree
        float rnd = AppMath::getInstance()->randomNumber(.1f, .4f);
        glm::vec3 scale = glm::vec3(rnd);

        // random angle; between 0 and 360
        rnd = AppMath::getInstance()->randomNumber(0.f, 360.f);
        glm::vec3 rotation = glm::vec3(0.f, rnd, 0.f);

        // random position in the area
        float xRadius = 10.f;
		float zRadius = 20.f;

        float x = this->m_center.x, z = this->m_center.z;
        while (std::abs(this->m_center.x - x) < xRadius && std::abs(this->m_center.z - z) < zRadius) {
            x = AppMath::getInstance()->randomNumber(this->m_min.x + this->m_size.x / 4.f, this->m_max.x - this->m_size.x / 4.f);
            z = AppMath::getInstance()->randomNumber(this->m_min.z + this->m_size.z / 4.f, this->m_max.z - this->m_size.z / 4.f);
        }
        glm::vec3 position = glm::vec3(x, 0.f, z);

        model = this->m_modelWarehouse->createModel(
            "06::tree" + std::to_string(i),
			//"06::shader:phong", "res:tree", 0, 92814, // old tree
            "06::shader:phong_texture",
			"resobj:tree0", // vao
			"resobj:tree0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
            0, numVerticesList[0],
            scale, rotation, position);
        model->setTextureID(2); // texture unit 2; tree
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
            "06::bushes" + std::to_string(i),
            "06::shader:phong", "res:bushes", 0, 8730,
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

        /* used before ModelWarehouse::createModel was specialized; now it's obsolete
        auto shaderProgram = this->m_shaderWarehouse->getShaderProgram("06::shader:single_color");
        auto vao = this->m_modelWarehouse->getVAO("res:sphere");

        auto modelFf = std::make_unique<ModelFirefly>(shaderProgram, vao, 0, 2880);
        this->m_modelWarehouse->addModel("06::firefly" + std::to_string(i), std::move(modelFf));

        ModelFirefly* model = static_cast<ModelFirefly*>(this->m_modelWarehouse->getModel("06::firefly" + std::to_string(i)));
        //model->getTransformation()->setTranslation(position);
        model->getTransformation()->setScale(scale);*/

        auto model = this->m_modelWarehouse->createModel<ModelFirefly>(
            "06::firefly" + std::to_string(i),
            "06::shader:single_color", "res:sphere", 0, 2880,
            scale, glm::vec3(0.f), position);
        model->getTransformation()->updateTranslateStep(std::make_shared<TransformationAnimationRandomMove>(position));

        // --- firefly light source
        light = this->m_lightWarehouse->createLight("06::firefly_light" + std::to_string(i), Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f)); // no need to set position; it will follow the model
        light->setAttenuation(glm::vec3(1.f, .7f, 1.8f));

        model->addObserver(light); // light source now follows the model
    }

    // gift
    model = this->m_modelWarehouse->createModel(
        "06::gift",
        "06::shader:phong", sizeof(gift), gift, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624,
        glm::vec3(11.f), glm::vec3(0.f), glm::vec3(this->m_min.x + 22.f, 4.f, this->m_min.z + 22.f));
    model->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(.05f, .1f, .15f))); // all axis rotation

    // suzanne
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:suzanne_flat", (this->m_modelResourcesPath + "my/suzanne-flat.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "06::suzanne_flat",
        "06::shader:phong_texture",
        "resobj:suzanne_flat0", // vao
        //"resobj:suzanne_flat0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x - 3.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));
    model->setTextureID(6); // texture unit 6; metal
    model->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation

    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:suzanne_smooth", (this->m_modelResourcesPath + "my/suzanne-smooth.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "06::suzanne_smooth",
        "06::shader:phong_texture",
        "resobj:suzanne_smooth0", // vao
        //"resobj:suzanne_smooth0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x + 3.f, 1.5f, this->m_center.z + this->m_size.z / 4.f + 3.f));
    model->setTextureID(6); // texture unit 6; metal
    model->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation

    // cubes
    float zCoord = this->m_center.z + this->m_size.z / 4.f + 3.f;

    this->m_modelWarehouse->createVertexResources("res:cube_texture", ModelLibrary::MODEL_CUBE_TEXTURE, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL_TEXTURE);

    model = this->m_modelWarehouse->createModel(
        "06::cube01",
        "06::shader:phong_texture", "res:cube_texture", 0, 36,
        glm::vec3(3.f), glm::vec3(0.f), glm::vec3(this->m_center.x - 11.5f, this->m_min.y, zCoord - 1.5f));
    model->setTextureID(1); // texture unit 1; wood

    model = this->m_modelWarehouse->createModel(
        "06::cube02",
        "06::shader:phong_texture", "res:cube_texture", 0, 36,
        glm::vec3(3.f), glm::vec3(0.f), glm::vec3(this->m_center.x + 8.5f, this->m_min.y, zCoord - 1.5f));
    model->setTextureID(1); // texture unit 1; wood

    // torches
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:sphere", (this->m_modelResourcesPath + "my/sphere.obj").c_str());

    // --- torch 01
    auto modelLE = this->m_modelWarehouse->createModel<ModelLightEmitting>(
        "06::torch01",
        //"06::shader:single_color",
        "06::shader:texture",
        "resobj:sphere0", // vao
        //"resobj:sphere0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(this->m_center.x - 10.f, 4.5f, zCoord));
    modelLE->setDiffuseColor(glm::vec3(.6f));
    modelLE->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    modelLE->setTextureID(7); // texture unit 7; ice
    modelLE->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation

    light = this->m_lightWarehouse->createLight("06::torchlight01", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setAttenuation(glm::vec3(1.f, .1f, .01f));

    modelLE->addObserver(light); // light source now follows the model

    // --- torch 02
    modelLE = this->m_modelWarehouse->createModel<ModelLightEmitting>(
        "06::torch02",
        //"06::shader:single_color",
        "06::shader:texture",
        "resobj:sphere0", // vao
        //"resobj:sphere0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(.5f, 1.5f, .5f), glm::vec3(0.f), glm::vec3(this->m_center.x + 10.f, 4.5f, zCoord));
    modelLE->setDiffuseColor(glm::vec3(.6f));
    modelLE->setSpecularColor(glm::vec3(.6f, .6f, .6f));
    modelLE->setTextureID(7); // texture unit 7; ice
    modelLE->getTransformation()->updateRotateStep(
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation

    light = this->m_lightWarehouse->createLight("06::torchlight02", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f)); // no need to set position; it will follow the model
    light->setAttenuation(glm::vec3(1.f, .1f, .01f));

    modelLE->addObserver(light); // light source now follows the model

    // torch rings
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:torus", (this->m_modelResourcesPath + "my/torus.obj").c_str());

    // --- torch ring 01
    model = this->m_modelWarehouse->createModel(
        "06::torch_ring01",
        //"06::shader:single_color",
        "06::shader:texture",
        "resobj:torus0", // vao
        //"resobj:torus0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x - 10.f, 4.5f, zCoord));
    //model->setDiffuseColor(glm::vec3(.6f));
    model->setTextureID(7); // texture unit 7; ice
	model->getTransformation()->updateRotateStep( // 3rd step; y-axis rotation
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, -.03f, 0.f))); // 30 seconds for a full rotation
	model->getTransformation()->addStep(          // 2nd step; y-axis rotation
        std::make_shared<TransformationStepRotate>(glm::vec3(45.f, 0.f, 0.f)));
	model->getTransformation()->addStep(          // 1st step; x-axis rotation
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, -.1f,  0.f))); // 10 seconds for a full rotation

    // --- torch ring 02
    model = this->m_modelWarehouse->createModel(
        "06::torch_ring02",
        //"06::shader:single_color",
        "06::shader:texture",
        "resobj:torus0", // vao
        //"resobj:torus0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(1.5f), glm::vec3(0.f), glm::vec3(this->m_center.x + 10.f, 4.5f, zCoord));
    //model->setDiffuseColor(glm::vec3(.6f));
    model->setTextureID(7); // texture unit 7; ice
	model->getTransformation()->updateRotateStep( // 3rd step; y-axis rotation
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, .05f, 0.f))); // 20 seconds for a full rotation
	model->getTransformation()->addStep(          // 2nd step; y-axis rotation
        std::make_shared<TransformationStepRotate>(glm::vec3(45.f, 0.f, 0.f)));
    model->getTransformation()->addStep(          // 1st step; x-axis rotation
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, .1f,  0.f))); // 10 seconds for a full rotation

    // house
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:house", (this->m_modelResourcesPath + "house.obj").c_str());
    //numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:house", (this->m_modelResourcesPath + "house.triangulated.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "06::house",
		"06::shader:phong_texture",
		"resobj:house0", // vao
		"resobj:house0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(1.5f), glm::vec3(0.f, 10.f, 0.f), glm::vec3(this->m_center.x, this->m_min.y, this->m_center.z));
    model->setTextureID(3); // texture unit 3; house

	// zombie
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:zombie", (this->m_modelResourcesPath + "zombie.obj").c_str());
    //numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:zombie", (this->m_modelResourcesPath + "zombie.triangulated.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "06::zombie",
		"06::shader:phong_texture",
		"resobj:zombie0", // vao
		"resobj:zombie0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
        0, numVerticesList[0],
        glm::vec3(1.5f), glm::vec3(0.f, -20.f, 0.f), glm::vec3(this->m_center.x - 4.f, this->m_min.y, this->m_center.z + 16.f));
    model->setTextureID(4); // texture unit 4; zombie

    // login
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:login", (this->m_modelResourcesPath + "my/login.obj").c_str());

    model = this->m_modelWarehouse->createModel(
        "06::login",
		"06::shader:phong",
		"resobj:login0", // vao
		//"resobj:login0", // ibo; if no ibo specified, the vao will be used for rendering
        0, numVerticesList[0],
        glm::vec3(10.f), glm::vec3(0.f), glm::vec3(this->m_center.x, 50.f, this->m_center.z));
    model->getTransformation()->updateRotateStep(
        //std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.01f, .05f, 0.01f))); // all axis rotation
        std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(0.f, .05f, 0.f))); // y axis rotation

    // walls
    numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:wall", (this->m_modelResourcesPath + "zed.obj").c_str());
    //numVerticesList = this->m_modelWarehouse->createBufferResources("resobj:wall", (this->m_modelResourcesPath + "zed.triangulated.obj").c_str());

	this->m_wallPositions = this->generateWallPositions();

	for (size_t i = 0; i < this->m_wallPositions.size(); ++i) {
		model = this->m_modelWarehouse->createModel(
			"06::wall" + std::to_string(i),
			"06::shader:phong_texture",
			"resobj:wall0", // vao
			"resobj:wall0", // ibo; if no ibo specified, the vao will be used for rendering; the model mesh should be correctly triangulated
			0, numVerticesList[0],
			glm::vec3(1.5f), this->m_wallPositions[i].first, this->m_wallPositions[i].second);
		model->setTextureID(5); // texture unit 5; wall
	}

    // fireball
    // --- fireball model
    this->m_modelWarehouse->createVertexResources("res:sphere", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    auto modelFB = this->m_modelWarehouse->createModel<ModelFireball>(
        "06::fireball",
        "06::shader:single_color", "res:sphere", 0, 2880,
        glm::vec3(0.f));

    // --- fireball light source
    light = this->m_lightWarehouse->createLight("06::fireball_light", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f)); // no need to set position; it will follow the model
	//light->setDiffuseColor(glm::vec3(0.f));  // no light emission; will be set when the fireball is thrown
	//light->setSpecularColor(glm::vec3(0.f)); // no light emission; will be set when the fireball is thrown
	//light->setAttenuation(glm::vec3(1.f, 0.f, 0.f)); // no attenuation

    modelFB->addObserver(light); // light source now follows the model
}

void SceneBuilderPlugin06::loadTextures() {
    this->m_textureWarehouse->loadTexture("tex:grass",  (this->m_textureResourcesPath + "grass.png"       ).c_str(), GL_TEXTURE0);
    this->m_textureWarehouse->loadTexture("tex:wood",   (this->m_textureResourcesPath + "test.png"        ).c_str(), GL_TEXTURE1);
    this->m_textureWarehouse->loadTexture("tex:tree",   (this->m_textureResourcesPath + "tree.png"        ).c_str(), GL_TEXTURE2);
    this->m_textureWarehouse->loadTexture("tex:house",  (this->m_textureResourcesPath + "house.png"       ).c_str(), GL_TEXTURE3);
    this->m_textureWarehouse->loadTexture("tex:zombie", (this->m_textureResourcesPath + "zombie.png"      ).c_str(), GL_TEXTURE4);
    this->m_textureWarehouse->loadTexture("tex:wall",   (this->m_textureResourcesPath + "bake.png"        ).c_str(), GL_TEXTURE5);
    this->m_textureWarehouse->loadTexture("tex:metal",  (this->m_textureResourcesPath + "3rd/metal024.png").c_str(), GL_TEXTURE6);
    this->m_textureWarehouse->loadTexture("tex:ice",    (this->m_textureResourcesPath + "my/ice.png"      ).c_str(), GL_TEXTURE7);
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

	for (size_t i = 0; i < Config::ENVIRONMENT_TREES;  ++i)
		this->m_scene->addModel("tree"   + std::to_string(i), this->m_modelWarehouse->getModel("06::tree"   + std::to_string(i)));
	for (size_t i = 0; i < Config::ENVIRONMENT_BUSHES; ++i)
		this->m_scene->addModel("bushes" + std::to_string(i), this->m_modelWarehouse->getModel("06::bushes" + std::to_string(i)));
	for (size_t i = 0; i < Config::ENVIRONMENT_FIREFLIES; ++i) {
		this->m_scene->addModel("firefly"       + std::to_string(i), this->m_modelWarehouse->getModel("06::firefly"       + std::to_string(i)));
		this->m_scene->addLight("firefly_light" + std::to_string(i), this->m_lightWarehouse->getLight("06::firefly_light" + std::to_string(i)));
	}

    this->m_scene->addModel("gift",           this->m_modelWarehouse->getModel("06::gift"));
	this->m_scene->addModel("suzanne_flat",   this->m_modelWarehouse->getModel("06::suzanne_flat"));
	this->m_scene->addModel("suzanne_smooth", this->m_modelWarehouse->getModel("06::suzanne_smooth"));
	this->m_scene->addModel("cube01",         this->m_modelWarehouse->getModel("06::cube01"));
	this->m_scene->addModel("cube02",         this->m_modelWarehouse->getModel("06::cube02"));

    this->m_scene->addModel("torch01",      this->m_modelWarehouse->getModel("06::torch01"));
	this->m_scene->addModel("torch02",      this->m_modelWarehouse->getModel("06::torch02"));
	this->m_scene->addLight("torchlight01", this->m_lightWarehouse->getLight("06::torchlight01"));
	this->m_scene->addLight("torchlight02", this->m_lightWarehouse->getLight("06::torchlight02"));
    this->m_scene->addModel("torch_ring01", this->m_modelWarehouse->getModel("06::torch_ring01"));
    this->m_scene->addModel("torch_ring02", this->m_modelWarehouse->getModel("06::torch_ring02"));

    this->m_scene->addModel("house",  this->m_modelWarehouse->getModel("06::house"));
	this->m_scene->addModel("zombie", this->m_modelWarehouse->getModel("06::zombie"));
	this->m_scene->addModel("login",  this->m_modelWarehouse->getModel("06::login"));

    for (size_t i = 0; i < this->m_wallPositions.size(); ++i)
        this->m_scene->addModel("wall" + std::to_string(i), this->m_modelWarehouse->getModel("06::wall" + std::to_string(i)));

    this->m_scene->addModel("fireball",       this->m_modelWarehouse->getModel("06::fireball"));
    this->m_scene->addLight("fireball_light", this->m_lightWarehouse->getLight("06::fireball_light"));
}

// --- private -----------------------------------------------------------------
std::vector<std::pair<glm::vec3, glm::vec3>> SceneBuilderPlugin06::generateWallPositions() {
    std::vector<std::pair<glm::vec3, glm::vec3>> wallPositions;

    // different number of walls for each of the 4 sides
    size_t bottomCount = AppMath::getInstance()->randomNumber(Config::ENVIRONMENT_WALLS_PER_SIDE / 2, Config::ENVIRONMENT_WALLS_PER_SIDE);
    size_t topCount    = AppMath::getInstance()->randomNumber(Config::ENVIRONMENT_WALLS_PER_SIDE / 2, Config::ENVIRONMENT_WALLS_PER_SIDE);
    size_t leftCount   = AppMath::getInstance()->randomNumber(Config::ENVIRONMENT_WALLS_PER_SIDE / 2, Config::ENVIRONMENT_WALLS_PER_SIDE);
    size_t rightCount  = AppMath::getInstance()->randomNumber(Config::ENVIRONMENT_WALLS_PER_SIDE / 2, Config::ENVIRONMENT_WALLS_PER_SIDE);

    // bottom and top sides; parallel to x-axis
	generateWallsAlongAxis(wallPositions, 'x', -AppMath::getInstance()->randomNumber(this->minRange().z, this->maxRange().z), bottomCount); // min to max wall z size range
    generateWallsAlongAxis(wallPositions, 'x',  AppMath::getInstance()->randomNumber(this->minRange().z, this->maxRange().z), topCount);

    // left and right sides; parallel to z-axis; rotated 90 degrees
    generateWallsAlongAxis(wallPositions, 'z', -AppMath::getInstance()->randomNumber(this->minRange().x, this->maxRange().x), leftCount,  true); // min to max wall x size range
    generateWallsAlongAxis(wallPositions, 'z',  AppMath::getInstance()->randomNumber(this->minRange().x, this->maxRange().x), rightCount, true);

    return wallPositions;
}

void SceneBuilderPlugin06::generateWallsAlongAxis(std::vector<std::pair<glm::vec3, glm::vec3>>& t_walls,
    char t_axis, float t_fixedCoord, size_t t_count, bool t_rotate90) {
    for (size_t i = 0; i < t_count; ++i) {
        // random rotation
        glm::vec3 rotation(
            AppMath::getInstance()->randomNumber(-10.f, 10.f),             // tilt around x-axis
			t_rotate90 ?
                90.f + AppMath::getInstance()->randomNumber(-10.f, 10.f) : // rotate around y-axis by 90 degrees with deviation; z-axis walls
                       AppMath::getInstance()->randomNumber(-15.f, 15.f),  // y-axis rotation; x-axis walls
            AppMath::getInstance()->randomNumber(-10.f, 10.f)              // tilt around z-axis
        );

        // add extreme tilt around x-axis
        if (AppMath::getInstance()->randomNumber(0.f, 1.f) < .15f) // 15% chance for extreme tilt
            rotation.x = AppMath::getInstance()->randomNumber(-80.f, 80.f);

        // random position
        glm::vec3 position;
        if (t_axis == 'x') {
            position = glm::vec3(
                AppMath::getInstance()->randomNumber(
                    this->m_center.x - this->maxRange().x,
                    this->m_center.x + this->maxRange().x),       // x position
                AppMath::getInstance()->randomNumber(-5.f, 0.f), // y sinking into the ground
                this->m_center.z + t_fixedCoord);                 // fixed z coordinate
        } else if (t_axis == 'z') {
            position = glm::vec3(
                this->m_center.x + t_fixedCoord,                  // fixed x coordinate
                AppMath::getInstance()->randomNumber(-5.f, 0.f), // y sinking into the ground
                AppMath::getInstance()->randomNumber(
                    this->m_center.z - this->maxRange().z,
                    this->m_center.z + this->maxRange().z));      // z position
        }

        // the wall(rotation, position) to the vector
        t_walls.push_back(std::make_pair(rotation, position));
    }
}

glm::vec3 SceneBuilderPlugin06::minRange() { return glm::vec3(this->m_size / 2.f * Config::ENVIRONMENT_WALLS_RANGE.x); }
glm::vec3 SceneBuilderPlugin06::maxRange() { return glm::vec3(this->m_size / 2.f * Config::ENVIRONMENT_WALLS_RANGE.y); }
