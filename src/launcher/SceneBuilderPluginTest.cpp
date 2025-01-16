#include "SceneBuilderPluginTest.h"
#include "AppUtils.h"
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

#include "resShaders.h"
#include "resTMP.h"

#include "ModelLibrary.h"
#include "ModelLetters.h"
#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPluginTest::setSceneProperties(Scene* t_scene) {
    t_scene->setTitle("test | " + t_scene->getTitle());
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPluginTest::preProcess() {
    // scene size
    this->m_scene->setSize(
        Config::SKYBOX_MIN_VIRTUALWORLD,
        Config::SKYBOX_MAX);

    this->setEnvironment();
}

void SceneBuilderPluginTest::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createVertexShader  ("vert:view_projection_matrix", VSHADER_VIEW_PROJECTION_MATRIX);
    this->m_shaderWarehouse->createFragmentShader("frag:view_projection_matrix", FSHADER_VIEW_PROJECTION_MATRIX);

    this->m_shaderWarehouse->createShaderProgram("test::shader:view_projection_matrix",
        *this->m_shaderWarehouse->getShader("vert:view_projection_matrix"),
        *this->m_shaderWarehouse->getShader("frag:view_projection_matrix"));

    /*this->m_shaderWarehouse->createVertexShader("vert:tmp", VSHADER_TMP);
    this->m_shaderWarehouse->createFragmentShader("frag:tmp", FSHADER_TMP);

    this->m_shaderWarehouse->createShaderProgram("test::shader:tmp",
        *this->m_shaderWarehouse->getShader("vert:tmp"),
        *this->m_shaderWarehouse->getShader("frag:tmp"));*/

    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("test::shader:texture",       (this->m_shaderResourcesPath + "05/texture.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/texture.frag.glsl"      ).c_str());

    this->m_shaderWarehouse->createShaderProgram("test::shader:lambertian",    (this->m_shaderResourcesPath + "04/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "04/lambertian.frag.glsl"   ).c_str());
    this->m_shaderWarehouse->createShaderProgram("test::shader:phong",         (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/phong.frag.glsl"        ).c_str());
    this->m_shaderWarehouse->createShaderProgram("test::shader:phong_texture", (this->m_shaderResourcesPath + "05/normals-texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/phong-texture.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("test::shader:single_color",  (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/single-color.frag.glsl" ).c_str());

    this->m_shaderWarehouse->createShaderProgram("test::shader:tmp",           (this->m_shaderResourcesPath + "tmp.vert.glsl"               ).c_str(), (this->m_shaderResourcesPath + "tmp.frag.glsl"             ).c_str());
}

void SceneBuilderPluginTest::createLights() {
    Light* light;

    light = this->m_lightWarehouse->createLight("test::light01", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f, 40.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(glm::vec3(0.f, .3f, 0.f));
    light->setSpecularColor(glm::vec3(0.f, .3f, 0.f));
	light->setAttenuation(glm::vec3(.1f, .01f, .0001f));

	light = this->m_lightWarehouse->createLight("test::light02", Light::lightTypeE::SPOT_LIGHT, glm::vec3(8.f, 0.f, 1.f));
    light->setDirection(glm::vec3(-6.f, 0.f, -1.f));
    light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(glm::vec3(0.f, 0.f, 1.f));
    light->setSpecularColor(glm::vec3(1.f, 0.f, 0.f));
	light->setAttenuation(glm::vec3(.1f, .01f, .0001f));

	light = this->m_lightWarehouse->createLight("test::light03", Light::lightTypeE::SPOT_LIGHT, glm::vec3(-100.f, 50.f, 100.f));
    light->setDirection(glm::vec3(2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(3.f);
    light->setDiffuseColor(glm::vec3(.6f, .6f, 0.f)); // yellow
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.f)); // white
	light->setAttenuation(glm::vec3(.1f, .01f, .0001f));
}

void SceneBuilderPluginTest::createModels() {
    Light* light;
    //Model* model;
    //std::vector<GLsizei> numVerticesList;

    // skybox
    this->m_modelWarehouse->createModel(
        "test::skybox",
        //"test::shader:view_projection_matrix", ModelLibrary::MODEL_SKYBOX_RNDCOLORS, ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 36,
        //"test::shader:lambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        //"test::shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        "test::shader:tmp", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        glm::vec3(this->m_size.x, this->m_size.y, this->m_size.z),
        glm::vec3(0.f),
        glm::vec3(this->m_min.x, this->m_min.y, this->m_min.z));

    // vertex resources
    this->m_modelWarehouse->createVertexResources("res:bushes",     sizeof(bushes),     bushes,     ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:gift",       sizeof(gift),       gift,       ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:plain",      sizeof(plain),      plain,      ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:sphere",     sizeof(sphere),     sphere,     ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:suziFlat",   sizeof(suziFlat),   suziFlat,   ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:suziSmooth", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);
    this->m_modelWarehouse->createVertexResources("res:tree",       sizeof(tree),       tree,       ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    this->m_modelWarehouse->createVertexResources("res:wall", ModelLibrary::MODEL_SURFACE, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

	// models
    //this->m_modelWarehouse->createModel("test::bushes",     "test::shader:lambertian", "res:bushes",     0, 8730,  glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-9.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::gift",       "test::shader:lambertian", "res:gift",       0, 66624, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-6.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::plain",      "test::shader:lambertian", "res:plain",      0, 6,     glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-3.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::sphere",     "test::shader:lambertian", "res:sphere",     0, 2880,  glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 0.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::suziFlat",   "test::shader:lambertian", "res:suziFlat",   0, 2904,  glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 3.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::suziSmooth", "test::shader:lambertian", "res:suziSmooth", 0, 2904,  glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 6.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::tree",       "test::shader:lambertian", "res:tree",       0, 92814, glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 9.f, 0.f, 0.f));

    this->m_modelWarehouse->createModel("test::wall", "test::shader:tmp", "res:wall", 0, 6, glm::vec3(10.f), glm::vec3(0.f), glm::vec3(0.f));

    //this->m_modelWarehouse->createModel("test::bushes",     "test::shader:view_projection_matrix", sizeof(bushes),     bushes,     ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 8730);
    //this->m_modelWarehouse->createModel("test::gift",       "test::shader:view_projection_matrix", sizeof(gift),       gift,       ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624);
    //this->m_modelWarehouse->createModel("test::plain",      "test::shader:view_projection_matrix", sizeof(plain),      plain,      ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 6);
    //this->m_modelWarehouse->createModel("test::sphere",     "test::shader:view_projection_matrix", sizeof(sphere),     sphere,     ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880);
    //this->m_modelWarehouse->createModel("test::suziFlat",   "test::shader:view_projection_matrix", sizeof(suziFlat),   suziFlat,   ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904);
    //this->m_modelWarehouse->createModel("test::suziSmooth", "test::shader:view_projection_matrix", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904);
    //this->m_modelWarehouse->createModel("test::tree",       "test::shader:view_projection_matrix", sizeof(tree),       tree,       ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 92814);

    //this->m_modelWarehouse->getModel("test::bushes"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::gift"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::plain"     )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::sphere"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 0.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::suziFlat"  )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 3.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::suziSmooth")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 6.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::tree"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 9.f, 0.f, 0.f)));

	// animation
    std::shared_ptr<TransformationAnimationRotate> animationRotate = std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f), glm::vec3(.01f, .02f, .03f));
    //this->m_modelWarehouse->getModel("test::wall")->getTransformation()->updateRotateStep(animationRotate);

    // fireball
    // --- fireball model
    this->m_modelWarehouse->createVertexResources("res:sphere", sizeof(sphere), sphere, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL);

    auto modelFB = this->m_modelWarehouse->createModel<ModelFireball>(
        "test::fireball",
        "test::shader:single_color", "res:sphere", 0, 2880,
        glm::vec3(0.f));

    // --- fireball light source
    light = this->m_lightWarehouse->createLight("test::fireball_light", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f)); // no need to set position; it will follow the model
    //light->setDiffuseColor(glm::vec3(0.f));  // no light emission; will be set when the fireball is thrown
    //light->setSpecularColor(glm::vec3(0.f)); // no light emission; will be set when the fireball is thrown
    //light->setAttenuation(glm::vec3(1.f, 0.f, 0.f)); // no attenuation

    modelFB->addObserver(light); // light source now follows the model
}

void SceneBuilderPluginTest::loadTextures() {
    //this->m_textureWarehouse->loadTexture("tex:grass",  (this->m_textureResourcesPath + "grass.png" ).c_str(), GL_TEXTURE0);
    //this->m_textureWarehouse->loadTexture("tex:wood",   (this->m_textureResourcesPath + "test.png"  ).c_str(), GL_TEXTURE1);
    //this->m_textureWarehouse->loadTexture("tex:tree",   (this->m_textureResourcesPath + "tree.png"  ).c_str(), GL_TEXTURE2);
    //this->m_textureWarehouse->loadTexture("tex:house",  (this->m_textureResourcesPath + "house.png" ).c_str(), GL_TEXTURE3);
    //this->m_textureWarehouse->loadTexture("tex:zombie", (this->m_textureResourcesPath + "zombie.png").c_str(), GL_TEXTURE4);
    //this->m_textureWarehouse->loadTexture("tex:wall",   (this->m_textureResourcesPath + "bake.png"  ).c_str(), GL_TEXTURE5);
    //this->m_textureWarehouse->loadTexture("tex:ice",    (this->m_textureResourcesPath + "my/ice.png").c_str(), GL_TEXTURE6);
}

void SceneBuilderPluginTest::postProcess() {
    // camera position & flashlight
    this->m_scene->getCamera()->setPosition(
        glm::vec3(this->m_center.x, this->m_center.y, this->m_center.z + 20.f),
        glm::vec3(0.f, 0.f, -1.f));

    //LightFlashlight* flashlight = static_cast<LightFlashlight*>(this->m_lightWarehouse->createFlashlight("test::flashlight", this->m_scene->getCamera()));
    Light* flashlight = this->m_lightWarehouse->createFlashlight("test::flashlight", this->m_scene->getCamera());
    flashlight->setAttenuation(glm::vec3(1.f, 0.01f, 0.001f));
}

void SceneBuilderPluginTest::addContextToScene() {
    // add lights to the scene
    this->m_scene->addLight("light01",    this->m_lightWarehouse->getLight("test::light01"));
    this->m_scene->addLight("light02",    this->m_lightWarehouse->getLight("test::light02"));
    this->m_scene->addLight("light03",    this->m_lightWarehouse->getLight("test::light03"));

    this->m_scene->addLight("flashlight", this->m_lightWarehouse->getLight("test::flashlight"));

    // add models and lights to the scene
    this->m_scene->addModel("skybox", this->m_modelWarehouse->getModel("test::skybox"));

    //this->m_scene->addModel("bushes",     this->m_modelWarehouse->getModel("test::bushes"));
    //this->m_scene->addModel("gift",       this->m_modelWarehouse->getModel("test::gift"));
    //this->m_scene->addModel("plain",      this->m_modelWarehouse->getModel("test::plain"));
    //this->m_scene->addModel("sphere",     this->m_modelWarehouse->getModel("test::sphere"));
    //this->m_scene->addModel("suziFlat",   this->m_modelWarehouse->getModel("test::suziFlat"));
    //this->m_scene->addModel("suziSmooth", this->m_modelWarehouse->getModel("test::suziSmooth"));
    //this->m_scene->addModel("tree",       this->m_modelWarehouse->getModel("test::tree"));

    this->m_scene->addModel("wall",           this->m_modelWarehouse->getModel("test::wall"));

    this->m_scene->addModel("fireball",       this->m_modelWarehouse->getModel("test::fireball"));
    this->m_scene->addLight("fireball_light", this->m_lightWarehouse->getLight("test::fireball_light"));
}

