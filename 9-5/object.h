#ifndef OBJECT_H
#define OBJECT_H

#include "bitmap.h"

class CObject
{
protected:
    COLORREF color; // オブジェクトの色
public:
    CObject(COLORREF color) { this->color = color; }
    virtual ~CObject() {};
    // オブジェクトを描画する純粋仮想関数
    virtual void draw(CBitmap& image) = 0;
};

#endif