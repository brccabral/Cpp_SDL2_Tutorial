
add_executable(01_Surface main.cpp)
target_compile_features(01_Surface PUBLIC cxx_std_17)
target_link_libraries(01_Surface PUBLIC SDL2pp::SDL2pp)

add_custom_command(TARGET 01_Surface POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 01_Surface)
