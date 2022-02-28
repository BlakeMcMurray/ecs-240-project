############################################################################
# Copyright (c) 2019, Sylvain Corlay, Johan Mabille, Wolf Vollprecht       #
# Copyright (c) 2019, QuantStack                                           #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.4.3)
project(xeus-basik)

set(XEUS_BASIK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Versionning
# ===========

file(STRINGS "${XEUS_BASIK_INCLUDE_DIR}/xeus-basik/xeus_basik_config.hpp" basik_version_defines
     REGEX "#define BASIK_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${basik_version_defines})
    if(ver MATCHES "#define BASIK_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(BASIK_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(${PROJECT_NAME}_VERSION
${BASIK_VERSION_MAJOR}.${XPYT_VERSION_MINOR}.${XPYT_VERSION_PATCH})
message(STATUS "Building xeus-basik v${${PROJECT_NAME}_VERSION}")

# Configuration
# =============

include(GNUInstallDirs)

# We generate the kernel.json file, given the installation prefix and the executable name
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/share/jupyter/kernels/basik/kernel.json.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/share/jupyter/kernels/basik/kernel.json"
)

# Dependencies
# ============

# Be sure to use recent versions
set(xeus_REQUIRED_VERSION 2.3.0)
set(cppzmq_REQUIRED_VERSION 4.8.1)

find_package(xeus ${xeus_REQUIRED_VERSION} REQUIRED)
find_package(cppzmq ${cppzmq_REQUIRED_VERSION} REQUIRED)

# Flags
# =====

include(CheckCXXCompilerFlag)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)

    if (HAS_CPP14_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        message(FATAL_ERROR "Unsupported compiler -- xeus requires C++14 support!")
    endif()
endif()

# Target and link
# ===============

# xeus-basik source directory
set(XEUS_BASIK_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# xeus-basik source files
set(XEUS_BASIK_SRC
    ${XEUS_BASIK_SRC_DIR}/xeus_basik_interpreter.cpp
)

set(XEUS_BASIK_HEADERS
    include/xeus-basik/xeus_basik_interpreter.hpp
    include/xeus-basik/xeus_basik_config.hpp
)

# xeus-basik is the target for the library
add_library(xeus-basik SHARED ${XEUS_BASIK_SRC} ${XEUS_BASIK_HEADERS})


# basik is the target for the kernel executable
add_executable(basik src/main.cpp)
set_target_properties(basik PROPERTIES ENABLE_EXPORTS 1)
target_link_libraries(basik PRIVATE xeus-basik)
target_compile_definitions(basik PRIVATE XEUS_BASIK_HOME="${BASIK_PREFIX}")

if (APPLE)
    set_target_properties(basik PROPERTIES
        MACOSX_RPATH ON
    )
else()
    set_target_properties(basik PROPERTIES
        BUILD_WITH_INSTALL_RPATH 1
        SKIP_BUILD_RPATH FALSE
    )
endif()


set_target_properties(basik xeus-basik PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE
)

# OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

#Option for GTest
# if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
#     set(BUILD_TESTS ON)
# endif()

target_link_libraries(xeus-basik PUBLIC xeus)


set_target_properties(basik PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE
)

target_include_directories(xeus-basik
                           PUBLIC
                           ${BASIK_INCLUDE_DIRS}
                           $<BUILD_INTERFACE:${XEUS_BASIK_INCLUDE_DIR}>
                           $<INSTALL_INTERFACE:include>)

set_target_properties(xeus-basik PROPERTIES
                      PUBLIC_HEADER "${XEUS_BASIK_HEADERS}"
                      COMPILE_DEFINITIONS "XEUS_BASIK_EXPORTS"
                      PREFIX ""
                      VERSION ${${PROJECT_NAME}_VERSION}
                      SOVERSION ${BASIK_VERSION_MAJOR}
OUTPUT_NAME "libxeus-basik")


## Test ##
# take into account the CMakeList in test

# OPTION(BUILD_TESTS "xeus-basik test suite" OFF)
# OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

# if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
#     set(BUILD_TESTS ON)
# endif()


# if(BUILD_TESTS)
#     add_subdirectory(test)
# endif()

# Installation
# ============

# Install xeus-basik and basik
install(TARGETS xeus-basik
        EXPORT ${PROJECT_NAME}-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xeus-basik)

install(TARGETS basik
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Configuration and data directories for jupyter and xeus_basik
set(XJUPYTER_DATA_DIR "share/jupyter" CACHE STRING "Jupyter data directory")

# Install Jupyter kernelspecs
set(XEUS_BASIKSPEC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/share/jupyter/kernels)
install(DIRECTORY ${XEUS_BASIKSPEC_DIR}
        DESTINATION ${XJUPYTER_DATA_DIR}
        PATTERN "*.in" EXCLUDE)


# Extra path for installing Jupyter kernelspec
if (XEXTRA_JUPYTER_DATA_DIR)
    install(DIRECTORY ${XEUS_BASIKSPEC_DIR}
            DESTINATION ${XEXTRA_JUPYTER_DATA_DIR}
            PATTERN "*.in" EXCLUDE)
endif(XEXTRA_JUPYTER_DATA_DIR)
