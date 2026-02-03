#include "bitmap.h"
#include <iostream>
#include <cstring>

CBitmap::CBitmap() { Bits = NULL; }

CBitmap::CBitmap(int width, int height) {
    Bits = NULL;
    Create(width, height);
}

CBitmap::CBitmap(const CBitmap& x) {
    Bits = NULL;
    BITMAPINFOHEADER info = x.GetInfo();
    BYTE* xbits = x.GetBits(0, info.biHeight - 1);
    if (xbits != NULL) {
        Create(info.biWidth, info.biHeight);
        std::memcpy(Bits, xbits, Info.biSizeImage);
    }
}

CBitmap& CBitmap::operator=(const CBitmap& x) {
    if (this != &x) {
        Release();
        BITMAPINFOHEADER info = x.GetInfo();
        BYTE* xbits = x.GetBits(0, info.biHeight - 1);
        if (xbits != NULL) {
            Create(info.biWidth, info.biHeight);
            std::memcpy(Bits, xbits, Info.biSizeImage);
        }
    }
    return *this;
}

CBitmap::~CBitmap() { Release(); }

void CBitmap::Create(int width, int height) {
    Release();
    Info.biSize = sizeof(BITMAPINFOHEADER);
    Info.biWidth = width;
    Info.biHeight = height;
    Info.biBitCount = 24;
    Info.biPlanes = 1;
    Info.biXPelsPerMeter = 0;
    Info.biYPelsPerMeter = 0;
    Info.biClrUsed = 0;
    Info.biClrImportant = 0;
    Info.biCompression = 0;
    Info.biSizeImage = width * height * 3;
    Bits = new BYTE[Info.biSizeImage];
}

void CBitmap::Release() {
    if (Bits != NULL) {
        delete[] Bits;
        Bits = NULL;
    }
}

bool CBitmap::SaveBmp(string path) const {
    FILE* fp = fopen(path.c_str(), "wb");
    if (fp == NULL) return false;

    WORD bfType = ('M' << 8) | 'B';
    DWORD bfSize = 14 + sizeof(BITMAPINFOHEADER) + Info.biSizeImage;
    WORD rsv1 = 0, rsv2 = 0;
    DWORD off = 14 + sizeof(BITMAPINFOHEADER);

    fwrite(&bfType, 2, 1, fp);
    fwrite(&bfSize, 4, 1, fp);
    fwrite(&rsv1, 2, 1, fp);
    fwrite(&rsv2, 2, 1, fp);
    fwrite(&off, 4, 1, fp);
    fwrite(&Info, sizeof(BITMAPINFOHEADER), 1, fp);
    fwrite(Bits, 1, Info.biSizeImage, fp);
    fclose(fp);
    return true;
}

BYTE* CBitmap::GetBits(int x, int y) const {
    int w = Info.biWidth, h = Info.biHeight;
    if (x < 0 || w <= x || y < 0 || h <= y) return NULL;
    return Bits + (h - y - 1) * 3 * w + x * 3;
}

void CBitmap::SetPixel(int x, int y, COLORREF color) {
    BYTE* p = GetBits(x, y);
    if (p) {
        p[0] = GetBValue(color);
        p[1] = GetGValue(color);
        p[2] = GetRValue(color);
    }
}

void CBitmap::DrawFunctionImage(COLORREF (*F)(int x, int y)) {
    int w = Width(), h = Height();
    for (int y = 0; y < h; y++) {
        BYTE* p = GetBits(0, y);
        for (int x = 0; x < w; x++) {
            COLORREF color = F(x, y);
            p[0] = GetBValue(color);
            p[1] = GetGValue(color);
            p[2] = GetRValue(color);
            p += 3;
        }
    }
}