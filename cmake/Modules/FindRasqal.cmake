# - Try to find Rasqal
# Once done, this will define
#
#  Rasqal_FOUND - system has Rasqal
#  Rasqal_INCLUDE_DIRS - the Rasqal include directories
#  Rasqal_LIBRARIES - link these to use Rasqal
#
# See documentation on how to write CMake scripts at
# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries

include(LibFindMacros)

pkg_check_modules(PC_RASQAL REQUIRED rasqal)

find_library(Rasqal_LIBRARY NAMES rasqal
    HINTS ${PC_RASQAL_LIBDIR} ${PC_RASQAL_LIBRARY_DIRS}
    ${RASQAL_PATH}/lib ${RASQAL_PATH}/lib64)

find_path(Rasqal_INCLUDE_DIR rasqal.h
    HINTS ${PC_RASQAL_INCLUDEDIR} ${PC_RASQAL_INCLUDE_DIRS}
    ${RASQAL_PATH}/include)

set(Rasqal_PROCESS_INCLUDES Rasqal_INCLUDE_DIR)
set(Rasqal_PROCESS_LIBS Rasqal_LIBRARY)
libfind_process(Rasqal)

