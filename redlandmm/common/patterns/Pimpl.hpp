// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file Pimpl.hpp
  * @author JKM
  * @date 12/27/2014
  * @copyright Apache License, Version 2.0
  * @brief Pimpl idiom pattern based on Herb Sutter GotW 101
  * @details http://herbsutter.com/gotw/_101/
**/

# ifndef __RLMM_PIMPL_H__
# define __RLMM_PIMPL_H__

// == MACROS ==================================================

# if (__cplusplus < 201103L)
#   error "C++11 only"
# endif

// == INCLUDES ================================================

#include "redlandmm/common/core/RedlandmmCore.h"
#include <memory>

// == CODE ====================================================

namespace redlandmm {

  template <class T>
  class Pimpl {
  protected:
    typedef std::unique_ptr<T> Ptr;
    Ptr p_;

  public:

    /// Empty ctor
    Pimpl();

    /// Forwarding ctor
    template<class ...Args>
    Pimpl(Args&&...);

    /// Move ctor
    Pimpl(Pimpl&& other)
      : p_(std::move(other.p_)) {}

    /// Dtor
    ~Pimpl();

    T* operator->();

    T& operator*();

  };

}

# endif // header guard