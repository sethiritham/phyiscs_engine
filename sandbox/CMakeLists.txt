add_executable(SandboxApp main.cpp)

# Link the sandbox to your massive EngineCore library
target_link_libraries(SandboxApp PRIVATE EngineCore)
