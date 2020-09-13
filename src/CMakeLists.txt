cmake_minimum_required(VERSION 2.8)
project( my_elas )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(code_that_works src)
include_directories( "${code_that_works}" )

FILE (GLOB anuelas "src/*.cpp")

set(CMAKE_BUILD_TYPE Release)

add_executable( my_elas ${anuelas} )
target_link_libraries( my_elas ${OpenCV_LIBS} )
