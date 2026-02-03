#include <iostream>
#include <algorithm> // std::swap用
#include "line.h"

CLine::CLine(int sx, int sy, int ex, int ey, COLORREF color) : CObject(color) {
    this->sx = sx; this->sy = sy;
    this->ex = ex; this->ey = ey;
}

void CLine::draw(CBitmap& image) {
    int dx = (ex > sx) ? ex - sx : sx - ex;
    int dy = (ey > sy) ? ey - sy : sy - ey;
    int step, E;

    if (dx >= dy) {
        if (ex < sx) {
            std::swap(sx, ex); std::swap(sy, ey);
        }
        step = (ey > sy) ? 1 : -1;
        E = dx >> 1;
        do {
            image.SetPixel(sx, sy, color);
            if ((E -= dy) < 0) {
                sy += step;
                E += dx;
            }
        } while (++sx <= ex);
    } else {
        if (ey < sy) {
            std::swap(sx, ex); std::swap(sy, ey);
        }
        step = (ex > sx) ? 1 : -1;
        E = dy >> 1;
        do {
            image.SetPixel(sx, sy, color);
            if ((E -= dx) < 0) {
                sx += step;
                E += dy;
            }
        } while (++sy <= ey);
    }
}