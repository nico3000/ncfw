cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ncfw)

find_package(Lua REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

if(WIN32)
    add_compile_definitions(NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

#[====[
library: ncfw
]====]
list(
    APPEND ncfw_SOURCES
    ncfw/src/Actor.cpp
    ncfw/src/ActorFactory.cpp
    ncfw/src/App.cpp
    ncfw/src/EventManager.cpp
    ncfw/src/FileSystemSource.cpp
    ncfw/src/Logger.cpp
    ncfw/src/ProcessManager.cpp
    ncfw/src/Property.cpp
    ncfw/src/PropertyContainer.cpp
    ncfw/src/PropertyProxy.cpp
    ncfw/src/ResCache.cpp
    ncfw/src/Resource.cpp
)

list(
    APPEND ncfw_HEADERS
    ncfw/include/ncfw/ActorSystem/Actor.hpp
    ncfw/include/ncfw/ActorSystem/ActorFactory.hpp
    ncfw/include/ncfw/ActorSystem/ActorId.hpp
    ncfw/include/ncfw/Algebra/Angle.hpp
    ncfw/include/ncfw/Algebra/Matrix.hpp
    ncfw/include/ncfw/Algebra/MatrixFactory.hpp
    ncfw/include/ncfw/Algebra/Vector.hpp
    ncfw/include/ncfw/EventSystem/Event.hpp
    ncfw/include/ncfw/EventSystem/EventListener.hpp
    ncfw/include/ncfw/EventSystem/EventListenerCallbackHandle.hpp
    ncfw/include/ncfw/EventSystem/EventManager.hpp
    ncfw/include/ncfw/EventSystem/UniversalEventListener.hpp
    ncfw/include/ncfw/EventSystem/UniversalEventListenerCallbackHandle.hpp
    ncfw/include/ncfw/ProcessSystem/Process.hpp
    ncfw/include/ncfw/ProcessSystem/ProcessManager.hpp
    ncfw/include/ncfw/PropertySystem/Property.hpp
    ncfw/include/ncfw/PropertySystem/PropertyContainer.hpp
    ncfw/include/ncfw/PropertySystem/PropertyProxy.hpp
    ncfw/include/ncfw/ResCache/FileSystemSource.hpp
    ncfw/include/ncfw/ResCache/ResCache.hpp
    ncfw/include/ncfw/ResCache/Resource.hpp
    ncfw/include/ncfw/ResCache/ResourceSource.hpp
    ncfw/include/ncfw/App.hpp
    ncfw/include/ncfw/AppModule.hpp
    ncfw/include/ncfw/Exception.hpp
    ncfw/include/ncfw/Logger.hpp
)

add_library(
    ncfw STATIC
    ${ncfw_SOURCES}
    ${ncfw_HEADERS}
)

target_include_directories(
    ncfw
    PUBLIC ncfw/include/
    PUBLIC ${LUA_INCLUDE_DIR}
)

target_link_libraries(
    ncfw
    PUBLIC lua
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC Vulkan::Vulkan
    PUBLIC ${LUA_LIBRARIES}
)

#[====[
executable: ncfw_sandbox
]====]
add_executable(
    ncfw_sandbox
    ncfw_sandbox/main.cpp
)

target_link_libraries(
    ncfw_sandbox
    PUBLIC ncfw
)
