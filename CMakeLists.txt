cmake_minimum_required(VERSION 3.17)
project(projeto2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB SOURCES *.h *.c)

add_executable(projeto2 ${SOURCES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})
target_link_libraries(projeto2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

if(WIN32)
    target_include_directories(projeto2 PRIVATE pthread)
    target_link_directories(projeto2 PRIVATE pthread)
    target_link_libraries(projeto2 pthreadVC3)
else()
    target_link_libraries(projeto2 pthread)
endif()

add_custom_command(
    TARGET projeto2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/assets/chef.png
    ${PROJECT_SOURCE_DIR}/cmake-build-debug/assets/chef.png)