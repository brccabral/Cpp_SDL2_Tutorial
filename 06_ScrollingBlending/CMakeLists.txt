
add_executable(06_ScrollingBlending main.cpp)
target_compile_features(06_ScrollingBlending PUBLIC cxx_std_17)
target_link_libraries(06_ScrollingBlending PUBLIC SDL2pp::SDL2pp)

add_custom_command(TARGET 06_ScrollingBlending POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 06_ScrollingBlending)
