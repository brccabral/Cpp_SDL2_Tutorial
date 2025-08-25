
add_executable(20_RotateTexture main.cpp)
target_compile_features(20_RotateTexture PUBLIC cxx_std_17)
target_link_libraries(20_RotateTexture PUBLIC sdl2tutorial)

add_custom_command(TARGET 20_RotateTexture POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 20_RotateTexture)
