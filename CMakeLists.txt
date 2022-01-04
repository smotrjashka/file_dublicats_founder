cmake_minimum_required(VERSION 3.19)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(file_double_triple_founder VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)

##set(Boost_USE_STATIC_LIBS ON)
##find_package(Boost 1.66.0 COMPONENTS program_options REQUIRED)
##include_directories(${Boost_INCLUDE_DIR})

add_executable(file_double_triple_founder main.cpp dir_reader.cpp dir_reader.h file_info.cpp file_info.h dir_treat.cpp dir_treat.h file_list_filter.cpp file_list_filter.h cmd_options_parser.cpp cmd_options_parser.h cmd_options_helper.cpp cmd_options_helper.h md5.cpp md5.h sha1.cpp sha1.h sha2.cpp sha2.h)

###target_link_libraries(boost_options_demo boost_program_options)

set_target_properties(
        file_double_triple_founder PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

install(TARGETS file_double_triple_founder RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)