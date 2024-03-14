cmake_minimum_required(VERSION 3.26)
# 添加文件夹下所有文件当作GlobalType变量值
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} GlobalType)
# 将所有文件放入GLOBAL_TYPE_SRC全局变量内
set(GLOBAL_TYPE_SRC ${GlobalType} PARENT_SCOPE)
# 全局定义完成
message("Global type define OK!")