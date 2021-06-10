cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(GFCC-Test VERSION 0.0.0 LANGUAGES CXX)
find_package(GFCC REQUIRED)
include(TargetMacros)

include_directories(${CMAKE_SOURCE_DIR}/..)
include_directories(${CMAKE_SOURCE_DIR}/../src)
include_directories(${CMAKE_SOURCE_DIR}/../utils/external)
add_mpi_unit_test(CD_CCSD 2 "${CMAKE_SOURCE_DIR}/../tests/co.json")
add_mpi_unit_test(GF_CCSD 2 "${CMAKE_SOURCE_DIR}/../tests/co.json")
add_mpi_unit_test(HartreeFock 2 "${CMAKE_SOURCE_DIR}/../tests/co.json")
add_mpi_unit_test(CholeskyDecomp 2 "${CMAKE_SOURCE_DIR}/../tests/co.json")

set(CCSD_T_SRCDIR ${CMAKE_SOURCE_DIR}/../src/gfcc/contrib/ccsd_t)
set(CCSD_T_SRCS
    ${CCSD_T_SRCDIR}/memory.cpp
    ${CCSD_T_SRCDIR}/ccsd_t_common.hpp
    ${CCSD_T_SRCDIR}/hybrid.cpp
    ${CCSD_T_SRCDIR}/ccsd_t_fused_driver.hpp
    ${CCSD_T_SRCDIR}/fused_common.hpp
    )

if(USE_CUDA)
    set(CCSD_T_FUSED_SRCS ${CCSD_T_SRCS}
            ${CCSD_T_SRCDIR}/ccsd_t_all_fused.hpp
            ${CCSD_T_SRCDIR}/ccsd_t_all_fused_gpu.cu)

elseif(USE_DPCPP)
    set(CCSD_T_FUSED_SRCS ${CCSD_T_SRCS}
            ${CCSD_T_SRCDIR}/ccsd_t_all_fused.hpp
            ${CCSD_T_SRCDIR}/ccsd_t_all_fused_sycl.hpp)
else()
    set(CCSD_T_FUSED_SRCS ${CCSD_T_SRCS}
            ${CCSD_T_SRCDIR}/ccsd_t_all_fused_cpu.hpp)
endif()

add_mpi_cuda_unit_test(CCSD_T "${CCSD_T_FUSED_SRCS}" 2 "${CMAKE_SOURCE_DIR}/../tests/co.json")
