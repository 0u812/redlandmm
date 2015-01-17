// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file World.hpp
  * @author JKM
  * @date 12/27/2014
  * @copyright Apache License, Version 2.0
  * @brief librdf world
**/

# ifndef __RLMM_LIBRDF_WORLD_H__
# define __RLMM_LIBRDF_WORLD_H__

// == MACROS ==================================================

# if (__cplusplus < 201103L)
#   error "C++11 only"
# endif

// == INCLUDES ================================================

#include "redlandmm/common/core/RedlandmmCore.h"
#include "redlandmm/common/patterns/Pimpl.hpp"

// == CODE ====================================================

namespace redlandmm {

  class World {
  public:
    World();
    ~World();

  protected:
    class WorldImpl;
    typedef Pimpl<WorldImpl> Impl;
    Impl impl_;

    Impl& getimpl() { return impl_; }

    friend class StorageHashMem;
    friend class URI;
  };

  typedef std::unique_ptr<World> WorldPtr;

}

# endif // header guard