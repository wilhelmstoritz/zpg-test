#include "SceneBuilderPlugin02a.h"

#include "resShaders.h"

#include "bushes.h"
#include "gift.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// --- public ------------------------------------------------------------------
void SceneBuilderPlugin02a::setSceneProperties(Scene* t_scene) {
    t_scene->setTitle("2 | " + t_scene->getTitle());
}

// --- protected ---------------------------------------------------------------
void SceneBuilderPlugin02a::preProcess() {
	// scene size
	this->m_scene->setSize(
        Config::SKYBOX_MIN_VIRTUALWORLD,
        Config::SKYBOX_MAX);

	this->setEnvironment();
}

void SceneBuilderPlugin02a::createShaders() {
    // vertex & fragment shaders; shader program
    this->m_shaderWarehouse->createVertexShader  ("vert:view_projection_matrix", VSHADER_VIEW_PROJECTION_MATRIX);
    this->m_shaderWarehouse->createFragmentShader("frag:view_projection_matrix", FSHADER_VIEW_PROJECTION_MATRIX);

    this->m_shaderWarehouse->createShaderProgram("02:a:shader:view_projection_matrix",
        *this->m_shaderWarehouse->getShader("vert:view_projection_matrix"),
        *this->m_shaderWarehouse->getShader("frag:view_projection_matrix"));
}

void SceneBuilderPlugin02a::createModels() {
    this->m_modelWarehouse->createModel("02:a:bushes",     "02:a:shader:view_projection_matrix", sizeof(bushes),     bushes,     ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 8730);
    this->m_modelWarehouse->createModel("02:a:gift",       "02:a:shader:view_projection_matrix", sizeof(gift),       gift,       ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 66624);
    this->m_modelWarehouse->createModel("02:a:plain",      "02:a:shader:view_projection_matrix", sizeof(plain),      plain,      ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 6);
    this->m_modelWarehouse->createModel("02:a:sphere",     "02:a:shader:view_projection_matrix", sizeof(sphere),     sphere,     ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 2880);
    this->m_modelWarehouse->createModel("02:a:suziFlat",   "02:a:shader:view_projection_matrix", sizeof(suziFlat),   suziFlat,   ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 2904);
    this->m_modelWarehouse->createModel("02:a:suziSmooth", "02:a:shader:view_projection_matrix", sizeof(suziSmooth), suziSmooth, ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 2904);
    this->m_modelWarehouse->createModel("02:a:tree",       "02:a:shader:view_projection_matrix", sizeof(tree),       tree,       ModelFactory::BUFFERINFOLIST_POSITION_COLOR, 0, 92814);

    this->m_modelWarehouse->getModel("02:a:bushes"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-9.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02:a:gift"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-6.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02:a:plain"     )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3(-3.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02:a:sphere"    )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 0.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02:a:suziFlat"  )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 3.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02:a:suziSmooth")->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 6.f, 0.f, 0.f)));
    this->m_modelWarehouse->getModel("02:a:tree"      )->getTransformation()->addStep(std::make_shared<TransformationStepTranslate>(glm::vec3( 9.f, 0.f, 0.f)));
}

void SceneBuilderPlugin02a::postProcess() {
    // camera position
    this->m_scene->getCamera()->setPosition(
        glm::vec3(0.f, 0.f, 16.f),
        glm::vec3(0.f, 0.f, -1.f));
}

void SceneBuilderPlugin02a::addContextToScene() {
    // add models to the scene
	this->m_scene->addModel("bushes",     this->m_modelWarehouse->getModel("02:a:bushes"));
	this->m_scene->addModel("gift",       this->m_modelWarehouse->getModel("02:a:gift"));
	this->m_scene->addModel("plain",      this->m_modelWarehouse->getModel("02:a:plain"));
	this->m_scene->addModel("sphere",     this->m_modelWarehouse->getModel("02:a:sphere"));
	this->m_scene->addModel("suziFlat",   this->m_modelWarehouse->getModel("02:a:suziFlat"));
	this->m_scene->addModel("suziSmooth", this->m_modelWarehouse->getModel("02:a:suziSmooth"));
	this->m_scene->addModel("tree",       this->m_modelWarehouse->getModel("02:a:tree"));
}
