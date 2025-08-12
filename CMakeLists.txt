cmake_minimum_required(VERSION 3.21)
project(SDL2_Tutorial)

include(GNUInstallDirs)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp extras/glad/src/gl.c)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC extras/glad/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})

install(TARGETS ${PROJECT_NAME})
