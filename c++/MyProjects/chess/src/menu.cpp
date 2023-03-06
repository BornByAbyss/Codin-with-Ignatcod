#include "olcPixelGameEngine.h"
#include "chessGame.h"
#include "menu.h"

Menu::Menu()
{
    sAppName = "Menu";
}

bool Menu::OnUserCreate()
{
    return true;
}
bool Menu::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLANK);

    FillRect(olc::vf2d{156.0f, 276.0f}, olc::vf2d{328.0f, 88.0f}, olc::BLACK);
    FillRect(olc::vf2d{160.0f, 280.0f}, olc::vf2d{320.0f, 80.0f}, olc::CYAN);

    DrawString(olc::vf2d{200.0f, 315.0f}, "PLAY MOTHERFAKA", olc::BLACK, 2);

    olc::vf2d mouse = {float(GetMouseX()), float(GetMouseY())};

    if (GetMouse(0).bPressed)
    {
        if ((mouse.x >= 160.0f && mouse.x <= 480.0f) && (mouse.y >= 280.0f && mouse.y <= 360.0f))
        {
            if (game.Construct(640, 640, 1, 1))
            {
                game.Start();
            }
        }
    }

    return true;
}