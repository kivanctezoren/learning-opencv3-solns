cmake_minimum_required(VERSION 3.0)
project(ch2ex5-ocv4)

if(NOT OCV_PATH)
    set(OCV_PATH "")
endif()

find_package(OpenCV 4 REQUIRED PATHS ${OCV_PATH})
add_executable(ch2ex5-ocv4 ch2ex5-ocv4.cpp)
target_include_directories(ch2ex5-ocv4 PUBLIC ${OCV_PATH})
target_link_libraries(ch2ex5-ocv4 ${OpenCV_LIBS})
