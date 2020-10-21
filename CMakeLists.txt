
cmake_minimum_required(VERSION 3.17.0)
project(gfcc VERSION 1.0.0 LANGUAGES C CXX Fortran)
include(${PROJECT_SOURCE_DIR}/cmake/check_user_env.cmake)
set(NWX_PROJECTS gfcc)

set(gfcc_DEPENDENCIES NWX_MPI MSGSL Eigen3 LibInt2 HPTT HDF5 tamm) # GlobalArrays BLAS LAPACK

if(DEFINED BLAS_VENDOR)
    if(NOT ${BLAS_VENDOR} STREQUAL "ReferenceBLAS")
        list(APPEND gfcc_DEPENDENCIES BLIS)
    endif()
endif()

if(USE_CUDA) 
    list(APPEND gfcc_DEPENDENCIES TALSH)
endif()

list(APPEND gfcc_DEPENDENCIES GlobalArrays BLAS LAPACK)

set(BUILD_METHODS OFF)

set(gfcc_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/gfcc)
set(gfcc_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/driver/)

if(NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif()

find_package(CMakeBuild)
build_nwchemex_module(${CMAKE_CURRENT_LIST_DIR})
