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

    SDL_Surface *surface = SDL_LoadBMP("images/test.bmp");
    if (surface == nullptr)
    {
        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_FreeSurface(surface);

    // image destination
    constexpr SDL_Rect rect = {50, 50, 150, 150};
    SDL_Rect mouse_rect = {0, 0, 150, 150};

    // center = rotating point from destination rect position
    constexpr SDL_Point center = {rect.w / 2, rect.h / 2};

    bool gameIsRunning = true;

    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double deltaTime = 0.0; // seconds

    constexpr int FPS = 60;
    constexpr int frameDelay = 1000 / FPS;

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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // draw stuff
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &rect);

        SDL_Rect intersection;
        if (SDL_IntersectRect(&rect, &mouse_rect, &intersection))
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &intersection);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderDrawRect(renderer, &mouse_rect);

        static double angle = 0;
        angle += 1;
        SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, &center, SDL_FLIP_NONE);

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

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
