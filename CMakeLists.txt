# Set the minimum version of CMake required to build the project
cmake_minimum_required(VERSION 3.15)

# Set the project name
project(VoxelView)

# Disable regeneration and default build projects
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define important paths
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party)

# Automatically gather all .cpp and .hpp files in src/
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.hpp)

# Include directories
include_directories(${SRC_DIR})

# Ensure all subdirectories are included
file(GLOB_RECURSE ALL_DIRS LIST_DIRECTORIES true "${SRC_DIR}/*")
foreach(DIR ${ALL_DIRS})
    if(IS_DIRECTORY ${DIR})
        include_directories(${DIR})
    endif()
endforeach()

# Include dependencies directories
include_directories(${THIRD_PARTY_DIR}/freetype/include)
include_directories(${THIRD_PARTY_DIR}/glew/include)
include_directories(${THIRD_PARTY_DIR}/glfw/include)

# Link directories for external libraries
link_directories(${THIRD_PARTY_DIR}/freetype/lib)
link_directories(${THIRD_PARTY_DIR}/glew/lib)
link_directories(${THIRD_PARTY_DIR}/glfw/lib)

# Add preprocessor directive to link GLEW statically
add_definitions(-DGLEW_STATIC)

# Create the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link external libraries
target_link_libraries(${PROJECT_NAME} glew32s glfw3 opengl32 freetype)


# Set binary output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Organize files in Visual Studio using the folder structure from src/
source_group(TREE ${SRC_DIR} PREFIX "Source Files" FILES ${SRC_FILES})

# Set the startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

