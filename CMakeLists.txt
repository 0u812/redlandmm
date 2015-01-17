cmake_minimum_required(VERSION 2.8.11)
project(Redlandmm)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(ENABLE_FULL_RPATH 1 CACHE BOOL "Full rpath in linking phase (makes lib paths hardcoded)")

find_package(PkgConfig)

find_package(Raptor2 REQUIRED)

find_package(Rasqal REQUIRED)

find_package(Redland REQUIRED)

set(BOOST_VERSION "1.54" CACHE STRING "Version of Boost to use")
find_package(Boost ${BOOST_VERSION} REQUIRED COMPONENTS unit_test_framework)
if (NOT Boost_FOUND)
  if (ENABLE_UNIT_TESTS)
    message(SEND_ERROR "Unit tests require the Boost Unit Test Framework")
  endif()
  set(ENABLE_UNIT_TESTS OFF CACHE BOOL "Unit testing of components")
endif()
set(ENABLE_UNIT_TESTS ON CACHE BOOL "Unit testing of components")

include_directories(${Boost_INCLUDE_DIR})

# http://www.cmake.org/Wiki/CMake_RPATH_handling
if(ENABLE_FULL_RPATH)
    SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

    SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

    SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

    LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
    IF("${isSystemDir}" STREQUAL "-1")
        SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    ENDIF("${isSystemDir}" STREQUAL "-1")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "
-------------------------------------------------------------------------------
Redlandmm
-------------------------------------------------------------------------------

    C++ wrapper for Redland

    Configured on host $ENV{COMPUTERNAME} ${HOSTNAME}
      host OS                   ${CMAKE_SYSTEM_NAME}
      host architecture         ${CMAKE_SYSTEM_PROCESSOR}

    General flags:
      CC                        ${CMAKE_C_COMPILER}
      CXX                       ${CMAKE_CXX_COMPILER}
      CPPFLAGS                  ${BUILD_DEFINITIONS}
      CFLAGS                    ${CMAKE_C_FLAGS}
      CXXFLAGS                  ${CMAKE_CXX_FLAGS}
      LDFLAGS                   ${CMAKE_EXE_LINKER_FLAGS}

    Installation prefix:        ${CMAKE_INSTALL_PREFIX}

    Options:
      Unit tests                ${ENABLE_UNIT_TESTS}

    Dependencies (packages marked with *** are required):
    "
)

message( "  *** Raptor 2                              ")
message( "    * libs                                  ")
foreach(lib ${Raptor2_LIBRARIES})
  message( "      * ${lib}")
endforeach()
message( "    * include paths                         ")
foreach(path ${Raptor2_INCLUDE_DIRS})
  message( "      * ${path}")
endforeach()

message( "  *** Rasqal                                ")
message( "    * libs                                  ")
foreach(lib ${Rasqal_LIBRARIES})
  message( "      * ${lib}")
endforeach()
message( "    * include paths                         ")
foreach(path ${Rasqal_INCLUDE_DIRS})
  message( "      * ${path}")
endforeach()

message( "  *** Redland                               ")
message( "    * libs                                  ")
foreach(lib ${Redland_LIBRARIES})
  message( "      * ${lib}")
endforeach()
message( "    * include paths                         ")
foreach(path ${Redland_INCLUDE_DIRS})
  message( "      * ${path}")
endforeach()

if (Boost_FOUND)
  message( "  *   Boost                                 ")
  message( "    * libs                                  ")
  foreach(lib ${Boost_LIBRARIES})
    message( "      * ${lib}")
  endforeach()
  message( "    * include paths                         ")
  foreach(path ${Boost_INCLUDE_DIRS})
    message( "      * ${path}")
  endforeach()
endif()

add_subdirectory(redlandmm)


if(ENABLE_UNIT_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
