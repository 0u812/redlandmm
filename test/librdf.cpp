// == PREAMBLE ================================================

// * Licensed under the Apache License, Version 2.0; see README

// == FILEDOC =================================================

/** @file librdf.cpp
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
#include "redlandmm/librdf/World.hpp"
#include "redlandmm/librdf/Model.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOS_TEST_MODULE librdf
#include "boost/test/unit_test.hpp"

// == CODE ====================================================

BOOST_AUTO_TEST_SUITE( librdf )

BOOST_AUTO_TEST_CASE( sanity )
{
  BOOST_CHECK_MESSAGE( true == true, "Sanity check" );
}

BOOST_AUTO_TEST_CASE( my_test )
{
  using namespace redlandmm;

  World world;

  Model model(StorageHashMem());
}

BOOST_AUTO_TEST_SUITE_END()