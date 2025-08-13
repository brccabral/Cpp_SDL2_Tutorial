#include <glad/gl.h>
#include <SDL2/SDL.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window *window = SDL_CreateWindow(
            "C++ SDL2 Window",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    const int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    bool gameIsRunning = true;
    while (gameIsRunning)
    {
        glViewport(0, 0, 640, 480);
        SDL_Event event;
        // Start our event loop
        while (SDL_PollEvent(&event))
        {
            // Handle each specific event
            if (event.type == SDL_QUIT)
            {
                gameIsRunning = false;
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                printf(
                        "MouseMotion x = %d xrel = %d y = %d yrel = %d\n", event.motion.x,
                        event.motion.xrel, event.motion.y, event.motion.yrel);
            }
            if (event.type == SDL_KEYDOWN)
            {
                printf("KeyDown %d %d\n", event.key.keysym.scancode, event.key.keysym.sym);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    gameIsRunning = false;
                }

            }
        }

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
