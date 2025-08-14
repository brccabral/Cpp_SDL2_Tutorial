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

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    SDL_Surface *surface = SDL_LoadBMP("images/pool2.bmp");
    if (surface == nullptr)
    {
        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture1 = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture1 == nullptr)
    {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_SetTextureBlendMode(texture1, SDL_BLENDMODE_NONE);

    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture2 == nullptr)
    {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(texture1);
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_FreeSurface(surface);

    int w, h;
    SDL_QueryTexture(texture1, nullptr, nullptr, &w, &h);

    // rect1 and rect2 will move texture1 Horizontally
    SDL_Rect rectangle1;
    rectangle1.x = 0;
    rectangle1.y = 0;
    rectangle1.w = 640;
    rectangle1.h = 480;

    SDL_Rect rectangle2;
    rectangle2.x = -639;
    rectangle2.y = 0;
    rectangle2.w = 640;
    rectangle2.h = 480;

    // rect3 and rect4 will move texture2 Vertically
    SDL_Rect rectangle3;
    rectangle3.x = 0;
    rectangle3.y = 0;
    rectangle3.w = 640;
    rectangle3.h = 480;

    SDL_Rect rectangle4;
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
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_NONE);
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_ADD);
                }
                else if (event.button.button == SDL_BUTTON_MIDDLE)
                {
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND);
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_MOD);
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // draw stuff
        SDL_RenderCopy(renderer, texture1, nullptr, &rectangle1);
        SDL_RenderCopy(renderer, texture1, nullptr, &rectangle2);
        // Scrolling up and down
        SDL_RenderCopy(renderer, texture2, nullptr, &rectangle3);
        SDL_RenderCopy(renderer, texture2, nullptr, &rectangle4);

        // show renderer
        SDL_RenderPresent(renderer);

        // FPS
        const Uint64 frameTime = ((SDL_GetPerformanceCounter() - now) * 1000) /
                                 SDL_GetPerformanceFrequency();
        if (frameDelay > frameTime)
        {
            SDL_Delay((Uint32) (frameDelay - frameTime));
        }
    }

    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
