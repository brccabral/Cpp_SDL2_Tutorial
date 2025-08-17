
add_executable(19_Timer main.cpp
               TextureRectangle.cpp
               ResourceManager.cpp
               AnimatedSprite.cpp
               SDLApp.cpp
               GameObject.cpp
               Collider2D.cpp
               Sound.cpp
               DynamicText.cpp
               Music.cpp
)
target_compile_features(19_Timer PUBLIC cxx_std_17)
target_link_libraries(19_Timer PUBLIC ${SDL2_LIBRARIES} SDL2_ttf SDL2_mixer)

add_custom_command(TARGET 19_Timer POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

install(TARGETS 19_Timer)
