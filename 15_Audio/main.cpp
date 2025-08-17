#include <SDL2/SDL.h>

#include "GameObject.hpp"
#include "TextureRectangle.h"
#include "SDLApp.hpp"

class MyGame : public SDLApp
{
public:

    MyGame(const char *title, const int x, const int y, const int w, const int h) :
        SDLApp(title, x, y, w, h), object1(GetRenderer()),
        object2(GetRenderer())
    {
        int index = 0;

        object1.SetTextureRect("assets/images/kong.bmp", 0xFF, 0x00, 0xFF);
        object1.GetTextureRectangle().SetDimensions(100, 100);

        index = object1.AddCollider2D();
        object1.GetCollider2D(index).SetRelPosition(0, 0);
        object1.GetCollider2D(index).SetDimensions(100, 100);

        object1.SetPosition(50, 50);

        object2.SetTextureRect("assets/images/kong.bmp");
        object2.GetTextureRectangle().SetDimensions(100, 100);

        index = object2.AddCollider2D();
        object2.GetCollider2D(index).SetRelPosition(25, 25);
        object2.GetCollider2D(index).SetDimensions(50, 25);
        index = object2.AddCollider2D();
        object2.GetCollider2D(index).SetRelPosition(25, 50);
        object2.GetCollider2D(index).SetDimensions(50, 25);
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
                printf("IsColliding: %i\n", object1.IsColliding(object2.GetAllColliders()));
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
        SDL_SetRenderDrawColor(GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(GetRenderer(), 10, 10, GetMouseX(), GetMouseY());

        object1.Render();
        object2.Render();
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
    }

private:

    GameObject object1;
    GameObject object2;
};

int main()
{
    {
        MyGame app("SDL2 App Abstraction", 20, 20, 640, 480);
        app.SetFPS(30);
        app.RunLoop();
    }

    return 0;
}
