// line.h
#ifndef LINE_H
#define LINE_H
#include "object.h"

class CLine : public CObject
{
protected:
    int sx, sy; // 始点座標
    int ex, ey; // 終点座標
public:
    CLine(int sx, int sy, int ex, int ey, COLORREF color);
    void draw(CBitmap& image);
};
#endif
