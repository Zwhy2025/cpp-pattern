# !/bin/bash

# 检查时候含有build bin lib等文件夹，如果有则删除
if [ -d "build" ] || [ -d "bin" ] || [ -d "lib" ]; then
    echo "build/ or bin/ or lib/ 文件夹已经存在，删除..."
    rm -rf build bin lib
fi



echo "*********************** 构建 ***********************"
mkdir build && cd build && cmake ..
if [ $? -ne 0 ]; then
    echo "构建失败，退出."
    exit 1
fi

echo "*********************** 编译 ***********************"
make -j 16
if [ $? -ne 0 ]; then
    echo "编译失败，退出."
    exit 2
fi


echo "*********************** 运行 ***********************"
cd ../bin && ./display_pattern
if [ $? -ne 0 ]; then
    echo "运行失败."
    exit 3
fi

echo "finished."
exit 0
