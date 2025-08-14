
add_executable(03_Texture main.cpp)
target_compile_features(03_Texture PUBLIC cxx_std_17)
target_link_libraries(03_Texture PUBLIC ${SDL2_LIBRARIES})

install(TARGETS 03_Texture)
