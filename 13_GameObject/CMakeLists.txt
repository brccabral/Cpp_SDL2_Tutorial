
add_executable(13_GameObject main.cpp)
target_compile_features(13_GameObject PUBLIC cxx_std_17)
target_link_libraries(13_GameObject PUBLIC sdl2tutorial)

add_custom_command(TARGET 13_GameObject POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 13_GameObject)
