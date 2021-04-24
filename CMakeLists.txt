cmake_minimum_required(VERSION 3.17)
project(projeto2 C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES *.h *.c)

add_executable(projeto2 ${SOURCES})

if(WIN32)
    add_custom_command(
            TARGET projeto2 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/pthread/pthreadVC3.dll
            ${PROJECT_SOURCE_DIR}/cmake-build-debug/pthreadVC3.dll)
    target_include_directories(projeto2 PRIVATE pthread)
    target_link_directories(projeto2 PRIVATE pthread)
    target_link_libraries(projeto2 pthreadVC3)
else()
    target_link_libraries(projeto2 pthread)
endif()
