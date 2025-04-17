cmake_minimum_required(VERSION 3.30)
project(project0)

set(CMAKE_CXX_STANDARD 26)

# Set the path to your SFML installation
set(SFML_DIR "C:/Coding/C++/!lib/SFML/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add the executable
add_executable(project0 main.cpp)

# Link SFML libraries
target_link_libraries(project0 sfml-system sfml-window sfml-graphics)