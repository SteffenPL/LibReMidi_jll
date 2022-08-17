project(TestLib)

set(CMAKE_PREFIX_PATH /home/plunder/.julia/artifacts/46f8f1e48b3bed25ce3eb08a3bb43461f0980b82)

cmake_minimum_required(VERSION 3.4)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

find_package(JlCxx)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

message(STATUS "Found JlCxx at ${JlCxx_location}")

add_library(testlib SHARED src/demo.cpp)

target_link_libraries(testlib JlCxx::cxxwrap_julia)

install(TARGETS
  testlib
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib
RUNTIME DESTINATION lib)