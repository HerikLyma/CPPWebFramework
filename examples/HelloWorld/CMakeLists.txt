
cmake_minimum_required(VERSION 3.1.1)
project(HelloWorld)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED REQUIRED)


add_subdirectory(../../CPPWebFramework CPPWebFramework)
include_directories(.
    ../../CPPWebFramework/
    ${CMAKE_CURRENT_BINARY_DIR}
)


add_executable(${PROJECT_NAME} main.cpp )

target_link_libraries(${PROJECT_NAME} Qt5::Core  CPPWebFramework)
