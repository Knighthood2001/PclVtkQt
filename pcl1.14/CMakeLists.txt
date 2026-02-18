cmake_minimum_required(VERSION 3.5)

project(PCLTest)

# 设置PCL路径
set(PCL_DIR "C:/Program Files/PCL 1.14.0")

# 查找PCL
find_package(PCL REQUIRED)

# 添加可执行文件
add_executable(PCLTest PCL_Test.cpp)

# 链接库
target_link_libraries(PCLTest ${PCL_LIBRARIES})