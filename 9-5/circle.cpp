#include "circle.h"

CCircle::CCircle(int ox, int oy, int r, COLORREF color) : CObject(color) {
    this->ox = ox; this->oy = oy; this->r = r;
}

void CCircle::draw(CBitmap& image) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (x <= y) {
        image.SetPixel(x + ox, y + oy, color);
        image.SetPixel(y + ox, x + oy, color);
        image.SetPixel(-x + ox, y + oy, color);
        image.SetPixel(-y + ox, x + oy, color);
        image.SetPixel(-x + ox, -y + oy, color);
        image.SetPixel(-y + ox, -x + oy, color);
        image.SetPixel(x + ox, -y + oy, color);
        image.SetPixel(y + ox, -x + oy, color);

        if (d < 0) d = d + 4 * x + 6;
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}