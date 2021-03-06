// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file Storage.hpp
  * @author JKM
  * @date 01/17/2015
  * @copyright Apache License, Version 2.0
  * @brief librdf world
**/

# ifndef __RLMM_LIBRDF_STORAGE_H__
# define __RLMM_LIBRDF_STORAGE_H__

// == MACROS ==================================================

# if (__cplusplus < 201103L)
#   error "C++11 only"
# endif

// == INCLUDES ================================================

#include "redlandmm/common/core/RedlandmmCore.h"
#include "redlandmm/common/patterns/Pimpl.hpp"
#include "redlandmm/librdf/World.hpp"

#include <memory> // unique_ptr

// == CODE ====================================================

namespace redlandmm {

  class Storage {
  public:
    ~Storage();

  protected:
    Storage();

    class StorageImpl;
    Pimpl<StorageImpl> impl_;
  };

  typedef std::unique_ptr<Storage> StoragePtr;

  class StorageHashMem : public Storage {
  public:
    StorageHashMem(World& world);
    ~StorageHashMem();

    StorageHashMem(StorageHashMem&& other);

  protected:
    class StorageHashMemImpl;
    Pimpl<StorageHashMemImpl> impl_;
  };

  typedef std::unique_ptr<StorageHashMem> StorageHashMemPtr;

}

# endif // header guard