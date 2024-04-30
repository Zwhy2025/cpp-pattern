cmake_minimum_required(VERSION 3.10)

# 为创建型设计模式添加库
file(GLOB Creational_SRC_FILES "*.cpp")
add_library(creational_lib STATIC ${Creational_SRC_FILES})

# 设置库的包含目录
target_include_directories(creational_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
