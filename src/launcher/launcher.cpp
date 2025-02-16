#include "Application.h"
#include "Scene.h"
#include "SceneFlashlight.h"
#include "SceneFireball.h"
#include "SceneBuilder.h"

#include "SceneBuilderPluginEmptyScene.h"
#include "SceneBuilderPluginTest.h"
#include "SceneBuilderPluginMenu.h"
#include "SceneBuilderPlugin01.h"
#include "SceneBuilderPlugin02a.h"
#include "SceneBuilderPlugin02b.h"
#include "SceneBuilderPlugin03.h"
#include "SceneBuilderPlugin04.h"
#include "SceneBuilderPlugin05a.h"
#include "SceneBuilderPlugin05b.h"
#include "SceneBuilderPlugin05c.h"
#include "SceneBuilderPlugin06.h"

int main(void) {
	SceneBuilder* builder     = SceneBuilder::getInstance();
	Application*  application = Application ::getInstance();

	//application->addScene(builder->createScene                 ("scene::empty", new SceneBuilderPluginEmptyScene)); // empty scene; testing purposes
	//application->addScene(builder->createScene<SceneFireball>  ("scene::test", new SceneBuilderPluginTest)); // test scene
	application->addScene(builder->createScene<SceneFlashlight>(Config::SYSTEM_MENU, new SceneBuilderPluginMenu)); // main menu

	// zpg tasks
	application->addScene(builder->createScene                 ("scene::1", new SceneBuilderPlugin01));  // task 01;  basic geometries
	application->addScene(builder->createScene                 ("scene::2", new SceneBuilderPlugin02a)); // task 02a; zpg models; normals used as colors
	application->addScene(builder->createScene                 ("scene::3", new SceneBuilderPlugin02b)); // task 02b; woods; normals used as colors
	application->addScene(builder->createScene                 ("scene::4", new SceneBuilderPlugin03));  // task 03;  illuminated spheres
	application->addScene(builder->createScene<SceneFlashlight>("scene::5", new SceneBuilderPlugin04));  // task 04;  magic woods
	application->addScene(builder->createScene                 ("scene::6", new SceneBuilderPlugin05a)); // task 05a; skycube & skydome
	application->addScene(builder->createScene<SceneFlashlight>("scene::7", new SceneBuilderPlugin05b)); // task 05b; magic woods with textures; torches & grass
	application->addScene(builder->createScene<SceneFlashlight>("scene::8", new SceneBuilderPlugin05c)); // task 05c; magic woods with .obj models; trees, house, zombie & login
	application->addScene(builder->createScene<SceneFireball>  ("scene::9", new SceneBuilderPlugin06));  // task 06;  dark magic woods; everything + walls & bezier fireballs

	application->run();

	return(0);
}
