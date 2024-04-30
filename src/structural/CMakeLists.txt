cmake_minimum_required(VERSION 3.10)

# 为创建型设计模式添加库
file(GLOB Structural_SRC_FILES "*.cpp")
add_library(structural_lib STATIC ${Structural_SRC_FILES})

# 设置库的包含目录
target_include_directories(structural_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
