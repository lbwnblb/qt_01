cmake_minimum_required(VERSION 3.16)
project(qt_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

list(APPEND CMAKE_PREFIX_PATH "E:/Qt/6.11.0/msvc2022_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

qt_add_executable(qt_01 WIN32
    main.cpp
    LoginWindow.h
    LoginWindow.cpp
    LeftPanel.h
    LeftPanel.cpp
    RightPanel.h
    RightPanel.cpp
    RegisterPanel.h
    RegisterPanel.cpp
)
target_link_libraries(qt_01 PRIVATE Qt6::Widgets Qt6::Network)