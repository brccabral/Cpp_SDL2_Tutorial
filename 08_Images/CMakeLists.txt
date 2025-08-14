
add_executable(08_Images main.cpp)
target_compile_features(08_Images PUBLIC cxx_std_17)
target_link_libraries(08_Images PUBLIC ${SDL2_LIBRARIES})

add_custom_command(TARGET 08_Images POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 08_Images)
