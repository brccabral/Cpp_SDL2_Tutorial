
add_executable(01_Surface main.cpp)
target_compile_features(01_Surface PUBLIC cxx_std_17)
target_link_libraries(01_Surface PUBLIC ${SDL2_LIBRARIES})

install(TARGETS 01_Surface)
