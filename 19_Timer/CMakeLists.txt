
add_executable(19_Timer main.cpp)
target_compile_features(19_Timer PUBLIC cxx_std_17)
target_link_libraries(19_Timer PUBLIC sdl2tutorial)

add_custom_command(TARGET 19_Timer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

install(TARGETS 19_Timer)
