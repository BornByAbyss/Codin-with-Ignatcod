#ifndef MENU_H
#define MENU_H
#include "olcPixelGameEngine.h"
#include "chessGame.h"

    ChessGame game;
class Menu : public olc::PixelGameEngine
{
public:
    Menu(/* args */);
    virtual bool OnUserCreate() override;
    virtual bool OnUserUpdate(float fElapsedTime) override;
};

#endif
