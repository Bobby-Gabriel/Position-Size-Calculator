cmake_minimum_required(VERSION 4.0)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

project(PositionSizeCalculator)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(PositionSizeCalculator)

target_sources(PositionSizeCalculator
    PRIVATE
    main.cpp
)

target_link_libraries(PositionSizeCalculator
    PRIVATE
    Qt6::Widgets
)