cmake_minimum_required (VERSION 2.8)

project(NMRVis)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wno-sign-compare " )

set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Boost 1.49 REQUIRED COMPONENTS serialization)
find_package(FlowVR)

add_subdirectory(src)
add_subdirectory(start_scripts)

