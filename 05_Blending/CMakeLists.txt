
add_executable(05_Blending main.cpp)
target_compile_features(05_Blending PUBLIC cxx_std_17)
target_link_libraries(05_Blending PUBLIC SDL2pp::SDL2pp)

add_custom_command(TARGET 05_Blending POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 05_Blending)
