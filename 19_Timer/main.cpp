#include <SDL2/SDL.h>

#include "DynamicText.hpp"
#include "GameObject.hpp"
#include "Music.hpp"
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
        right_score_text("assets/fonts/8bitOperatorPlus8-Regular.ttf", 32),
        main_music("assets/music/guitarchords.mp3")
    {
        int index = 0;

        left_paddle.SetTextureRect("assets/images/leftpaddle.bmp");
        left_paddle.GetTextureRectangle().SetDimensions(20, 200);

        index = left_paddle.AddCollider2D();
        left_paddle.GetCollider2D(index).SetRelPosition(0, 0);
        left_paddle.GetCollider2D(index).SetDimensions(20, 200);

        left_paddle.SetPosition(10, 200);
        left_paddle.Update(0);

        right_paddle.SetTextureRect("assets/images/rightpaddle.bmp");
        right_paddle.GetTextureRectangle().SetDimensions(20, 200);

        index = right_paddle.AddCollider2D();
        right_paddle.GetCollider2D(index).SetRelPosition(0, 0);
        right_paddle.GetCollider2D(index).SetDimensions(20, 200);

        right_paddle.SetPosition(610, 200);
        right_paddle.Update(0);

        ball.SetTextureRect("assets/images/ball.bmp");
        ball.GetTextureRectangle().SetDimensions(20, 20);

        index = ball.AddCollider2D();
        ball.GetCollider2D(index).SetRelPosition(0, 0);
        ball.GetCollider2D(index).SetDimensions(20, 20);

        ball.SetPosition(GetWindowWidth() / 2 - 10, GetWindowHeight() / 2 - 10);
        ball.Update(0);

        ball_direction.x = (rand() % 2) * 2 - 1;
        ball_direction.y = (rand() % 2) * 2 - 1;

        collision_sound.SetupDevice();
        score_sound.SetupDevice();

        left_score_text.SetPosition({0, 0, 100, 50});
        right_score_text.SetPosition({500, 0, 100, 50});

        SetVolume(MIX_MAX_VOLUME / 4);
        main_music.Play(-1);
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
        }
        const Uint8 *keyboard_state = SDL_GetKeyboardState(nullptr);
        if (keyboard_state[SDL_SCANCODE_W])
        {
            const int old_position_y = left_paddle.GetTextureRectangle().GetPositionY();
            const int new_position_y = old_position_y - movement_speed;
            left_paddle.SetPosition(
                    left_paddle.GetTextureRectangle().GetPositionX(), new_position_y);
        }
        if (keyboard_state[SDL_SCANCODE_S])
        {
            const int old_position_y = left_paddle.GetTextureRectangle().GetPositionY();
            const int new_position_y = old_position_y + movement_speed;
            left_paddle.SetPosition(
                    left_paddle.GetTextureRectangle().GetPositionX(), new_position_y);
        }

        if (keyboard_state[SDL_SCANCODE_UP])
        {
            const int old_position_y = right_paddle.GetTextureRectangle().GetPositionY();
            const int new_position_y = old_position_y - movement_speed;
            right_paddle.SetPosition(
                    right_paddle.GetTextureRectangle().GetPositionX(), new_position_y);
        }
        if (keyboard_state[SDL_SCANCODE_DOWN])
        {
            const int old_position_y = right_paddle.GetTextureRectangle().GetPositionY();
            const int new_position_y = old_position_y + movement_speed;
            right_paddle.SetPosition(
                    right_paddle.GetTextureRectangle().GetPositionX(), new_position_y);
        }

    }

    void RenderCallback() override
    {
        // draw stuff
        left_paddle.Render();
        right_paddle.Render();
        ball.Render();

        left_score_text.Render(renderer);
        right_score_text.Render(renderer);
    }

    void UpdateCallback(const double deltaTime) override
    {
        int ball_x = ball.GetTextureRectangle().GetPositionX();
        int ball_y = ball.GetTextureRectangle().GetPositionY();

        if (ball_y < 0 || ball_y > GetWindowHeight() - 20)
        {
            ball_direction.y = -ball_direction.y;
        }

        if (ball_x < 0 || ball_x > GetWindowWidth() - 20)
        {
            if (ball_x < 0)
            {
                left_score++;
                score_sound.Play();
            }
            if (ball_x > GetWindowWidth() - 20)
            {
                right_score++;
                score_sound.Play();
            }
            ball_x = GetWindowWidth() / 2 - 10;
            ball_y = GetWindowHeight() / 2 - 10;
        }

        ball.SetPosition(
                ball_x + ball_speed * ball_direction.x, ball_y + ball_speed * ball_direction.y);
        if (ball.IsColliding(left_paddle.GetAllColliders()))
        {
            ball_direction.x = 1;
            collision_sound.Play();
        }
        else if (ball.IsColliding(right_paddle.GetAllColliders()))
        {
            ball_direction.x = -1;
            collision_sound.Play();
        }

        left_paddle.Update(deltaTime);
        right_paddle.Update(deltaTime);
        ball.Update(deltaTime);

        left_score_text.SetText(
                renderer, "Left: " + std::to_string(left_score), {0xFF, 0xFF, 0xFF, 0xFF});
        right_score_text.SetText(
                renderer, "Right: " + std::to_string(right_score), {0xFF, 0xFF, 0xFF, 0xFF});

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

    Music main_music{};
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
