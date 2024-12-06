#include "SceneBuilder.h"
#include "Config.h"

#include "ModelLibrary.h"

#include "bushes.h"
#include "gift.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "tree.h"

// include the standard C++ headers
#include <cstdlib> // rand, srand
#include <ctime>   // seeding random numbers

void SceneBuilder::createScene_02_woods() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random number generator

}
