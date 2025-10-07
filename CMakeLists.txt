cmake_minimum_required(VERSION 3.22)
project(learncpp_chapters_pro LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(CTest)

function(enable_warnings target)
  if (MSVC)
    target_compile_options(${target} PRIVATE /W4 /WX)
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
  endif()
endfunction()

add_executable(ch00_hello C00-Getting-Started/sections/s01-hello/main.cpp)
enable_warnings(ch00_hello)

add_executable(ch01_first C01-Program-Structure/sections/s01-first-program/main.cpp)
enable_warnings(ch01_first)

add_executable(ch02_funcs C02-Functions/sections/s01-functions/main.cpp C02-Functions/sections/s01-functions/lib.cpp)
target_include_directories(ch02_funcs PRIVATE C02-Functions/sections/s01-functions)
enable_warnings(ch02_funcs)

add_executable(ch03_io C03-IO-Format/sections/s01-format/main.cpp)
enable_warnings(ch03_io)

add_executable(ch04_types C04-Types-Init/sections/s01-types-init/main.cpp)
enable_warnings(ch04_types)

add_executable(ch05_ptrs C05-Pointers-References/sections/s01-ptrs-refs/main.cpp)
enable_warnings(ch05_ptrs)

add_executable(ch06_stl C06-Std-Containers-Algorithms/sections/s01-stl-records/main.cpp)
enable_warnings(ch06_stl)

add_executable(ch07_raii C07-Classes-RAII/sections/s01-file-raii/main.cpp)
enable_warnings(ch07_raii)

add_executable(ch08_smart C08-Smart-Pointers/sections/s01-tree/main.cpp)
enable_warnings(ch08_smart)

add_executable(ch09_moves C09-Moves-Ownership/sections/s01-move-strings/main.cpp)
enable_warnings(ch09_moves)

add_executable(ch10_tpl C10-Templates-Concepts/sections/s01-templates-concepts/main.cpp)
enable_warnings(ch10_tpl)

add_executable(ch11_ranges C11-Lambdas-Ranges/sections/s01-pipeline/main.cpp)
enable_warnings(ch11_ranges)

add_executable(ch12_errors C12-Error-Handling/sections/s01-optional-throw/main.cpp)
enable_warnings(ch12_errors)

add_executable(ch13_fs C13-Filesystem-Time/sections/s01-fs-time/main.cpp)
enable_warnings(ch13_fs)

add_executable(ch14_cmake C14-CMake-Project/sections/s01-app/main.cpp)
enable_warnings(ch14_cmake)

add_executable(ch15_tests C15-Testing/sections/s01-ctest/main.cpp external/minitest/minitest.hpp)
target_include_directories(ch15_tests PRIVATE external/minitest)
enable_warnings(ch15_tests)
add_test(NAME ch15_tests COMMAND ch15_tests)
