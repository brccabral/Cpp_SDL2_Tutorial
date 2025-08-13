
add_executable(02_RenderDraw main.cpp)
target_compile_features(02_RenderDraw PUBLIC cxx_std_17)
target_link_libraries(02_RenderDraw PUBLIC ${SDL2_LIBRARIES})

install(TARGETS 02_RenderDraw)
