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
#include "redlandmm/librdf/URI.hpp"

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

BOOST_AUTO_TEST_CASE( uri_test )
{
  using namespace redlandmm;

  World world;

  // http://www.textuality.com/tag/uri-comp-3.html

  URI a{world, "http://a/b"};
  URI b{world, "http://a/b"};
  URI c{world, "http://a%2fb"};

  BOOST_CHECK_MESSAGE( a == a, "Reflexivity" );

  BOOST_CHECK_MESSAGE( a == b, "URI comparison control" );

  BOOST_CHECK_MESSAGE( b == a, "Symmetry" );

  BOOST_CHECK_MESSAGE( a != c, "Escaped special char" );

  BOOST_CHECK_MESSAGE( b != c, "Transitivity" );

  // machine dependent

  URI d{world, "http://dir/a"};
  URI e{world, "http://dir/%61"};

  BOOST_CHECK_MESSAGE( d != e, "Machine-dependent encoding" );

  // RFC2396 logic

  URI f{world, "example://a/b/c/%7A"};
  URI g{world, "eXAMPLE://a/./b/../b/c/%7a"};

  // not supported by redland (probably for the better)
//   BOOST_CHECK_MESSAGE( d == e, "RFC2396 logic" );
}

BOOST_AUTO_TEST_CASE( model_test )
{
  using namespace redlandmm;

  World world;

  Model model{StorageHashMem(world)};
}

BOOST_AUTO_TEST_SUITE_END()