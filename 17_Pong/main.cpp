#include <SDL2/SDL.h>

#include "DynamicText.hpp"
#include "GameObject.hpp"
#include "TextureRectangle.h"
#include "SDLApp.hpp"
#include "Sound.hpp"

class MyGame : public SDLApp
{
public:

    MyGame(
            const Uint32 subsystemFlags, const char *title, const int x, const int y, const int w,
            const int h) :
        SDLApp(subsystemFlags, title, x, y, w, h), left_paddle(GetRenderer()),
        right_paddle(GetRenderer()), ball(GetRenderer()),
        collision_sound("assets/sounds/Collide.wav"),
        score_sound("assets/sounds/Score.wav"),
        left_score_text("assets/fonts/8bitOperatorPlus8-Regular.ttf", 32),
        right_score_text("assets/fonts/8bitOperatorPlus8-Regular.ttf", 16)
    {
        int index = 0;

        left_paddle.SetTextureRect("assets/images/leftpaddle.bmp");
        left_paddle.GetTextureRectangle().SetDimensions(20, 200);

        index = left_paddle.AddCollider2D();
        left_paddle.GetCollider2D(index).SetRelPosition(0, 0);
        left_paddle.GetCollider2D(index).SetDimensions(20, 200);

        left_paddle.SetPosition(10, 200);

        right_paddle.SetTextureRect("assets/images/rightpaddle.bmp");
        right_paddle.GetTextureRectangle().SetDimensions(20, 200);

        index = right_paddle.AddCollider2D();
        right_paddle.GetCollider2D(index).SetRelPosition(0, 0);
        right_paddle.GetCollider2D(index).SetDimensions(20, 200);

        right_paddle.SetPosition(610, 200);

        ball.SetTextureRect("assets/images/ball.bmp");
        ball.GetTextureRectangle().SetDimensions(20, 20);

        index = ball.AddCollider2D();
        ball.GetCollider2D(index).SetRelPosition(0, 0);
        ball.GetCollider2D(index).SetDimensions(20, 20);

        ball.SetPosition(GetWindowWidth() / 2 - 10, GetWindowHeight() / 2 - 10);

        collision_sound.SetupDevice();
        score_sound.SetupDevice();

        left_score_text.SetText(renderer, "SDL2 Tutorial", {0xFF, 0xFF, 0xFF, 0xFF});
        left_score_text.SetPosition({0, 0, 100, 50});
        right_score_text.SetText(renderer, "Message", {0xFF, 0xFF, 0xFF, 0xFF});
        right_score_text.SetPosition({300, 300, 200, 50});
    }

    void EventCallback() override
    {
        static SDL_Event event;
        // Start our event loop
        while (SDL_PollEvent(&event))
        {
            // Handle each specific event
            if (event.type == SDL_QUIT)
            {
                StopGame();
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    StopGame();
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                if (left_paddle.IsColliding(right_paddle.GetAllColliders()))
                {
                    collision_sound.Play();
                }
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                right_paddle.SetPosition(GetMouseX(), GetMouseY());
            }
        }
    }

    void RenderCallback() override
    {
        // draw stuff
        SDL_SetRenderDrawColor(GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(GetRenderer(), 10, 10, GetMouseX(), GetMouseY());

        left_paddle.Render();
        right_paddle.Render();

        left_score_text.Render(renderer);
        right_score_text.Render(renderer);
    }

    void UpdateCallback(const double deltaTime) override
    {
        const auto obj1Rect = left_paddle.GetTextureRectangle().GetDestRect();
        static double obj1SpeedX = 1;
        static double obj1SpeedY = 1;
        static double x = obj1Rect.x;
        static double y = obj1Rect.y;

        if (obj1Rect.x > 640 || obj1Rect.x < 0)
        {
            obj1SpeedX = -1;
        }
        if (obj1Rect.y > 480 || obj1Rect.y < 0)
        {
            obj1SpeedY = -1;
        }
        x += obj1SpeedX * 60 * deltaTime;
        y += obj1SpeedY * 60 * deltaTime;
        left_paddle.SetPosition(x, y);

        left_paddle.Update(deltaTime);
        right_paddle.Update(deltaTime);
    }

private:

    GameObject left_paddle{};
    GameObject right_paddle{};
    GameObject ball{};

    Sound collision_sound{};
    Sound score_sound{};

    Uint32 left_score{};
    DynamicText left_score_text{};
    Uint32 right_score{};
    DynamicText right_score_text{};

    float movement_speed{5.0f};
    float ball_speed{2.0f};
    SDL_Point ball_direction{};
};

int main()
{
    {
        MyGame app(SDL_INIT_VIDEO | SDL_INIT_AUDIO, "SDL2 App Abstraction", 20, 20, 640, 480);
        app.SetFPS(60);
        app.RunLoop();
    }

    return 0;
}
