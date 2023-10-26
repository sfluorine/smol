cmake_minimum_required(VERSION 3.7...3.27)

project(smol LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    smol
    src/lexer.cpp
    src/main.cpp
    src/parser.cpp
    )
target_compile_features(smol PRIVATE cxx_std_20)
