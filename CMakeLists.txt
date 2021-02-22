
cmake_minimum_required(VERSION 3.18.0)

project(gfcc VERSION 1.0.0 LANGUAGES C CXX Fortran)
include(${PROJECT_SOURCE_DIR}/cmake/check_user_env.cmake)

find_package( CMakeBuild )

set(CMSB_PROJECTS gfcc)

set(gfcc_DEPENDENCIES MSGSL Eigen3 LibInt2 HPTT HDF5) # GlobalArrays BLAS LAPACK

if(USE_CUDA) 
   list(APPEND gfcc_DEPENDENCIES TALSH)
endif()

if(DEFINED LINALG_VENDOR)
    if(NOT ${LINALG_VENDOR} STREQUAL "BLIS")
        list(APPEND gfcc_DEPENDENCIES BLIS)
    endif()
endif()

if(USE_GA_AT)
    if(USE_DPCPP)
        list(APPEND gfcc_DEPENDENCIES IntelSYCL)
    endif()
    list(APPEND gfcc_DEPENDENCIES GlobalArrays)
    if(USE_SCALAPACK)
        list(APPEND gfcc_DEPENDENCIES ScaLAPACK LAPACK BLAS)
    else()
        list(APPEND gfcc_DEPENDENCIES LAPACK BLAS)
    endif()
else()
    list(APPEND gfcc_DEPENDENCIES GlobalArrays)
endif()

list(APPEND gfcc_DEPENDENCIES tamm)

set(BUILD_METHODS OFF)

set(gfcc_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/gfcc)
set(gfcc_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/driver/)

if(NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif()

build_cmsb_module(${CMAKE_CURRENT_LIST_DIR})
