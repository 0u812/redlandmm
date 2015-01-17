// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file Model.hpp
  * @author JKM
  * @date 01/17/2015
  * @copyright Apache License, Version 2.0
  * @brief librdf world
**/

# ifndef __RLMM_LIBRDF_MODEL_H__
# define __RLMM_LIBRDF_MODEL_H__

// == MACROS ==================================================

# if (__cplusplus < 201103L)
#   error "C++11 only"
# endif

// == INCLUDES ================================================

#include "redlandmm/common/core/RedlandmmCore.h"
#include "redlandmm/librdf/Storage.hpp"
#include "redlandmm/common/patterns/Pimpl.hpp"

#include <memory> // unique_ptr

// == CODE ====================================================

namespace redlandmm {

  class Model {
  public:
    Model(StoragePtr&& storage);

    template <class StorageClass>
    Model(StorageClass&& storage)
      : Model(StoragePtr(new StorageClass(std::move(storage)))) {}

    ~Model();

  protected:
    class ModelImpl;
    Pimpl<ModelImpl> impl_;
  };

  typedef std::unique_ptr<Model> ModelPtr;

}

# endif // header guard