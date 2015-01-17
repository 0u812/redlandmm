// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file URI.hpp
  * @author JKM
  * @date 01/17/2015
  * @copyright Apache License, Version 2.0
  * @brief librdf uri
**/

# ifndef __RLMM_LIBRDF_URI_H__
# define __RLMM_LIBRDF_URI_H__

// == MACROS ==================================================

# if (__cplusplus < 201103L)
#   error "C++11 only"
# endif

// == INCLUDES ================================================

#include "redlandmm/common/core/RedlandmmCore.h"
#include "redlandmm/librdf/World.hpp"
#include "redlandmm/common/patterns/Pimpl.hpp"

// == CODE ====================================================

namespace redlandmm {

  class URI {
  public:
    URI(World& world, std::string id);
    ~URI();

    bool operator == (const URI& other) const;

  protected:
    class URIImpl;
    typedef Pimpl<URIImpl> Impl;
    Impl impl_;
  };

  typedef std::unique_ptr<URI> URIPtr;

}

# endif // header guard