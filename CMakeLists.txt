cmake_minimum_required(VERSION 3.0)
project(cardio)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 2)

add_subdirectory(dmz)
include_directories(dmz)

add_executable(main main.cpp)
target_link_libraries(main dmz ${OpenCV_LIBRARIES})

add_custom_target(cardio ALL
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND python setup.py build_ext -b build
        DEPENDS dmz)
