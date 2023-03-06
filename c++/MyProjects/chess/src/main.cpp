
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "chessGame.h"

int main()
{
    ChessGame game;

    if (game.Construct(640, 640, 1, 1)) // 80 - size of square
    {
        game.Start();
    }

    return 0;
}