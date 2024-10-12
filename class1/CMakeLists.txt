cmake_minimum_required(VERSION 3.5.0)
project(class1 VERSION 0.1.0 LANGUAGES C CXX)

# 生成动态库
add_library(leptjson leptjson.c) 
# 生成可执行文件
add_executable(leptjson_test test.c) 
# 链接动态库
target_link_libraries(leptjson_test leptjson) 
