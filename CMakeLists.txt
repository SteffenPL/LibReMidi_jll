project(jllibremidi)

cmake_minimum_required(VERSION 3.4)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

find_package(JlCxx)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")
message(STATUS "Found JlCxx at ${JlCxx_location}")

add_subdirectory(extern/libremidi)

add_library(jllibremidi SHARED src/libremidi_cxxwrap.cpp)

target_link_libraries(jllibremidi JlCxx::cxxwrap_julia libremidi)

install(TARGETS
jllibremidi
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib
RUNTIME DESTINATION lib)
