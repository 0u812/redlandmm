// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file World.cpp
  * @author JKM
  * @date 12/27/2014
  * @copyright Apache License, Version 2.0
**/

// == MACROS ==================================================

# if (__cplusplus < 201103L)
#   error "C++11 only"
# endif

// == INCLUDES ================================================

#include "redlandmm/common/core/RedlandmmCore.h"
#include "redlandmm/librdf/World.hpp"

#include "librdf.h"

// == CODE ====================================================

namespace redlandmm {

  class World::WorldImpl {
  public:
    WorldImpl() {
      world_ = librdf_new_world();
    }

    ~WorldImpl() {
      librdf_free_world(world_);
    }

  protected:
    librdf_world* world_ = NULL;
  };

  World::World() {}

}