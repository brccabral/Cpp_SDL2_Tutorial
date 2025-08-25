#include <sdl2tutorial/SDL2Tutorial.hpp>

class MyGame : public SDLApp
{
public:

    MyGame(
            const Uint32 subsystemFlags, const char *title, const int x, const int y, const int w,
            const int h) :
        SDLApp(subsystemFlags, title, x, y, w, h),
        collision_sound(
                "assets/sounds/collide.wav", "Dell D3100 Docking Station Digital Stereo (IEC958)"),
        title_dyn_text("assets/fonts/8bitOperatorPlus8-Regular.ttf", 32),
        message_dyn_text("assets/fonts/8bitOperatorPlus8-Regular.ttf", 16),
        counter_dyn_text("assets/fonts/8bitOperatorPlus8-Regular.ttf", 16)
    {
        int index = 0;

        object1.SetTextureRect(renderer, "assets/images/kong.bmp", 0xFF, 0x00, 0xFF);
        object1.GetTextureRectangle().SetDimensions(100, 100);

        index = object1.AddCollider2D();
        object1.GetCollider2D(index).SetRelPosition(0, 0);
        object1.GetCollider2D(index).SetDimensions(100, 100);

        object1.SetPosition(50, 50);

        object2.SetTextureRect(renderer, "assets/images/kong.bmp");
        object2.GetTextureRectangle().SetDimensions(100, 100);

        index = object2.AddCollider2D();
        object2.GetCollider2D(index).SetRelPosition(25, 25);
        object2.GetCollider2D(index).SetDimensions(50, 25);
        index = object2.AddCollider2D();
        object2.GetCollider2D(index).SetRelPosition(25, 50);
        object2.GetCollider2D(index).SetDimensions(50, 25);

        title_dyn_text.SetText(renderer, "SDL2 Tutorial", {0xFF, 0xFF, 0xFF, 0xFF});
        title_dyn_text.SetPosition({0, 0, 100, 50});
        message_dyn_text.SetText(renderer, "Message", {0xFF, 0xFF, 0xFF, 0xFF});
        message_dyn_text.SetPosition({300, 300, 200, 50});
        counter_dyn_text.SetPosition({50, 300, 50, 50});
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
                if (object1.IsColliding(object2.GetAllColliders()))
                {
                    collision_sound.Play();
                }
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                object2.SetPosition(GetMouseX(), GetMouseY());
            }
        }
    }

    void RenderCallback() override
    {
        // draw stuff
        renderer.SetDrawColor(255, 0, 0, SDL_ALPHA_OPAQUE);
        renderer.DrawLine(10, 10, GetMouseX(), GetMouseY());

        object1.Render(renderer);
        object2.Render(renderer);

        title_dyn_text.Render(renderer);
        message_dyn_text.Render(renderer);
        counter_dyn_text.Render(renderer);
    }

    void UpdateCallback(const double deltaTime) override
    {
        const auto obj1Rect = object1.GetTextureRectangle().GetDestRect();
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
        object1.SetPosition(x, y);

        object1.Update(deltaTime);
        object2.Update(deltaTime);

        static int counter = 0;
        counter++;
        counter_dyn_text.SetText(renderer, std::to_string(counter), {0xFF, 0xFF, 0xFF, 0xFF});
    }

private:

    GameObject object1{};
    GameObject object2{};

    Sound collision_sound;

    DynamicText title_dyn_text;
    DynamicText message_dyn_text;
    DynamicText counter_dyn_text;
};

int main()
{
    {
        MyGame app(SDL_INIT_VIDEO | SDL_INIT_AUDIO, "SDL2 App Abstraction", 20, 20, 640, 480);
        app.SetFPS(30);
        app.RunLoop();
    }

    return 0;
}
