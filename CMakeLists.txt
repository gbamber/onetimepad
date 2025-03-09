##
## Written and Copyright (c) 2025 gbamber
## Licensed under the EUPL-1.2
## SPDX-License-Identifier: EUPL-1.2
## License URL: https://joinup.ec.europa.eu/collection/eupl
## https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
##


cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  message (STATUS "In debug-mode. Setting -D_DEBUG -O0 -ggdb")
  add_compile_definitions(_DEBUG)
  add_compile_options(-O0)
  add_compile_options(-ggdb)
  add_compile_options(-Wpedantic)
else ()
  message (STATUS "NOT in debug-mode: ${CMAKE_BUILD_TYPE}")
  add_compile_definitions(NDEBUG)
  add_compile_options(-O3)
endif ()

add_compile_definitions(_GBAMBER)
add_compile_options(-Wall)
add_compile_options(-Wextra)

project(onetimepad C CXX ASM)

file(GLOB SOURCES "src/*.cpp")

add_executable(onetimepad ${SOURCES})

# Add the standard include files to the build
target_include_directories(onetimepad PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/include
)

# Add any user requested libraries
target_link_libraries(onetimepad 
        )





