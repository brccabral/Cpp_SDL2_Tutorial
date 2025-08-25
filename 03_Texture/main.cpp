#include <exception>
#include <SDL2pp/SDL2pp.hh>

int main()
try
{
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window(
            "C++ SDL2 03_Texture",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL2pp::Surface surface("images/test.bmp");

    SDL2pp::Texture texture(renderer, surface);

    // image destination
    SDL2pp::Rect rect{50, 50, 150, 150};

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
            }
        }

        // clear screen
        renderer.SetDrawColor(0, 0, 0, SDL_ALPHA_OPAQUE);
        renderer.Clear();

        // draw stuff
        renderer.SetDrawColor(255, 0, 0, SDL_ALPHA_OPAQUE);
        renderer.DrawLine(10, 10, mouseX, mouseY);

        renderer.Copy(texture, SDL2pp::NullOpt, rect);

        // show renderer
        renderer.Present();
    }

    return 0;
}
catch (std::exception &e)
{
    fprintf(stderr, "Error: %s\n", e.what());
    return 1;
}
