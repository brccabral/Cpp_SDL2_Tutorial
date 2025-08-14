
add_executable(07_Fonts main.cpp)
target_compile_features(07_Fonts PUBLIC cxx_std_17)
target_link_libraries(07_Fonts PUBLIC ${SDL2_LIBRARIES} SDL2_ttf)

add_custom_command(TARGET 07_Fonts POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/fonts ${CMAKE_CURRENT_BINARY_DIR}/fonts
)

install(TARGETS 07_Fonts)
