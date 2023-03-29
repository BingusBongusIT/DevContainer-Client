cmake_minimum_required(VERSION 3.20)
project(CC-Client)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADER_FILES "header/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})