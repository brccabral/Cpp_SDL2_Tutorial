
add_executable(14_CollisionComponent main.cpp
               TextureRectangle.cpp
               ResourceManager.cpp
               AnimatedSprite.cpp
               SDLApp.cpp
               GameObject.cpp
)
target_compile_features(14_CollisionComponent PUBLIC cxx_std_17)
target_link_libraries(14_CollisionComponent PUBLIC ${SDL2_LIBRARIES})

add_custom_command(TARGET 14_CollisionComponent POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 14_CollisionComponent)
