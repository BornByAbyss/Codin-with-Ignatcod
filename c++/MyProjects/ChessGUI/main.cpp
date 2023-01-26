#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "../chess/src/point.h"
#include "../chess/src/deck.h"
#include <unordered_map>

class PawnS
{
public:
    bool iswhite = true;
    int NomerPawn = 0;
    olc::Sprite *sprPawn = nullptr;
    olc::Decal *decPawn = nullptr;
    olc::vf2d PwnPos;

public:
    PawnS(float x, float y)
    {
        sprPawn = new olc::Sprite("./images/pawn.png");
        decPawn = new olc::Decal(sprPawn);
        PwnPos.x = x;
        PwnPos.y = y;
    }

    PawnS(float x, float y, bool bl)
    {
        sprPawn = new olc::Sprite("./images/pawn.png");
        decPawn = new olc::Decal(sprPawn);
        PwnPos.x = x;
        PwnPos.y = y;
        iswhite = bl;
    }
};

class ChessG : public olc::PixelGameEngine
{
public:
    ChessG()
    {
        sAppName = "Chess";
    }

    olc::Sprite *sprDeck = nullptr;

    int nLayerBackground = 0;

private:
    olc::vf2d *pSelected = nullptr;
    olc::vf2d temp = {0.0f, 0.0f};

    std::vector<PawnS> pawns;

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

        for (float l = 0.0f; l <= 182.0f; l += 26.0f)
        {
            pawns.push_back(PawnS(l, 156.0f));
            pawns.push_back(PawnS(l, 26.0f, false));
        }

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

        for (int k = 0; k < pawns.size(); k++)
        {
            if (pawns[k].iswhite && pawns[k].decPawn != nullptr)
                DrawDecal(pawns[k].PwnPos, pawns[k].decPawn, {0.05f, 0.05f});
            else if (pawns[k].decPawn && pawns[k].decPawn != nullptr)
                DrawDecal(pawns[k].PwnPos, pawns[k].decPawn, {0.05f, 0.05f}, olc::BLACK);
        }

        olc::vf2d mouse = {float(GetMouseX()), float(GetMouseY())};

        if (GetMouse(0).bPressed)
        {
            pSelected = nullptr;

            for (int k = 0; k < pawns.size(); k++)
                if (((pawns[k].PwnPos - mouse).mag() < 20.0f))
                {
                    isItAwesomeMydear = true;
                    pSelected = &pawns[k].PwnPos;

                    ch = 'a';
                    temp = *pSelected;
                    ch += (int)(pawns[k].PwnPos.x / 26.0f);
                    currentPos = ch;
                    currentPos += ('0' + (int)((208.0f - pawns[k].PwnPos.y) / 26));

                    chessdeck.logicOperation(currentPos);
                    vectorOfpoints = chessdeck.takeVpoints();
                    chessdeck.clearPoints();
                    currentPos = "";
                    break;
                }
        }

        if (GetMouse(0).bReleased && isItAwesomeMydear)
        {
            for (unsigned i = 0; i < vectorOfpoints.size(); i++)
            {
                if (olc::vf2d{((float)vectorOfpoints[i].col * 26.0f - (float)(*pSelected).x), ((float)vectorOfpoints[i].row * 26.0f - (float)(*pSelected).y)}.mag() < 20.0f)
                {
                    for (int k = 0; k < pawns.size(); k++)
                    {
                        if (pawns[k].PwnPos.x == ((float)vectorOfpoints[i].col * 26.0f) && pawns[k].PwnPos.y == ((float)vectorOfpoints[i].row * 26.0f))
                        {
                            delete pawns[k].decPawn;
                            delete pawns[k].sprPawn;
                            pawns[k].sprPawn = nullptr;
                            pawns[k].decPawn = nullptr;
                            pawns.erase(pawns.begin() + k);
                            break;
                        }
                    }
                    *pSelected = {float(vectorOfpoints[i].col * 26.0f), (float)(vectorOfpoints[i].row * 26.0f)};
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
                DrawCircle({((vectorOfpoints[i].col * 26) + 13), ((vectorOfpoints[i].row * 26) + 13)}, 5, olc::RED);
            }
            *pSelected = (mouse - olc::vf2d{13.0f, 13.0f});
        }

        return true;
    }
};

int main()
{
    ChessG demo;
    if (demo.Construct(208, 208, 1, 1))
        demo.Start();
    return 0;
}