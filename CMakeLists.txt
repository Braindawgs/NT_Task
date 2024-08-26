cmake_minimum_required(VERSION 3.10)
project(NT_Task)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

include_directories(extern)
find_package(SQLite3 REQUIRED)

add_executable(NT_Task
    main.cpp
    smartStorage.cpp
    database.cpp
)

target_link_libraries(NT_Task SQLite::SQLite3)
