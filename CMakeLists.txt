cmake_minimum_required(VERSION 2.8)
project(min-HPSF)

set(CMAKE_VERBOSE_MAKEFILE ON) # 显示详细输出
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -g -std=c++11 -Wall -Wno-deprecated - Werror -Wno-unused-function")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") # 编译时优化, 影响debug

set(LIB_LOG
    src/log.cc
    )

# add_library(sylar SHARED ${LIB_LOG}) # 生成.so库文件

include_directories(include)
add_executable(mytest ${LIB_LOG} tests/test.cc)
# add_dependencies(mytest sylar)
# target_link_libraries(mytest sylar)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib})