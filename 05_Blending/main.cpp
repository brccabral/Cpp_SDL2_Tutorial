#include <exception>
#include <SDL2pp/SDL2pp.hh>

int main()
try
{
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window(
            "C++ SDL2 05_Blending",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL2pp::Surface surface("images/kong.bmp");

    // make color 0xFF00FF transparent
    surface.SetColorKey(true, SDL_MapRGB(surface.Get()->format, 0xFF, 0, 0xFF));

    SDL2pp::Texture texture(renderer, surface);

    // image destination
    SDL_Rect rect = {50, 50, 150, 150};
    SDL_Rect rect2 = {50, 50, 150, 150};

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
            if (event.type == SDL_MOUSEMOTION)
            {
                rect2.x = event.motion.x;
                rect2.y = event.motion.y;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    texture.SetBlendMode(SDL_BLENDMODE_ADD);
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    texture.SetBlendMode(SDL_BLENDMODE_BLEND);
                }
                else if (event.button.button == SDL_BUTTON_MIDDLE)
                {
                    texture.SetBlendMode(SDL_BLENDMODE_MOD);
                }
            }
            else
            {
                texture.SetBlendMode(SDL_BLENDMODE_NONE);
            }
        }

        // clear screen
        renderer.SetDrawColor(0, 0, 0xFF, SDL_ALPHA_OPAQUE);
        renderer.Clear();

        // draw stuff
        renderer.SetDrawColor(255, 0, 0, SDL_ALPHA_OPAQUE);
        renderer.DrawLine(10, 10, mouseX, mouseY);

        renderer.Copy(texture, SDL2pp::NullOpt, rect);
        renderer.Copy(texture, SDL2pp::NullOpt, rect2);

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
