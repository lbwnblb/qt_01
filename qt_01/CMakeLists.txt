cmake_minimum_required(VERSION 3.16)
project(qianniu_login LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# 如果Qt不在默认路径，请取消注释并修改下面这行
list(APPEND CMAKE_PREFIX_PATH "E:/Qt/6.11.0/msvc2022_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(qianniu_login main.cpp)
target_link_libraries(qianniu_login PRIVATE Qt6::Widgets)