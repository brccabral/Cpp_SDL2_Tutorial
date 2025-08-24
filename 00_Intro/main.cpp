#include <glad/glad.h>
#include <sdl/sdl_cpp.h>

int main()
{
    sdl::Context ctx;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    const sdl::Window window{"C++ SDL2 Window", sdl::Size{640, 480},
                             SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL};

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr)
    {
        fprintf(stderr, "SDL_GL_CreateContext Error: %s\n", SDL_GetError());
        return 1;
    }

    // GLAD Option 1
    // const int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    // printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    // GLAD Option 2
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        fprintf(stderr, "gladLoadGLLoader Error: %u\n", glGetError());
        return 1;
    }
    printf("GL %d.%d\n", GLVersion.major, GLVersion.minor);

    bool gameIsRunning = true;
    // Event handler
    sdl::EventHandler handler;
    handler.on_quit(
            [&gameIsRunning]()
            {
                gameIsRunning = false;
            });
    handler.on_press(
            sdl::KeyCode::Esc, [&gameIsRunning]()
            {
                gameIsRunning = false;
            });
    handler.on_press(
            sdl::KeyCode::Right, [&gameIsRunning]()
            {
                printf("Right key pressed\n");
            });
    handler.on_motion(
            [](const sdl::s32 x, const sdl::s32 y, const sdl::s32 dx, const sdl::s32 dy)
            {
                printf("MouseMotion x = %d xrel = %d y = %d yrel = %d\n", x, dx, y, dy);
            });

    const auto &mouse_handler = handler.get<sdl::MouseStateHandler>();

    while (gameIsRunning)
    {
        glViewport(0, 0, 640, 480);
        const auto mouse_state = mouse_handler.state();
        const auto mouse_coords = mouse_state.coords();

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
        handler.update();
    }

    SDL_GL_DeleteContext(context);

    return 0;
}
