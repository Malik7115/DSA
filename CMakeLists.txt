cmake_minimum_required(VERSION 3.0.0)
project(DSA VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(
    cHelperFuncs
    cHelperFuncs.cpp
    cAlgorithms
    cAlgorithms.cpp
    cDataStructs
    cDataStructs.cpp

)



add_executable(DSA main.cpp)

target_link_libraries(
    cHelperFuncs
    cAlgorithms
    cDataStructs
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
