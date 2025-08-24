file(GLOB_RECURSE SDL2TUTORIAL_SOURCES src/*.cpp)
file(GLOB_RECURSE SDL2TUTORIAL_HEADERS include/*.cpp)

add_library(sdl2tutorial)
target_sources(sdl2tutorial
    PRIVATE ${SDL2TUTORIAL_SOURCES}
    PUBLIC
       FILE_SET sdl2tutorial_headers
       TYPE HEADERS
       BASE_DIRS ./include
       FILES ${SDL2TUTORIAL_HEADERS}
)
target_link_libraries(sdl2tutorial PUBLIC SDL2pp::SDL2pp)
