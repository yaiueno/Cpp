#ifndef CAMERA_H
#define CAMERA_H

#include "vec3d.h"
#include "matrix4d.h"

class CCamera
{
public:
    // スクリーン座標(x, y)を絶対座標(ワールド座標)に変換
    vec3d ScreenToAbsolute(int x, int y);
    
    // カメラパラメータの設定
    // pos: 視点位置, target: 注視点, angle: スクリーン距離(画角係数), turnangle: 画面の回転角
    void SetCamera(vec3d pos, vec3d target, double angle, double turnangle, int screen_cx, int screen_cy);
    
    vec3d GetViewPoint() { return viewpoint; }
    vec3d GetDirection() { return direction; }
    double GetAngle() { return angle; }
    double GetTurnAngle() { return turnangle; }
    void GetScreenSize(int& sx, int& sy) { sx = screensize_cx; sy = screensize_cy; }

private:
    vec3d viewpoint;   // 視点の位置ベクトル
    vec3d direction;   // カメラの方向ベクトル
    double angle;      // スクリーンと視点との距離(画角)
    double turnangle;  // スクリーンの回転角度
    
    int screensize_cx; // スクリーンの大きさ(半分) X
    int screensize_cy; // スクリーンの大きさ(半分) Y
    
    matrix4d V;        // スクリーン座標から絶対座標への変換行列 (4x4)
    
    void CalculationV(); // 行列を計算
};

#endif