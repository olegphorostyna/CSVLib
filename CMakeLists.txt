cmake_minimum_required(VERSION 3.4.1)

project(csv_lib)

set(CMAKE_TOOLCHAIN_FILE "$ENV{ANDROID_CMAKE_HOME}/android.toolchain.cmake")
set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(ANDROID_PLATFORM_LEVEL 21)
set(ANDROID_ABI "armeabi-v7a")

set(SOURCE_EXE CSVReader.cpp)


add_executable(main ${SOURCE_EXE})

add_subdirectory(table)
set_target_properties(table PROPERTIES COMPILE_DEFINITIONS "ANDROID")


target_link_libraries(main table)
