cmake_minimum_required (VERSION 2.6)
project (Lotto)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

find_package(Boost 1.55 COMPONENTS filesystem system program_options REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
