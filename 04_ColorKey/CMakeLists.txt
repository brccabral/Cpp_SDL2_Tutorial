
add_executable(04_ColorKey main.cpp)
target_compile_features(04_ColorKey PUBLIC cxx_std_17)
target_link_libraries(04_ColorKey PUBLIC SDL2pp::SDL2pp)

add_custom_command(TARGET 04_ColorKey POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 04_ColorKey)
