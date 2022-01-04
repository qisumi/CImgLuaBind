cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")
message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}.")

project(CImgLuaBind)

set(CMAKE_CXX_STANDARD 17)

add_executable(CImgLuaBind main.cpp)
include_directories("includes")

find_package(Lua REQUIRED)
target_include_directories(CImgLuaBind PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(CImgLuaBind PRIVATE ${LUA_LIBRARIES})

find_package(CImg CONFIG REQUIRED)
target_link_libraries(CImgLuaBind PRIVATE CImg::CImg)