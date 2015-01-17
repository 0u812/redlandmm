// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file URI.cpp
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
#include "redlandmm/librdf/URI.hpp"

#include "librdf.h"

// == CODE ====================================================

namespace redlandmm {

  class URI::URIImpl {
  public:
    URIImpl(World::Impl& world, std::string id) {
      uri_ = librdf_new_uri(world->get_world(), (const unsigned char*)id.c_str());
    }

    ~URIImpl() {
      librdf_free_uri(uri_);
    }

    bool compare(const URIImpl& other) const {
      return librdf_uri_equals(uri_, other.uri_);
    }

  protected:
    librdf_uri *uri_ = NULL;
  };

  URI::URI(World& world, std::string id)
    : impl(world.getimpl(), id) {}

  URI::~URI() {}

  bool operator == (const URI& other) const {
    return impl_.compare(*other.impl_);
  }

}