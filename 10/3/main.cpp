#include "vec3d.h"
#include "matrix4d.h"
#include "camera.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    // PDFの記述通り: hight_half=320, width_half=240
    // (一般的な解像度640x480を想定していると思われるが変数名と値の関係に注意)
    const int image_hight_half = 320;
    const int image_width_half = 240;
    
    const int image_hight = image_hight_half * 2;
    const int image_width = image_width_half * 2;

    CCamera camera;
    
    // SetCamera(pos, target, angle, turnangle, screen_cx, screen_cy)
    camera.SetCamera(
        vec3d(300, 160, -600),   // pos
        vec3d(100, -40, -150),   // target
        600,                     // angle (screen distance)
        0,                       // turnangle
        image_hight_half,        // screen_cx (320)
        image_width_half         // screen_cy (240)
    );

    int screensize_cx, screensize_cy;
    camera.GetScreenSize(screensize_cx, screensize_cy);

    cout << fixed << setprecision(2);

    vec3d viewpoint = camera.GetViewPoint();
    cout << "viewpoint: " << viewpoint.x << " " << viewpoint.y << " " << viewpoint.z << endl;

    int sx = -screensize_cx; // スクリーン座標でのピクセルの開始位置 (-320)
    int ex = screensize_cx;  // スクリーン座標でのピクセルの終了位置 (320)

    for(int y = 0; y < image_hight; y += 100)
    {
        // 画素のy座標をスクリーン座標に変換
        // y=0 のとき sy=240 (上端), y=large のとき sy=負 (下端)
        int sy = screensize_cy - y;

        for(int x = sx; x < ex; x += 100)
        {
            // スクリーン座標でのピクセル位置を絶対座標に変換
            vec3d pixelpos = camera.ScreenToAbsolute(x, sy);
            
            cout << "(" << x << "," << y << ") : " 
                 << pixelpos.x << " " << pixelpos.y << " " << pixelpos.z << endl;
        }
    }

    return 0;
}