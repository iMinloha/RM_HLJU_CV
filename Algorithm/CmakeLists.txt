cmake_minimum_required(VERSION 3.10)
# 添加文件夹下所有文件当作GlobalType变量值
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} Algorithm)
# 将所有文件放入GLOBAL_TYPE_SRC全局变量内
set(ALGORITHM_SRC ${Algorithm} PARENT_SCOPE)
# 全局定义完成
message("Algorithm define OK!")