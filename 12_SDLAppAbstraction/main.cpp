#include <sdl2tutorial/SDL2Tutorial.hpp>

class MyGame : public SDLApp
{
public:

    MyGame(const char *title, const int x, const int y, const int w, const int h) :
        SDLApp(title, x, y, w, h), object1(GetRenderer(), "images/test.bmp"),
        object2(GetRenderer(), "images/test.bmp")
    {
        object1.SetPosition(50, 50);
        object1.SetDimensions(100, 100);
        object2.SetDimensions(100, 100);
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
                printf("IsColliding: %i\n", object1.IsColliding(object2));
            }
        }
    }

    void RenderCallback() override
    {
        // draw stuff
        GetRenderer().SetDrawColor(255, 0, 0, SDL_ALPHA_OPAQUE);
        GetRenderer().DrawLine(10, 10, GetMouseX(), GetMouseY());

        object2.SetPosition(GetMouseX(), GetMouseY());

        object1.Render(GetRenderer());
        object2.Render(GetRenderer());
    }

    void UpdateCallback(const double deltaTime) override{};

private:

    TextureRectangle object1;
    TextureRectangle object2;
};

int main()
{
    {
        MyGame app("SDL2 App Abstraction", 20, 20, 640, 480);
        app.RunLoop();
    }

    return 0;
}
