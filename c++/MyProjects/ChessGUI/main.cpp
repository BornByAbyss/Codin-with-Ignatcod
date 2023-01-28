#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "../chess/src/point.h"
#include "../chess/src/deck.h"

class PawnS
{
public:
    bool iswhite = true;
    int NomerPawn = 0;
    olc::vf2d PwnPos;

public:
    PawnS(float x, float y)
    {
        PwnPos.x = x;
        PwnPos.y = y;
    }

    PawnS(float x, float y, bool bl)
    {
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
    int tempIndex = -1;

private:
    olc::vf2d *pSelected = nullptr;
    olc::vf2d temp = {0.0f, 0.0f};
    std::vector<PawnS> pawns;

private:
    olc::Sprite *sprPawnBlack = nullptr;
    olc::Sprite *sprPawnWhite = nullptr;

    olc::Decal *decPawnBlack = nullptr;
    olc::Decal *decPawnWhite = nullptr;

private:
    chesslogix::Deck chessdeck;
    chesslogix::Point initialPoint;
    bool isFind = false;

    std::vector<chesslogix::Point> vectorOfPoints;

protected:
    virtual bool OnUserCreate() override
    {

        sprDeck = new olc::Sprite("./images/deck.png");

        sprPawnWhite = new olc::Sprite("./images/pawn.png");
        sprPawnBlack = new olc::Sprite("./images/pawnBlack.png");

        decPawnWhite = new olc::Decal(sprPawnWhite);
        decPawnBlack = new olc::Decal(sprPawnBlack);

        for (float l = 0.0f; l <= 560.0f; l += 80.0f)
        {
            pawns.push_back(PawnS(l, 480.0f));
            pawns.push_back(PawnS(l, 80.0f, false));
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
            if (pawns[k].iswhite)
            {
                if (pSelected == &pawns[k].PwnPos)
                {
                    tempIndex = k;
                    continue;
                }
                DrawDecal(pawns[k].PwnPos, decPawnWhite);
            }
            else
            {
                if (pSelected == &pawns[k].PwnPos)
                {
                    tempIndex = k;
                    continue;
                }
                DrawDecal(pawns[k].PwnPos, decPawnBlack);
            }
        }
        if (tempIndex >= 0)
        {
            if (pawns[tempIndex].iswhite)
                DrawDecal(pawns[tempIndex].PwnPos, decPawnWhite);
            else
                DrawDecal(pawns[tempIndex].PwnPos, decPawnBlack);

            tempIndex = -1;
        }

        olc::vf2d mouse = {float(GetMouseX()), float(GetMouseY())};

        if (GetMouse(0).bPressed)
        {
            pSelected = nullptr;

            for (int k = 0; k < pawns.size(); k++)
                if (((mouse.x > pawns[k].PwnPos.x) && (mouse.x < (pawns[k].PwnPos.x + 80.0f))) && ((mouse.y > pawns[k].PwnPos.y) && (mouse.y < (pawns[k].PwnPos.y + 80.0f))))
                {
                    pSelected = &pawns[k].PwnPos;
                    temp = pawns[k].PwnPos;
                    initialPoint = {((int)pawns[k].PwnPos.y / 80), ((int)pawns[k].PwnPos.x / 80), true};

                    chessdeck.logicOperation(initialPoint);
                    vectorOfPoints = chessdeck.takePoints();
                    chessdeck.clearPoints();
                    break;
                }
        }

        if (GetMouse(0).bReleased && pSelected != nullptr)
        {
            for (int k = 0; k < vectorOfPoints.size(); k++)
            {
                if (((mouse.x > (float)vectorOfPoints[k].col * 80.0f) && (mouse.x < ((float)vectorOfPoints[k].col * 80.0f + 80.0f))) && ((mouse.y > (float)vectorOfPoints[k].row * 80.0f) && (mouse.y < ((float)vectorOfPoints[k].row * 80.0f + 80.0f))))
                {
                    if (chessdeck.toStep(chesslogix::Point{vectorOfPoints[k].row, vectorOfPoints[k].col}))
                    {
                        for (int i = 0; i < pawns.size(); i++)
                        {
                            if (((float)vectorOfPoints[k].col * 80.0f == pawns[i].PwnPos.x) && ((float)vectorOfPoints[k].row * 80.0f == pawns[i].PwnPos.y))
                            {
                                pawns.erase(pawns.begin() + i);

                                break;
                            }
                        }
                    }
                    *pSelected = {(float)vectorOfPoints[k].col * 80.0f, (float)vectorOfPoints[k].row * 80.0f};
                    isFind = true;
                    break;
                }
            }
            if (!isFind)
                *pSelected = temp;

            isFind = false;
            pSelected = nullptr;
        }

        if (pSelected != nullptr)
        {
            for (unsigned i = 0; i < vectorOfPoints.size(); i++)
            {
                DrawRect(vectorOfPoints[i].col * 80 + 2, vectorOfPoints[i].row * 80 + 2, 75, 75, olc::VERY_DARK_CYAN);
                DrawRect(vectorOfPoints[i].col * 80 + 3, vectorOfPoints[i].row * 80 + 3, 73, 73, olc::CYAN);
            }
            *pSelected = (mouse - olc::vf2d{40.0f, 40.0f});
        }

        return true;
    }
};

int main()
{
    ChessG demo;
    if (demo.Construct(640, 640, 1, 1)) // 80 - size of square
        demo.Start();
    return 0;
}
