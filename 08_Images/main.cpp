#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <SDL_image.h>

int main()
try
{
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window(
            "C++ SDL2 Window",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    bool gameIsRunning = true;

    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double deltaTime = 0.0; // seconds

    // types of images we want to use
    constexpr int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    // SDL2pp::SDLImage throws exception if any flag not accepted
    SDL2pp::SDLImage sdl_image(flags);

    SDL2pp::Surface image("images/mario.png");

    SDL2pp::Texture texture(renderer, image);

    while (gameIsRunning)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double) ((now - last) * 1000) / SDL_GetPerformanceFrequency();
        deltaTime /= 1000.0; // convert ms to seconds

        SDL_Event event;
        int mouseX, mouseY;
        Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

        // Input
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

        // Draw
        // clear screen
        renderer.SetDrawColor(0, 0, 0xFF, SDL_ALPHA_OPAQUE);
        renderer.Clear();

        renderer.Copy(texture, SDL2pp::NullOpt, SDL2pp::NullOpt);

        // show renderer
        renderer.Present();

        // FPS
        const Uint64 frameTime = ((SDL_GetPerformanceCounter() - now) * 1000) /
                                 SDL_GetPerformanceFrequency();
        if (frameDelay > frameTime)
        {
            SDL_Delay((Uint32) (frameDelay - frameTime));
        }
    }

    return 0;
}
catch (std::exception &e)
{
    fprintf(stderr, "Error: %s\n", e.what());
    return 1;
}
