
add_executable(15_Audio main.cpp)
target_compile_features(15_Audio PUBLIC cxx_std_17)
target_link_libraries(15_Audio PUBLIC sdl2tutorial)

add_custom_command(TARGET 15_Audio POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

install(TARGETS 15_Audio)
