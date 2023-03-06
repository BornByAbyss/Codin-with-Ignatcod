
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "menu.h"
#include "chessGame.h"

int main()
{
    Menu menu;

    while (true)
    {
        menu.Start();
        if (menu.Construct(640, 640, 1, 1)) // 80 - size of square
        
    }

    return 0;
}