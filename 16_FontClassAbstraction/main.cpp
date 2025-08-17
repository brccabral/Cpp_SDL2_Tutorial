#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

    constexpr int FPS = 60;
    constexpr int frameDelay = 1000 / FPS;

    if (TTF_Init() == -1)
    {
        fprintf(stderr, "TTF_Init() Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    TTF_Font *font = TTF_OpenFont("assets/fonts/8bitOperatorPlus8-Regular.ttf", 32);
    if (font == nullptr)
    {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, "SDL2 TTF", {0xFF, 0xFF, 0xFF, 0xFF});
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_Rect rectText = {10, 10, surfaceText->w, surfaceText->h};
    SDL_FreeSurface(surfaceText);

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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, textureText, nullptr, &rectText);

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

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(textureText);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
