// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file Storage.cpp
  * @author JKM
  * @date 01/17/2015
  * @copyright Apache License, Version 2.0
**/

// == MACROS ==================================================

# if (__cplusplus < 201103L)
#   error "C++11 only"
# endif

// == INCLUDES ================================================

#include "redlandmm/common/core/RedlandmmCore.h"
#include "redlandmm/common/patterns/PimplImpl.hpp"
#include "redlandmm/librdf/WorldImpl.hpp"
#include "redlandmm/librdf/Storage.hpp"

#include "librdf.h"

// == CODE ====================================================

namespace redlandmm {

  class Storage::StorageImpl {
  public:
    StorageImpl() {
    }

    ~StorageImpl() {
    }

  protected:
  };

  Storage::Storage() {}

  Storage::~Storage() {}

  class StorageHashMem::StorageHashMemImpl {
  public:
    StorageHashMemImpl(World::Impl& world) {
      storage_ = librdf_new_storage(world->get_world(), "hashes", NULL, "hash-type='memory'");
      if (!storage_)
        REDLANDMM_THROW( RuntimeException, "Failed to create hashed storage in memory", "StorageHashMemImpl::StorageHashMemImpl" );
    }

    ~StorageHashMemImpl() {
      librdf_free_storage(storage_);
    }

  protected:
    librdf_storage* storage_ = NULL;
  };

  StorageHashMem::StorageHashMem(World& world)
    : impl_(world.getimpl()) {}

  StorageHashMem::~StorageHashMem() {}

}