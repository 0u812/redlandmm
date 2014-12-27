// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file PimplImpl.hpp
  * @author JKM
  * @date 12/27/2014
  * @copyright Apache License, Version 2.0
  * @brief Pimpl idiom pattern based on Herb Sutter GotW 101
  * @details http://herbsutter.com/gotw/_101/
**/

# ifndef __RLMM_PIMPL_IMPL_H__
# define __RLMM_PIMPL_IMPL_H__

// == MACROS ==================================================

# if (__cplusplus < 201103L)
#   error "C++11 only"
# endif

// == INCLUDES ================================================

#include "redlandmm/common/patterns/Pimpl.hpp"

// == CODE ====================================================

template <class T>
Pimpl<T>::Pimpl() : p_{ new T{} } {}

template <class T>
template <class ...Args>
Pimpl<T>::Pimpl( Args&& ...args )
  : p_{ new T{ std::forward<Args>(args)... } } {}

template <class T>
Pimpl<T>::~Pimpl() {}

template <class T>
T* Pimpl<T>::operator->() { return  p_.get(); }

template <class T>
T& Pimpl<T>::operator* () { return *p_.get(); }

# endif // header guard