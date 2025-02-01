cmake_minimum_required (VERSION 3.22)

# Change project name
set (PROJECT_NAME exeSmallString)

project (${PROJECT_NAME} C CXX)

# Folder where the Coverage module is
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Source files folder
set (SRC_DIR src)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Wall -Werror -fsanitize=address -static-libasan -g")

include_directories (${PROJECT_SOURCE_DIR}/include)
set (SOURCE
    ${SRC_DIR}/main.cc
)

link_directories(/usr/local/lib)

# Output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")

# Add the executable for the program
add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME})

add_subdirectory(tests)