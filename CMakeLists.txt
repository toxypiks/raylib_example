cmake_minimum_required(VERSION 3.16)
project(simple_raylib_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SIMPLE_RAYLIB_EXAMPLE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  )

set(SIMPLE_3D_EXAMPLE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/3D_example.cpp
  )

set(3D_PROJECTILES_EXAMPLE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/3D_projectiles_example.cpp
  )

find_package(raylib)

add_executable(simple_raylib_example)
target_sources(simple_raylib_example
 PRIVATE
  ${SIMPLE_RAYLIB_EXAMPLE}
  )

add_executable(simple_3d_example)
target_sources(simple_3d_example
 PRIVATE
  ${SIMPLE_3D_EXAMPLE}
)

add_executable(3d_projectiles_example)
target_sources(3d_projectiles_example
 PRIVATE
 ${3D_PROJECTILES_EXAMPLE}
)

target_include_directories(simple_raylib_example
 PRIVATE
  ${raylib_INCLUDE_DIRS}
  )

target_include_directories(simple_3d_example
 PRIVATE
  ${raylib_INCLUDE_DIRS}
  )

target_include_directories(3d_projectiles_example
 PRIVATE
  ${raylib_INCLUDE_DIRS}
  )

target_link_libraries(simple_raylib_example
  ${raylib_LIBRARIES}
  )

target_link_libraries(simple_3d_example
  ${raylib_LIBRARIES}
)

target_link_libraries(3d_projectiles_example
  ${raylib_LIBRARIES}
)
