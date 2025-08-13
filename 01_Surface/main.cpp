#include <SDL2/SDL.h>

void SetPixel(
        SDL_Surface *surface, const Uint32 x, const Uint32 y, const Uint8 r, const Uint8 g,
        const Uint8 b)
{
    // lock surface to avoid other threads to modify it
    SDL_LockSurface(surface);
    auto *pixels = (Uint8 *) surface->pixels;
    // pay attention to the format (RGB, BGRA, etc).
    pixels[y * surface->pitch + x * surface->format->BytesPerPixel] = b;
    pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 1] = g;
    pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 2] = r;
    SDL_UnlockSurface(surface);
}

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
        int mouseX, mouseY;
        Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

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
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                printf("Mouse Left pressed x = %d y = %d\n", mouseX, mouseY);
                SetPixel(screen, mouseX, mouseY, 0, 0, 255);
            }
        }
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
