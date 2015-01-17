include_directories(${Raptor2_INCLUDE_DIRS})
include_directories(${Rasqal_INCLUDE_DIRS})
include_directories(${Redland_INCLUDE_DIRS})

set(COMMON_SOURCES
    common/core/RedlandmmAssert.c
    common/core/RedlandmmCommon.cpp
    common/core/RedlandmmException.cpp
    )

set(COMMON_HEADERS
    common/core/BaseWORDs.h
    common/core/Debug.hpp
    common/core/DefaultBool.hpp
    common/core/RedlandmmAssert.h
    common/core/RedlandmmCommon.h
    common/core/RedlandmmConfigure.h
    common/core/RedlandmmCore.h
    common/core/RedlandmmException.hpp
    common/core/RedlandmmPlatform.h
    common/core/RedlandmmPlatformWin.h
    common/core/RedlandmmPrefetch.h

    common/patterns/Pimpl.hpp
    common/patterns/PimplImpl.hpp)

set(LIBRDF_SOURCES
    librdf/Model.cpp
    librdf/World.cpp
    )

set(LIBRDF_HEADERS
    librdf/Model.hpp
    librdf/World.hpp
    )

configure_file(common/core/config.h.in common/core/config.h)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/common/core/config.h DESTINATION include/redlandmm/common/core)

set( REDLANDMM_SOURCES ${COMMON_SOURCES} ${LIBRDF_SOURCES} )

add_library(redlandmm SHARED ${REDLANDMM_SOURCES})

target_link_libraries(redlandmm ${Redland_LIBRARIES} ${Rasqal_LIBRARIES} ${Raptor2_LIBRARIES})

install(TARGETS redlandmm DESTINATION lib)

# ** Headers **

set( REDLANDMM_HEADERS ${COMMON_HEADERS} ${LIBRDF_HEADERS} )

foreach(header ${REDLANDMM_HEADERS})
  get_filename_component(prefix ${header} PATH)
#   message("header ${header}, prefix ${prefix}")
  install(FILES ${header} DESTINATION include/redlandmm/${prefix})
endforeach()