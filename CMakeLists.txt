﻿cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

project (AES128 VERSION 0.1)
add_library(AES128 STATIC "src/ShiftRows.cpp" "src/SubBytes.cpp" "src/AES128.cpp" "src/MixColumns.cpp" "src/Key.cpp")
target_include_directories(AES128 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable (main "main.cpp")
target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries (main PUBLIC AES128)  

