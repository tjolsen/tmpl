cmake_minimum_required(VERSION 3.8)
project(tmpl)


# tmpl requires C++17!
set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/include/tmpl.hpp
        ${CMAKE_SOURCE_DIR}/include/tmpl_common.hpp

        ${CMAKE_SOURCE_DIR}/include/concepts.hpp
        ${CMAKE_SOURCE_DIR}/include/for_constexpr.hpp
        ${CMAKE_SOURCE_DIR}/include/mp_funs.hpp
        ${CMAKE_SOURCE_DIR}/include/type_collections.hpp
        ${CMAKE_SOURCE_DIR}/include/type_list.hpp
        ${CMAKE_SOURCE_DIR}/include/value_list.hpp
        )

add_library(tmpl INTERFACE)

# This makes it more IDE-friendly, but is not necessary for use/installation
target_sources(tmpl INTERFACE $<BUILD_INTERFACE:${SOURCE_FILES}>)

target_include_directories(tmpl INTERFACE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/tmpl>)

install(TARGETS tmpl EXPORT tmplConfig)
install(
        DIRECTORY include/
        DESTINATION include/tmpl
        FILES_MATCHING PATTERN "*.hpp")

install(EXPORT tmplConfig
        DESTINATION share/tmpl/cmake
        NAMESPACE tmpl::)

#-------------------------------
# Development target
#-------------------------------
add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox PUBLIC tmpl)

#-------------------------------
# Examples of usage
#-------------------------------
option(BUILD_EXAMPLES "Build tmpl examples" ON)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()