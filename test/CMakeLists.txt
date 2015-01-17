include_directories(${Raptor2_INCLUDE_DIRS})
include_directories(${Rasqal_INCLUDE_DIRS})
include_directories(${Redland_INCLUDE_DIRS})

set(UTEST_SOURCES
    librdf.cpp
    )

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_TEST_DYN_LINK")

add_executable( redlandmm_test ${UTEST_SOURCES} )
target_link_libraries( redlandmm_test redlandmm ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
set_target_properties( redlandmm_test PROPERTIES COMPILE_DEFINITIONS REDLANDMM_CLIENT_BUILD=1 )

# add_test(librdf redlandmm_test)

install( TARGETS redlandmm_test DESTINATION test )