cmake_minimum_required(VERSION 3.10)
project(RMArmor)
# 设置C++版本为C17
set(CMAKE_CXX_STANDARD 17)
# 设置OpenCV的目录
set(OpenCV_DIR E:/opencv/build/install/x64/mingw/lib)
# 寻找必要文件
find_package(OpenCV REQUIRED)
# 导入OpenCV的头
include_directories(${OpenCV_INCLUDE_DIRS})
# 添加子目录(需要为文件夹名) GlobalType
add_subdirectory(GlobalType)
add_subdirectory(Algorithm)
# 添加构建项目
add_executable(RMArmor main.cpp
        GlobalDef.hpp ${GLOBAL_TYPE_SRC} ${ALGORITHM_SRC})
# 连接动态链接库
target_link_libraries(RMArmor ${OpenCV_LIBS})
