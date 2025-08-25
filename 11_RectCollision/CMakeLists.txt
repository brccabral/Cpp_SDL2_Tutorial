
add_executable(11_RectCollision main.cpp)
target_compile_features(11_RectCollision PUBLIC cxx_std_17)
target_link_libraries(11_RectCollision PUBLIC sdl2tutorial)

add_custom_command(TARGET 11_RectCollision POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 11_RectCollision)
