cmake_minimum_required(VERSION 3.12)
project(dot_screen_saver CXX)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "[!] Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(SOURCE
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/tokenizer.cpp
  ${PROJECT_SOURCE_DIR}/src/parser.cpp
  ${PROJECT_SOURCE_DIR}/src/node.cpp)

add_executable(dot_screen_saver
  ${SOURCE}) 
target_compile_features(dot_screen_saver PRIVATE cxx_std_20)

find_package(Siv3D)
target_link_libraries(dot_screen_saver PUBLIC Siv3D::Siv3D)
