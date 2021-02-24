cmake_minimum_required(VERSION 3.0)
project(ch2ex2-ocv3)

if(NOT OCV_PATH)
    set(OCV_PATH "")
endif()

find_package(OpenCV 3 REQUIRED PATHS ${OCV_PATH})
add_executable(ch2ex2-ocv3 ch2ex2-ocv3.cpp)
target_include_directories(ch2ex2-ocv3 PUBLIC ${OCV_PATH})
target_link_libraries(ch2ex2-ocv3 ${OpenCV_LIBS})
