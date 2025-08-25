
add_executable(18_Mixer main.cpp)
target_compile_features(18_Mixer PUBLIC cxx_std_17)
target_link_libraries(18_Mixer PUBLIC sdl2tutorial)

add_custom_command(TARGET 18_Mixer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

install(TARGETS 18_Mixer)
