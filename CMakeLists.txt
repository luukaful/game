cmake_minimum_required(VERSION 3.30)
project(project0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to your SFML installation
set(CMAKE_PREFIX_PATH "C:/SFML")
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.6.2 COMPONENTS system window graphics REQUIRED)

# Add the executable
add_executable(project0 main.cpp player.cpp player.h map.cpp map.h)

# Link SFML libraries
target_link_libraries(project0 sfml-system sfml-window sfml-graphics)