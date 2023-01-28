#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "chessGame.h"

int main()
{
    ChessGame demo;
    if (demo.Construct(640, 640, 1, 1)) // 80 - size of square
        demo.Start();
    return 0;
}
