cmake_minimum_required(VERSION 3.16)
project(featExtractor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
include_directories(include ${OpenCV_INCLUDE_DIRS})

add_executable(featExtractor
    src/main.cpp
    src/dataset.cpp
    src/preprocessing.cpp
    src/features.cpp
    src/csv_writer.cpp
)

target_link_libraries(featExtractor ${OpenCV_LIBS} stdc++fs)