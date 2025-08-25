#include <exception>
#include <SDL2pp/SDL2pp.hh>

int main()
try
{
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window(
            "C++ SDL2 07_Fonts",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    SDL2pp::SDLTTF ttf;

    SDL2pp::Font font("fonts/8bitOperatorPlus8-Regular.ttf", 32);

    SDL2pp::Surface surfaceText = font.RenderText_Solid("SDL2 TTF", {0xFF, 0xFF, 0xFF, 0xFF});
    SDL2pp::Texture textureText{renderer, surfaceText};
    SDL2pp::Rect rectText = {10, 10, surfaceText.GetWidth(), surfaceText.GetHeight()};

    bool gameIsRunning = true;

    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double deltaTime = 0.0; // seconds

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

        renderer.Copy(textureText, SDL2pp::NullOpt, rectText);

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
