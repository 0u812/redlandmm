# - Try to find the Redland rdf libraries (http://librdf.org/)
# Once done this will define
#
#  Redland_FOUND       - system has Redland
#  Redland_LIBRARIES   - Link these to use REDLAND
#  Redland_INCLUDE_DIRS - Include directory for using the redland library
#  Redland_VERSION     - The redland version string
#
# Specifying the minimum required version via the find_package() interface
# is also supported by this module.

# Always empty, so remove it from the docs for now, Alex
#  REDLAND_DEFINITIONS - Compiler switches required for using REDLAND

# (c) 2007-2009 Sebastian Trueg <trueg@kde.org>
#
# Based on FindFontconfig Copyright (c) 2006,2007 Laurent Montel, <montel@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if(WINCE)
find_program(
  REDLAND_CONFIG_EXECUTABLE
  NAMES redland-config
  PATHS ${HOST_BINDIR} NO_DEFAULT_PATH
  )
else(WINCE)
find_program(
  REDLAND_CONFIG_EXECUTABLE
  NAMES redland-config
  )
endif(WINCE)

if(REDLAND_CONFIG_EXECUTABLE)
  EXECUTE_PROCESS(
    COMMAND ${REDLAND_CONFIG_EXECUTABLE} --version
    OUTPUT_VARIABLE Redland_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  if(Redland_VERSION)

    # extract include paths from redland-config
    execute_process(
      COMMAND ${REDLAND_CONFIG_EXECUTABLE} --cflags
      OUTPUT_VARIABLE redland_LIBS_ARGS)
    string( REPLACE " " ";" redland_LIBS_ARGS ${redland_LIBS_ARGS} )
    foreach( _ARG ${redland_LIBS_ARGS} )
      if(${_ARG} MATCHES "^-I")
        string(REGEX REPLACE "^-I" "" _ARG ${_ARG})
        string( REPLACE "\n" "" _ARG ${_ARG} )
        list(APPEND redland_INCLUDE_DIRS ${_ARG})
      endif(${_ARG} MATCHES "^-I")
    endforeach(_ARG)

    # extract lib paths from redland-config
    execute_process(
      COMMAND ${REDLAND_CONFIG_EXECUTABLE} --libs
      OUTPUT_VARIABLE redland_CFLAGS_ARGS)
    string( REPLACE " " ";" redland_CFLAGS_ARGS ${redland_CFLAGS_ARGS} )
    foreach( _ARG ${redland_CFLAGS_ARGS} )
      if(${_ARG} MATCHES "^-L")
        string(REGEX REPLACE "^-L" "" _ARG ${_ARG})
        list(APPEND redland_LIBRARY_DIRS ${_ARG})
      endif(${_ARG} MATCHES "^-L")
    endforeach(_ARG)
  endif(Redland_VERSION)
endif(REDLAND_CONFIG_EXECUTABLE)

# This one is always empty, Alex
# set(REDLAND_DEFINITIONS ${redland_CFLAGS})


find_path(Redland_INCLUDE_DIRS redland.h
  HINTS
  ${redland_INCLUDE_DIRS}
  /usr/X11/include
  PATH_SUFFIXES redland
  )

find_library(Redland_LIBRARIES NAMES rdf librdf
  HINTS
  ${redland_LIBRARY_DIRS}
  )

set(_Redland_VERSION_OK TRUE)
if(NOT WIN32)

  # Look for unresolved symbols in shared librdf_storage_* libs
  set(_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
  set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_SHARED_LIBRARY_SUFFIX})
  set(_REDLAND_STORAGE_LIBS)
  foreach(_STORAGE_LIB rdf_storage_mysql rdf_storage_sqlite rdf_storage_tstore rdf_storage_postgresql rdf_storage_virtuoso)
    set(_LIB_PATH NOTFOUND)
    find_library(_LIB_PATH
      ${_STORAGE_LIB}
      HINTS
      ${redland_LIBRARY_DIRS}
      PATH_SUFFIXES redland
    )
    if(_LIB_PATH)
      set(_REDLAND_STORAGE_LIBS ${_REDLAND_STORAGE_LIBS} ${_LIB_PATH})
    endif(_LIB_PATH)
  endforeach(_STORAGE_LIB)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ${_SUFFIXES})
  if(_REDLAND_STORAGE_LIBS)
    message(STATUS "Found Redland storage: ${_REDLAND_STORAGE_LIBS}")
  endif(_REDLAND_STORAGE_LIBS)

endif(NOT WIN32)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Redland  DEFAULT_MSG  REDLAND_CONFIG_EXECUTABLE Redland_LIBRARIES Redland_LIBRARIES _Redland_VERSION_OK)

mark_as_advanced(Redland_INCLUDE_DIRS_TMP
  Redland_INCLUDE_DIRS
  Redland_LIBRARIES)
