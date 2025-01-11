#include "SceneBuilderPluginTest.h"
#include "AppUtils.h"
#include "Config.h"
#include "Light.h"
#include "LightFlashlight.h"
#include "Model.h"
#include "ModelLightEmitting.h"
#include "ModelFireball.h"
#include "ModelFirefly.h"
#include "TransformationAnimationRandomMove.h"
#include "TransformationAnimationRotate.h"

#include "resShaders.h"
#include "resTMP.h"

#include "ModelLibrary.h"
//#include "ModelLetters.h"
#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPluginTest::setSceneProperties(Scene* t_scene) {
    t_scene->setTitle(this->m_windowTitle
        + Config::WINDOW_TITLE_MOVE
        + Config::WINDOW_TITLE_HELP_FLASHLIGHT);
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPluginTest::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createVertexShader("vert:view_projection_matrix", VSHADER_VIEW_PROJECTION_MATRIX);
    this->m_shaderWarehouse->createFragmentShader("frag:view_projection_matrix", FSHADER_VIEW_PROJECTION_MATRIX);

    this->m_shaderWarehouse->createShaderProgram("shader:view_projection_matrix",
        *this->m_shaderWarehouse->getShader("vert:view_projection_matrix"),
        *this->m_shaderWarehouse->getShader("frag:view_projection_matrix"));

    /*this->m_shaderWarehouse->createVertexShader("vert:tmp", VSHADER_TMP);
    this->m_shaderWarehouse->createFragmentShader("frag:tmp", FSHADER_TMP);

    this->m_shaderWarehouse->createShaderProgram("shader:tmp",
        *this->m_shaderWarehouse->getShader("vert:tmp"),
        *this->m_shaderWarehouse->getShader("frag:tmp"));*/

    this->m_shaderWarehouse->createShaderProgram("shader:lambertian",   (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/lambertian.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("shader:phong",        (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/phong.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("shader:single_color", (this->m_shaderResourcesPath + "04/normals.vert.glsl").c_str(), (this->m_shaderResourcesPath + "04/single-color.frag.glsl").c_str());

    this->m_shaderWarehouse->createShaderProgram("shader:tmp", (this->m_shaderResourcesPath + "tmp.vert.glsl").c_str(), (this->m_shaderResourcesPath + "tmp.frag.glsl").c_str());

    /**/
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createShaderProgram("test::shader:texture",       (this->m_shaderResourcesPath + "05/texture.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/texture.frag.glsl"      ).c_str());

    this->m_shaderWarehouse->createShaderProgram("test::shader:phong",         (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/phong.frag.glsl"        ).c_str());
    this->m_shaderWarehouse->createShaderProgram("test::shader:phong_texture", (this->m_shaderResourcesPath + "05/normals-texture.vert.glsl").c_str(), (this->m_shaderResourcesPath + "05/phong-texture.frag.glsl").c_str());
    this->m_shaderWarehouse->createShaderProgram("test::shader:single_color",  (this->m_shaderResourcesPath + "05/normals.vert.glsl"        ).c_str(), (this->m_shaderResourcesPath + "05/single-color.frag.glsl" ).c_str());
}

void SceneBuilderPluginTest::createLights() {
    Light* light;

    light = this->m_lightWarehouse->createLight("test::light01", Light::lightTypeE::POINT_LIGHT, glm::vec3(0.f, 40.f, 0.f));
    light->setDirection(glm::vec3(0.f, -1.f, 0.f));
    //light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(glm::vec3(0.f, .3f, 0.f));
    light->setSpecularColor(glm::vec3(0.f, .3f, 0.0f));
	light->setAttenuation(glm::vec3(.1f, 0.01f, 0.0001f));

	light = this->m_lightWarehouse->createLight("test::light02", Light::lightTypeE::SPOT_LIGHT, glm::vec3(8.f, 0.f, 1.f));
    light->setDirection(glm::vec3(-6.f, 0.f, -1.f));
    light->setSpotCutoffDegrees(10.f);
    light->setDiffuseColor(glm::vec3(0.f, 0.f, 1.0f));
    light->setSpecularColor(glm::vec3(1.f, 0.f, 0.0f));
	light->setAttenuation(glm::vec3(.1f, 0.01f, 0.0001f));

	light = this->m_lightWarehouse->createLight("test::light03", Light::lightTypeE::SPOT_LIGHT, glm::vec3(-100.f, 50.f, 100.f));
    light->setDirection(glm::vec3(2.f, -1.f, -2.f));
    light->setSpotCutoffDegrees(3.f);
    light->setDiffuseColor(glm::vec3(.6f, .6f, 0.f)); // yellow
    light->setSpecularColor(glm::vec3(1.f, 1.f, 1.0f)); // white
	light->setAttenuation(glm::vec3(.1f, 0.01f, 0.0001f));
}

void SceneBuilderPluginTest::createModels() {
    Light* light;
    Model* model;
    std::vector<GLsizei> numVerticesList;

    // skybox
    this->m_modelWarehouse->createModel(
        "test::skybox",
        //"shader:view_projection_matrix", ModelLibrary::MODEL_SKYBOX_RNDCOLORS, ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 36,
        //"shader:lambertian", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        //"shader:phong", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
        "shader:tmp", ModelLibrary::MODEL_SKYBOX_NORMALS, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 36,
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
    //this->m_modelWarehouse->createModel("test::bushes01",     "shader:lambertian", "res:bushes",     0, 8730,  glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-9.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::gift01",       "shader:lambertian", "res:gift",       0, 66624, glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-6.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::plain01",      "shader:lambertian", "res:plain",      0, 6,     glm::vec3(1.f), glm::vec3(0.f), glm::vec3(-3.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::sphere01",     "shader:lambertian", "res:sphere",     0, 2880,  glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 0.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::suziFlat01",   "shader:lambertian", "res:suziFlat",   0, 2904,  glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 3.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::suziSmooth01", "shader:lambertian", "res:suziSmooth", 0, 2904,  glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 6.f, 0.f, 0.f));
    //this->m_modelWarehouse->createModel("test::tree01",       "shader:lambertian", "res:tree",       0, 92814, glm::vec3(1.f), glm::vec3(0.f), glm::vec3( 9.f, 0.f, 0.f));

    this->m_modelWarehouse->createModel("test::wall01",       "shader:tmp", "res:wall", 0, 6, glm::vec3(10.f), glm::vec3(0.f), glm::vec3(0.f));

    //this->m_modelWarehouse->createModel("test::bushes",     "shader:view_projection_matrix", sizeof(bushes),     bushes,     ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 8730);
    //this->m_modelWarehouse->createModel("test::gift",       "shader:view_projection_matrix", sizeof(gift),       gift,       ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 66624);
    //this->m_modelWarehouse->createModel("test::plain",      "shader:view_projection_matrix", sizeof(plain),      plain,      ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 6);
    //this->m_modelWarehouse->createModel("test::sphere",     "shader:view_projection_matrix", sizeof(sphere),     sphere,     ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2880);
    //this->m_modelWarehouse->createModel("test::suziFlat",   "shader:view_projection_matrix", sizeof(suziFlat),   suziFlat,   ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904);
    //this->m_modelWarehouse->createModel("test::suziSmooth", "shader:view_projection_matrix", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 2904);
    //this->m_modelWarehouse->createModel("test::tree",       "shader:view_projection_matrix", sizeof(tree),       tree,       ModelFactory::BUFFERINFOLIST_POSITION_NORMAL, 0, 92814);

    //this->m_modelWarehouse->getModel("test::bushes01"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::gift01"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::plain01"     )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::sphere01"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 0.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::suziFlat01"  )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 3.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::suziSmooth01")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 6.f, 0.f, 0.f)));
    //this->m_modelWarehouse->getModel("test::tree01"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 9.f, 0.f, 0.f)));

	// animation
    std::shared_ptr<TransformationAnimationRotate> animationRotate = std::make_shared<TransformationAnimationRotate>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(.01f, .02f, .03f));
    //this->m_modelWarehouse->getModel("test::wall01")->getTransformation()->updateRotateStep(animationRotate);

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
    //light->setAttenuation(glm::vec3(1.f, 10.f, 100.f)); // huge (absurd) attenuation; the light source will be visible only when the fireball is thrown

    modelFB->addObserver(light); // light source now follows the model
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
