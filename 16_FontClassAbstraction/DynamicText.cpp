#include "DynamicText.hpp"
#include <SDL_ttf.h>


DynamicText::DynamicText()
{
    if (!isTTF_initialized && TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
    }
    else
    {
        isTTF_initialized = SDL_TRUE;
    }
}

DynamicText::~DynamicText()
{
    if (isTTF_initialized)
    {
        TTF_Quit();
        isTTF_initialized = SDL_FALSE;
    }
}

SDL_bool DynamicText::isTTF_initialized = SDL_FALSE;
