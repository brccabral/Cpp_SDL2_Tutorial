cmake_minimum_required(VERSION 3.21)
project(SDL2_Tutorial)

include(GNUInstallDirs)

find_package(SDL2 REQUIRED)

add_subdirectory(00_Intro)
add_subdirectory(01_Surface)
add_subdirectory(02_RenderDraw)
add_subdirectory(03_Texture)
add_subdirectory(04_ColorKey)
add_subdirectory(05_Blending)
add_subdirectory(06_ScrollingBlending)
add_subdirectory(07_Fonts)
add_subdirectory(08_Images)
