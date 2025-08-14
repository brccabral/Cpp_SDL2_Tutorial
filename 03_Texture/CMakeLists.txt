
add_executable(03_Texture main.cpp)
target_compile_features(03_Texture PUBLIC cxx_std_17)
target_link_libraries(03_Texture PUBLIC ${SDL2_LIBRARIES})

add_custom_command(TARGET 03_Texture POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 03_Texture)
