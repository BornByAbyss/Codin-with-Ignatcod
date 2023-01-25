#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "../chess/src/point.h"
#include "../chess/src/deck.h"

class ChessG : public olc::PixelGameEngine
{
public:
    ChessG()
    {
        sAppName = "Chess";
    }

    olc::Sprite *sprDeck = nullptr;
    olc::Sprite *sprPawn = nullptr;
    olc::Decal *decPawn = nullptr;

    int nLayerBackground = 0;

private:
    olc::vf2d *pSelected = nullptr;
    olc::vf2d Pawn_W1 = {0.0f, 156.0f};
    olc::vf2d temp = {0.0f, 0.0f};

private:
    chesslogix::Deck chessdeck;
    char ch;
    bool isItFind = false;
    bool isItAwesomeMydear = false;
    std::string currentPos = "";
    std::vector<chesslogix::Point> vectorOfpoints;

protected:
    virtual bool OnUserCreate() override
    {

        sprDeck = new olc::Sprite("./images/deck.png");
        sprPawn = new olc::Sprite("./images/pawn.png");
        decPawn = new olc::Decal(sprPawn);

        nLayerBackground = CreateLayer();
        SetDrawTarget(nLayerBackground);
        Clear(olc::BLANK);

        SetPixelMode(olc::Pixel::ALPHA);
        DrawSprite({0, 0}, sprDeck, 1);
        SetPixelMode(olc::Pixel::NORMAL);

        EnableLayer(nLayerBackground, true);
        SetDrawTarget(nullptr);

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLANK);
        DrawDecal(Pawn_W1, decPawn, {0.05f, 0.05f});

        olc::vf2d mouse = {float(GetMouseX()), float(GetMouseY())};

        if (GetMouse(0).bPressed)
        {
            pSelected = nullptr;

            if ((Pawn_W1 - mouse).mag() < 25.0f)
            {
                isItAwesomeMydear = true;
                pSelected = &Pawn_W1;

                ch = 'a';
                temp = *pSelected;
                ch += (int)(Pawn_W1.x / 26.0f);
                currentPos = ch;
                currentPos += ('0' + (int)((208.0f - Pawn_W1.y) / 26));

                chessdeck.logicOperation(currentPos);
                vectorOfpoints = chessdeck.takeVpoints();
                chessdeck.clearPoints();
                currentPos = "";
            }
        }

        if (GetMouse(0).bReleased && isItAwesomeMydear)
        {
            for (unsigned i = 0; i < vectorOfpoints.size(); i++)
            {
                if (olc::vf2d{(float)(vectorOfpoints[i].col * 26 - Pawn_W1.x), (float)(vectorOfpoints[i].row * 26 - Pawn_W1.y)}.mag() < 25.0f)
                {
                    *pSelected = {float(vectorOfpoints[i].col * 26), (float)(vectorOfpoints[i].row * 26)};
                    chessdeck.makeAstep(vectorOfpoints[i]);
                    isItFind = true;
                    break;
                }
            }
            if (!isItFind)
            {
                *pSelected = temp;
            }
            isItAwesomeMydear = false;
            isItFind = false;
            pSelected = nullptr;
        }
        if (pSelected != nullptr)
        {
            for (unsigned i = 0; i < vectorOfpoints.size(); i++)
            {
                DrawCircle({float((vectorOfpoints[i].col * 26) + 13), float((vectorOfpoints[i].row * 26) + 13)}, 5, olc::RED);
            }
            *pSelected = (mouse - olc::vf2d{13.0f, 13.0f});
        }

        return true;
    }
};

int main()
{
    ChessG demo;
    if (demo.Construct(208, 208, 2, 2))
        demo.Start();
    return 0;
}