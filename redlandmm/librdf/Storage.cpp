// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file Storage.cpp
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
#include "redlandmm/librdf/Storage.hpp"
#include "redlandmm/common/patterns/PimplImpl.hpp"

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

  Storage()
    {}

  Storage::~Storage() {}

}