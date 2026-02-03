#ifndef BITMAP_H
#define BITMAP_H

#include <string>
#include <cstdio> // FILE型の定義に必要
using namespace std;

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;
typedef unsigned int COLORREF;

#define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define GetRValue(rgb) ((BYTE)(rgb))
#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb) ((BYTE)((rgb)>>16))

#pragma pack(push, 2)
struct BITMAPINFOHEADER {
    DWORD biSize;
    int biWidth;
    int biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
};
#pragma pack(pop)

class CBitmap {
public:
    CBitmap();
    CBitmap(int width, int height);
    CBitmap(const CBitmap& x);
    CBitmap& operator=(const CBitmap& x);
    ~CBitmap();

    void Create(int width, int height);
    void Release();
    int Width() const { return Info.biWidth; }
    int Height() const { return Info.biHeight; }
    BYTE* GetBits(int x, int y) const;
    BITMAPINFOHEADER GetInfo() const { return Info; }
    bool SaveBmp(string path) const;
    void SetPixel(int x, int y, COLORREF color);
    void DrawFunctionImage(COLORREF (*F)(int x, int y));

private:
    BITMAPINFOHEADER Info;
    BYTE* Bits;
};
#endif