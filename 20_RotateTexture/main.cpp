#include <sdl2tutorial/SDL2Tutorial.hpp>


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

    SDL2pp::Surface surface{"images/test.bmp"};

    SDL2pp::Texture texture{renderer, surface};

    // image destination
    constexpr SDL2pp::Rect rect{50, 50, 150, 150};
    SDL2pp::Rect mouse_rect{0, 0, 150, 150};

    // center = rotating point from destination rect position
    constexpr SDL2pp::Point center{rect.w / 2, rect.h / 2};

    while (gameIsRunning)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double) ((now - last) * 1000) / SDL_GetPerformanceFrequency();
        deltaTime /= 1000.0; // convert ms to seconds

        SDL_Event event;
        int mouseX, mouseY;
        Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);
        mouse_rect.x = mouseX;
        mouse_rect.y = mouseY;

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
            }
        }

        // clear screen
        renderer.SetDrawColor(0, 0, 0, SDL_ALPHA_OPAQUE);
        renderer.Clear();

        // draw stuff
        renderer.SetDrawColor(255, 255, 255, SDL_ALPHA_OPAQUE);
        renderer.DrawRect(rect);

        SDL2pp::Optional<SDL2pp::Rect> intersection;
        if ((intersection = rect.GetIntersection(mouse_rect)))
        {
            renderer.SetDrawColor(255, 0, 255, SDL_ALPHA_OPAQUE);
            renderer.DrawRect(intersection.value());
            renderer.SetDrawColor(255, 0, 0, SDL_ALPHA_OPAQUE);
        }
        renderer.DrawRect(mouse_rect);

        static double angle = 0;
        angle += 1;
        renderer.Copy(texture, SDL2pp::NullOpt, rect, angle, center, SDL_FLIP_NONE);

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
