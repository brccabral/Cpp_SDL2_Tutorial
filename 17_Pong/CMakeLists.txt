
add_executable(17_Pong main.cpp)
target_compile_features(17_Pong PUBLIC cxx_std_17)
target_link_libraries(17_Pong PUBLIC sdl2tutorial)

add_custom_command(TARGET 17_Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

install(TARGETS 17_Pong)
