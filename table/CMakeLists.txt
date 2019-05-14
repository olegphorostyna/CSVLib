cmake_minimum_required(VERSION 2.8)

project(table)

set(SOURCE_LIB CsvTable.cpp Query.cpp Record.cpp ResultSet.cpp )

FILE (GLOB PREDIACATE_CPP predicate/*.cpp)
FILE (GLOB EXCEPTIONS_CPP exceptions/*.cpp)
FILE (GLOB SERIALIZATION_CPP serialization/*.cpp)

#if(ANDROID)
add_library(table SHARED ${SOURCE_LIB} ${PREDIACATE_CPP} ${EXCEPTIONS_CPP} ${SERIALIZATION_CPP})
#else()
#add_library(table STATIC ${SOURCE_LIB} ${PREDIACATE_CPP} ${EXCEPTIONS_CPP} ${SERIALIZATION_CPP})
#endif()

target_include_directories(table INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
