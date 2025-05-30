cmake_minimum_required(VERSION 3.30)
project(project0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML setup
set(SFML_DIR "${CMAKE_SOURCE_DIR}/include/SFML v2.6.2/lib/cmake/SFML")
find_package(SFML 2.6.2 COMPONENTS system window graphics audio REQUIRED)

# Gather source and header files automatically
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)
file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS
    include/*.h
)

# Add executable
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
        src/Story1.cpp
        include/Story1.h
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include

)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


