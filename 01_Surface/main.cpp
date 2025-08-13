#include <SDL2/SDL.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
            "C++ SDL2 Window",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_Surface *image = SDL_LoadBMP("images/demo.bmp");
    if (image == nullptr)
    {
        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_BlitSurface(image, nullptr, screen, nullptr);
    SDL_FreeSurface(image);

    SDL_UpdateWindowSurface(window);

    bool gameIsRunning = true;
    while (gameIsRunning)
    {
        SDL_Event event;
        // Start our event loop
        while (SDL_PollEvent(&event))
        {
            // Handle each specific event
            if (event.type == SDL_QUIT)
            {
                gameIsRunning = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    gameIsRunning = false;
                }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
