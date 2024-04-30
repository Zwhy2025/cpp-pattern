cmake_minimum_required(VERSION 3.10)
project(DesignPatterns)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置共享库,静态库的输出路径
# 注意CMakelists的继承顺序，先设置输出路径，再添加子目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(src)

# 临时办法，想要把所有设计模式实现写在一个cpp文件里面
include_directories(src)

# 创建可执行文件
add_executable(display_pattern src/patterns.cpp)
target_link_libraries(display_pattern behavioral_lib creational_lib structural_lib)
