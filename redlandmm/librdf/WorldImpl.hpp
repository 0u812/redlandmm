// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file WorldImpl.hpp
  * @author JKM
  * @date 01/17/2015
  * @copyright Apache License, Version 2.0
**/

# ifndef __RLMM_WORLD_IMPL_H__
# define __RLMM_WORLD_IMPL_H__

// == MACROS ==================================================

# if (__cplusplus < 201103L)
#   error "C++11 only"
# endif

// == INCLUDES ================================================

#include "redlandmm/common/core/RedlandmmCore.h"
#include "redlandmm/common/patterns/PimplImpl.hpp"
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
    librdf_world* get_world() {
      if (!world_)
        REDLANDMM_THROW( RuntimeException, "Empty ref", "WorldImpl::get_world" );
      return world_;
    }

    librdf_world* world_ = NULL;

    friend class StorageHashMem;
  };

}

# endif