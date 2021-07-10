cmake_minimum_required(VERSION 2.8)
project(min-HPSF)

set(CMAKE_VERBOSE_MAKEFILE ON) # 显示详细输出
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -g -std=c++11 -Wall -Wno-deprecated - Werror -Wno-unused-function")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") # 编译时优化, 影响debug

set(LIB_SRC
    src/log_level.cc src/log_event.cc
    src/log_appender.cc src/log_stdout_appender.cc src/log_file_appender.cc
    src/log_formatter.cc src/log_format_item.cc
    src/logger.cc
    )
# aux_source_directory(src LIB_SRC)

# add_library(lib_log SHARED ${LIB_SRC}) # 生成.so库文件
# add_library(log STATIC ${LIB_SRC})
# set_target_properties()

include_directories(include)
add_executable(test_exe ${LIB_SRC} tests/test.cc)
# add_dependencies(test_exe lib_log)
# target_link_libraries(test_exe lib_log)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib})