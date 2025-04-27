cmake_minimum_required(VERSION 3.30)
project(project0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to the SFML installation
set(SFML_DIR "${CMAKE_SOURCE_DIR}/include/ext/SFML v2.6.2/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.6.2 COMPONENTS system window graphics REQUIRED)

# Add the executable
add_executable(project0
        src/main.cpp
        src/map.cpp
        src/player.cpp
        include/player.h
        include/map.h
)

# Include directories
target_include_directories(project0 PRIVATE include/ext/SFML)
target_include_directories(project0 PRIVATE include/ext)

# Link SFML libraries
target_link_libraries(project0 sfml-system sfml-window sfml-graphics)
