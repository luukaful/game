cmake_minimum_required(VERSION 3.30)
project(project0)

# C++ standaard instellen
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specificeer SFML folder
set(SFML_DIR "${CMAKE_SOURCE_DIR}/include/SFML v2.6.2/lib/cmake/SFML")

# Vind SFML
find_package(SFML 2.6.2 COMPONENTS system window graphics audio REQUIRED)

# Voeg de executable toe
add_executable(project0
        src/DialoogBox.cpp
        include/DialoogBox.h
)

# Bronbestanden toevoegen
target_sources(project0 PRIVATE
        src/main.cpp
        src/player.cpp
        include/player.h
)

# Voeg de bibliotheken toe
target_include_directories(project0 PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/tmxlite
)

# Link bibliotheken
target_link_libraries(project0 PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

# Stel de uitvoermap in
set_target_properties(project0 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)