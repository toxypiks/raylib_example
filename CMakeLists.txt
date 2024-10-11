cmake_minimum_required(VERSION 3.16)
project(simple_raylib_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SIMPLE_RAYLIB_EXAMPLE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  )

find_package(raylib)

add_executable(simple_raylib_example)
target_sources(simple_raylib_example
 PRIVATE
  ${SIMPLE_RAYLIB_EXAMPLE}
)

target_include_directories(simple_raylib_example
 PRIVATE
  ${raylib_INCLUDE_DIRS}
)
target_link_libraries(simple_raylib_example
  ${raylib_LIBRARIES}
)
