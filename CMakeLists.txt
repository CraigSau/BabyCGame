cmake_minimum_required(VERSION 3.15)
project(BasicGame)

set(CMAKE_C_STANDARD 11) # Requires C11 standard

# Add raylib as a subdirectory
add_subdirectory(raylib)

add_executable(${PROJECT_NAME} 
src/main.c
)

# Link raylib to your project
target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
