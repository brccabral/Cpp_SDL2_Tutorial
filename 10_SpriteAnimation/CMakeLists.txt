
add_executable(10_SpriteAnimation main.cpp
               TextureRectangle.cpp
               ResourceManager.cpp
)
target_compile_features(10_SpriteAnimation PUBLIC cxx_std_17)
target_link_libraries(10_SpriteAnimation PUBLIC ${SDL2_LIBRARIES})

add_custom_command(TARGET 10_SpriteAnimation POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 10_SpriteAnimation)
