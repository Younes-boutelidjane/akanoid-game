cmake_minimum_required(VERSION 3.5)

project(game_f LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

add_executable(game_p main.cpp header_file.h source_file.cpp)

target_link_libraries(game_p sfml-system sfml-window sfml-graphics sfml-audio)

install(TARGETS game_p
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
