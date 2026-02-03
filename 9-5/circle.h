// circle.h
#ifndef CIRCLE_H
#define CIRCLE_H
#include "object.h"

class CCircle : public CObject
{
protected:
    int ox, oy; // 中心座標
    int r;      // 半径
public:
    CCircle(int ox, int oy, int r, COLORREF color);
    void draw(CBitmap& image);
};
#endif