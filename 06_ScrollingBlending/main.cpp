#include <exception>
#include <SDL2pp/SDL2pp.hh>

int main()
try
{
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window(
            "C++ SDL2 06_ScrollingBlending",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    SDL2pp::Surface surface("images/pool2.bmp");

    SDL2pp::Texture texture1(renderer, surface);
    texture1.SetBlendMode(SDL_BLENDMODE_NONE);

    SDL2pp::Texture texture2(renderer, surface);

    const auto size = texture1.GetSize();
    int w = size.x, h = size.y;

    // rect1 and rect2 will move texture1 Horizontally
    SDL2pp::Rect rectangle1;
    rectangle1.x = 0;
    rectangle1.y = 0;
    rectangle1.w = 640;
    rectangle1.h = 480;

    SDL2pp::Rect rectangle2;
    rectangle2.x = -639;
    rectangle2.y = 0;
    rectangle2.w = 640;
    rectangle2.h = 480;

    // rect3 and rect4 will move texture2 Vertically
    SDL2pp::Rect rectangle3;
    rectangle3.x = 0;
    rectangle3.y = 0;
    rectangle3.w = 640;
    rectangle3.h = 480;

    SDL2pp::Rect rectangle4;
    rectangle4.x = 0;
    rectangle4.y = -480;
    rectangle4.w = 640;
    rectangle4.h = 480;

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
                if (event.key.keysym.scancode == SDL_SCANCODE_R)
                {
                    texture2.SetBlendMode(SDL_BLENDMODE_NONE);
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    texture2.SetBlendMode(SDL_BLENDMODE_ADD);
                }
                else if (event.button.button == SDL_BUTTON_MIDDLE)
                {
                    texture2.SetBlendMode(SDL_BLENDMODE_BLEND);
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    texture2.SetBlendMode(SDL_BLENDMODE_MOD);
                }
            }
        }

        // Update
        // Handle textures scrolling left to right
        rectangle1.x++;
        if (rectangle1.x > 639)
        {
            rectangle1.x = -639;
        }
        rectangle2.x++;
        if (rectangle2.x > 639)
        {
            rectangle2.x = -639;
        }

        rectangle3.y++;
        if (rectangle3.y > 479)
        {
            rectangle3.y = -480;
        }
        rectangle4.y++;
        if (rectangle4.y > 479)
        {
            rectangle4.y = -480;
        }

        // Draw
        // clear screen
        renderer.SetDrawColor(0, 0, 0xFF, SDL_ALPHA_OPAQUE);
        renderer.Clear();

        // draw stuff
        renderer.Copy(texture1, SDL2pp::NullOpt, rectangle1);
        renderer.Copy(texture1, SDL2pp::NullOpt, rectangle2);

        // Scrolling up and down
        renderer.Copy(texture2, SDL2pp::NullOpt, rectangle3);
        renderer.Copy(texture2, SDL2pp::NullOpt, rectangle4);

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
