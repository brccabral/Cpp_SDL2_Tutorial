#include <sdl2tutorial/SDL2Tutorial.hpp>

class MyGame : public SDLApp
{
public:

    MyGame(const char *title, const int x, const int y, const int w, const int h) :
        SDLApp(SDL_INIT_VIDEO, title, x, y, w, h)
    {
        object1.SetTextureRect(renderer, "images/test.bmp");
        object2.SetTextureRect(renderer, "images/test.bmp");
        object1.GetTextureRectangle().SetPosition(50, 50);
        object1.GetTextureRectangle().SetDimensions(100, 100);
        object2.GetTextureRectangle().SetDimensions(100, 100);
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
                printf(
                        "IsColliding: %i\n",
                        object1.GetTextureRectangle().IsColliding(object2.GetTextureRectangle()));
            }
        }
    }

    void RenderCallback() override
    {
        // draw stuff
        renderer.SetDrawColor(255, 0, 0, SDL_ALPHA_OPAQUE);
        renderer.DrawLine(10, 10, GetMouseX(), GetMouseY());

        object2.GetTextureRectangle().SetPosition(GetMouseX(), GetMouseY());

        object1.Render(renderer);
        object2.Render(renderer);
    }

    void UpdateCallback(const double deltaTime) override
    {
    };

private:

    GameObject object1{};
    GameObject object2{};
};

int main()
{
    {
        MyGame app("SDL2 GameObject", 20, 20, 640, 480);
        app.SetFPS(30);
        app.RunLoop();
    }

    return 0;
}
