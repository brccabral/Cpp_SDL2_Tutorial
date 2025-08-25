#include <string>
#include <sdl2tutorial/SDL2Tutorial.hpp>


int main()
try
{
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window(
            "C++ SDL2 10_SpriteAnimation",
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

    AnimatedSprite animated_sprite(renderer, "images/edited.bmp");
    animated_sprite.Draw(200, 200, 150, 150);

    static int frameNumber = 0;

    while (gameIsRunning)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double) ((now - last) * 1000) / SDL_GetPerformanceFrequency();
        deltaTime /= 1000.0; // convert ms to seconds

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
            }
        }

        // clear screen
        renderer.SetDrawColor(0, 0, 0, SDL_ALPHA_OPAQUE);
        renderer.Clear();

        // draw stuff
        renderer.SetDrawColor(255, 0, 0, SDL_ALPHA_OPAQUE);
        renderer.DrawLine(10, 10, mouseX, mouseY);

        animated_sprite.PlayFrame(0, 0, 170, 110, frameNumber);
        animated_sprite.Render(renderer);
        frameNumber++;
        if (frameNumber > 6)
        {
            frameNumber = 0;
        }

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

    ResourceManager::Destroy();

    return 0;
}
catch (std::exception &e)
{
    fprintf(stderr, "Error: %s\n", e.what());
    return 1;
}
