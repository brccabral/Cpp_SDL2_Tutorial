#include <exception>
#include  <SDL2pp/SDL2pp.hh>

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
try
{
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window(
            "C++ SDL2 01_Surface",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);

    SDL2pp::Surface screen = window.GetSurface();

    SDL2pp::Surface image("images/demo.bmp");

    SDL2pp::Optional<SDL2pp::Rect> dstrect = SDL2pp::NullOpt;
    image.Blit(SDL2pp::NullOpt, screen, dstrect);

    window.UpdateSurface();

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
                SetPixel(screen.Get(), mouseX, mouseY, 0, 0, 255);
            }
        }
        window.UpdateSurface();
    }

    return 0;
}
catch (std::exception &e)
{
    fprintf(stderr, "Error: %s\n", e.what());
    return 1;
}

