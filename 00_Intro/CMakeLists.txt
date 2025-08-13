
add_executable(00_Intro main.cpp ${PROJECT_SOURCE_DIR}/extras/glad/src/glad.c)
target_compile_features(00_Intro PUBLIC cxx_std_17)
target_include_directories(00_Intro PUBLIC ${PROJECT_SOURCE_DIR}/extras/glad/include)
target_link_libraries(00_Intro PUBLIC ${SDL2_LIBRARIES})

install(TARGETS 00_Intro)
