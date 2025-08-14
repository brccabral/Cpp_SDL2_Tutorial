
add_executable(09_TextureClassAbstraction main.cpp
               TextureRectangle.cpp)
target_compile_features(09_TextureClassAbstraction PUBLIC cxx_std_17)
target_link_libraries(09_TextureClassAbstraction PUBLIC ${SDL2_LIBRARIES})

add_custom_command(TARGET 09_TextureClassAbstraction POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 09_TextureClassAbstraction)
