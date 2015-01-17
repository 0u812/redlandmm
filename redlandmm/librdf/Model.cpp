// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file Model.cpp
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
#include "redlandmm/librdf/Model.hpp"
#include "redlandmm/common/patterns/PimplImpl.hpp"

#include "librdf.h"

// == CODE ====================================================

namespace redlandmm {

  class Model::ModelImpl {
  public:
    ModelImpl(StoragePtr&& storage) {
    }

    ~ModelImpl() {
    }

  protected:
  };

  Model::Model(StoragePtr&& storage)
    : impl_(std::move(storage)) {}

  Model::~Model() {}

}