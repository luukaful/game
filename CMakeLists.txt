cmake_minimum_required(VERSION 3.30)
project(project0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to specify SFML directory
set(SFML_DIR "${CMAKE_SOURCE_DIR}/include/SFML v2.6.2/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.6.2 COMPONENTS system window graphics REQUIRED)

# Add the executable
add_executable(project0)

# Add source files
target_sources(project0 PRIVATE
        src/main.cpp
        src/player.cpp
        include/player.h
)

# Include directories
target_include_directories(project0 PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/tmxlite
)

# Link SFML libraries
target_link_libraries(project0 PRIVATE sfml-system sfml-window sfml-graphics)

# Set output directory
set_target_properties(project0 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)