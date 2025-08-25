
add_executable(12_SDLAppAbstraction main.cpp)
target_compile_features(12_SDLAppAbstraction PUBLIC cxx_std_17)
target_link_libraries(12_SDLAppAbstraction PUBLIC sdl2tutorial)

add_custom_command(TARGET 12_SDLAppAbstraction POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 12_SDLAppAbstraction)
