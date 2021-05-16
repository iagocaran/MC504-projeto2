cmake_minimum_required(VERSION 3.17)
project(projeto2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB SOURCES *.h *.c)

add_executable(projeto2 ${SOURCES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(projeto2 ${SDL2_LIBRARIES})

if(WIN32)
    find_package(SDL2_image REQUIRED)
    include_directories(${SDL2_IMAGE_DIRS}) 
    target_include_directories(projeto2 PRIVATE pthread)
    target_link_directories(projeto2 PRIVATE pthread)
    target_link_libraries(projeto2 pthreadVC3 ${SDL2_IMAGE_LIBRARIES})
elseif(APPLE)
    target_include_directories(projeto2 PRIVATE /usr/local/include/SDL2)
    target_link_directories(projeto2 PRIVATE /usr/local/lib)
    target_link_libraries(projeto2 SDL2_image)
else()
    target_link_libraries(projeto2 pthread)
endif()

file(INSTALL assets DESTINATION ${CMAKE_BINARY_DIR})