cmake_minimum_required(VERSION 3.16)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Mandatory for flawless LSP/auto-completion

# 1. FIND SYSTEM LIBRARIES (Only the OS-level ones)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# 2. BUILD THE VENDOR LIBRARIES (GLAD)
add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)

# 3. BUILD YOUR ENGINE CORE (Gather all your .cpp files)
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")
add_library(EngineCore STATIC ${ENGINE_SOURCES})

# 4. ENGINE INCLUDES (Tell the engine where to find headers)
target_include_directories(EngineCore PUBLIC 
    include
    vendor/glm
    vendor/stb
)

# 5. LINK ENGINE DEPENDENCIES
target_link_libraries(EngineCore PUBLIC 
    OpenGL::GL 
    glfw 
    glad 
    m  # Math library
    dl
    pthread
)

# 6. ADD THE SANDBOX EXECUTABLE
add_subdirectory(sandbox)
