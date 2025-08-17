
add_executable(15_Audio main.cpp
               TextureRectangle.cpp
               ResourceManager.cpp
               AnimatedSprite.cpp
               SDLApp.cpp
               GameObject.cpp
               Collider2D.cpp
)
target_compile_features(15_Audio PUBLIC cxx_std_17)
target_link_libraries(15_Audio PUBLIC ${SDL2_LIBRARIES})

add_custom_command(TARGET 15_Audio POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

install(TARGETS 15_Audio)
