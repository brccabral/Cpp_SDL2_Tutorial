
add_executable(16_FontClassAbstraction main.cpp)
target_compile_features(16_FontClassAbstraction PUBLIC cxx_std_17)
target_link_libraries(16_FontClassAbstraction PUBLIC ${SDL2_LIBRARIES} SDL2_ttf)

add_custom_command(TARGET 16_FontClassAbstraction POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

install(TARGETS 16_FontClassAbstraction)
