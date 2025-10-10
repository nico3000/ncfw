cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ncfw)

include(FetchContent)
FetchContent_Declare(
    nlohmannJson
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmannJson)

if(WIN32)
    add_compile_definitions(NOMINMAX)
endif()

add_library(
    ncfw STATIC
    ncfw/src/Actor.cpp
    ncfw/src/ActorFactory.cpp
    ncfw/src/App.cpp
    ncfw/src/EventManager.cpp
    ncfw/src/Logger.cpp
    ncfw/src/ProcessManager.cpp
    ncfw/src/Property.cpp
    ncfw/src/PropertyContainer.cpp
    ncfw/src/PropertyProxy.cpp
)

target_include_directories(
    ncfw
    PUBLIC ncfw/include/
)

add_executable(
    ncfw_sandbox
    ncfw_sandbox/main.cpp
)

target_link_libraries(
    ncfw_sandbox
    PUBLIC ncfw
    PUBLIC nlohmann_json::nlohmann_json
)
