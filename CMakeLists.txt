cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
endif(MSVC)

project(VulkanTest)
find_package(Vulkan REQUIRED)

add_definitions(-DSHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)

set(VTEST_SRC)
set(VTRIANGLE_SRC src/VulkanBaseContext.cpp)

add_executable(vtest src/main.cpp)
add_executable(vtriangle src/HelloTriangleApp.cpp ${VTRIANGLE_SRC})

target_include_directories(vtest PRIVATE include)
target_include_directories(vtriangle PRIVATE include)

target_compile_definitions(vtest PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(vtest PRIVATE Vulkan::Vulkan)
target_link_libraries(vtest Vulkan::Vulkan)

target_include_directories(vtest PRIVATE libs/glfw/include)
target_include_directories(vtest PRIVATE libs/glm)
target_link_libraries(vtest glfw)

target_compile_definitions(vtriangle PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(vtriangle PRIVATE Vulkan::Vulkan)
target_link_libraries(vtriangle Vulkan::Vulkan)

target_include_directories(vtriangle PRIVATE libs/glfw/include)
target_include_directories(vtriangle PRIVATE libs/glm)
target_link_libraries(vtriangle glfw)

