cmake_minimum_required(VERSION 3.10)

# 为行为型设计模式添加库
file(GLOB Behavioral_SRC_FILES "*.cpp")
add_library(behavioral_lib STATIC ${Behavioral_SRC_FILES})

# 设置库的包含目录
target_include_directories(behavioral_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
