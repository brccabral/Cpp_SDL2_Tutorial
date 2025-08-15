
add_executable(12_SDLAppAbstraction main.cpp
               TextureRectangle.cpp
               ResourceManager.cpp
               AnimatedSprite.cpp
)
target_compile_features(12_SDLAppAbstraction PUBLIC cxx_std_17)
target_link_libraries(12_SDLAppAbstraction PUBLIC ${SDL2_LIBRARIES})

add_custom_command(TARGET 12_SDLAppAbstraction POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 12_SDLAppAbstraction)
