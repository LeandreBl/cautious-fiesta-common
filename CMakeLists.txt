cmake_minimum_required (VERSION 3.7)

set(LIB_NAME "cautious-fiesta-common")

project(LIB_NAME VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0.0")
    message(FATAL_ERROR "Insufficient gcc version")
  endif()
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SRCS "src/*.cpp")

set(HDRS "include")

set(CMAKE_CXX_FLAGS_DEBUG "-O3 -g3 -Wall -Wextra -Weffc++ -Wshadow -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wsign-conversion -Wlogical-op -Wuseless-cast -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -g3 -Wextra -O3 -fsanitize=address")

add_subdirectory(sfml-scene)
add_subdirectory(discord-rpc)

add_library(${LIB_NAME} SHARED ${SRCS} ${HDRS})
set_target_properties(${LIB_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(${LIB_NAME} PRIVATE ${HDRS} "sfml-scene/include" "discord-rpc/include")
target_link_libraries(${LIB_NAME} asan stdc++fs sfml-system sfml-graphics stdc++fs sfml-scene)
