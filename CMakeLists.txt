cmake_minimum_required(VERSION 3.9)
project(VulkanTest)

find_package(Vulkan REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)

set(VTEST_SRC)

add_executable(vtest src/main.cpp)


target_compile_definitions(vtest PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(vtest PRIVATE Vulkan::Vulkan)
target_link_libraries(vtest Vulkan::Vulkan)

target_include_directories(vtest PRIVATE libs/glfw/include)
target_include_directories(vtest PRIVATE libs/glm)
target_link_libraries(vtest glfw)
