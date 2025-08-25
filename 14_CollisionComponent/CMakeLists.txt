
add_executable(14_CollisionComponent main.cpp)
target_compile_features(14_CollisionComponent PUBLIC cxx_std_17)
target_link_libraries(14_CollisionComponent PUBLIC sdl2tutorial)

add_custom_command(TARGET 14_CollisionComponent POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
)

install(TARGETS 14_CollisionComponent)
