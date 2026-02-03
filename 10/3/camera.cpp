#include "camera.h"
#include <math.h>

// カメラの設定と変換行列の計算
void CCamera::SetCamera(vec3d pos, vec3d target, double angle, double turnangle, int screen_cx, int screen_cy)
{
    viewpoint = pos;
    direction = target - pos;
    direction.UnitVec(); // 方向ベクトルを正規化
    
    this->angle = angle;
    this->turnangle = turnangle;
    screensize_cx = screen_cx;
    screensize_cy = screen_cy;

    // 変換行列を計算
    CalculationV();
}

// 変換行列 V の計算
void CCamera::CalculationV()
{
    // 1. 各回転角の計算
    // xz_len: 方向ベクトルのXZ平面への射影長
    double xz_len = sqrt(direction.x * direction.x + direction.z * direction.z);

    // Y軸周りの回転 (alpha)
    // directionが正規化されている前提で計算
    double sina = direction.x / xz_len;
    double cosa = direction.z / xz_len;

    // X軸周りの回転 (beta)
    double sinb = direction.y;
    double cosb = xz_len;

    // Z軸周りの回転 (turnangle)
    double sinr = sin(turnangle);
    double cosr = cos(turnangle);

    // 2. 各変換行列の初期化
    matrix4d mRx = matrix4d::Identity(); // X-axis rotation
    matrix4d mRy = matrix4d::Identity(); // Y-axis rotation
    matrix4d mRz = matrix4d::Identity(); // Z-axis rotation
    matrix4d mT = matrix4d::Identity();  // Translation

    // X軸回転行列の設定 (Pitch)
    mRx.data[1][1] = cosb;
    mRx.data[1][2] = sinb;
    mRx.data[2][1] = -sinb;
    mRx.data[2][2] = cosb;

    // Y軸回転行列の設定 (Yaw)
    mRy.data[0][0] = cosa;
    mRy.data[0][2] = sina;
    mRy.data[2][0] = -sina; // 補完: 回転行列の性質より負号が必要
    mRy.data[2][2] = cosa;

    // Z軸回転行列の設定 (Roll)
    mRz.data[0][0] = cosr;
    mRz.data[0][1] = sinr;
    mRz.data[1][0] = -sinr;
    mRz.data[1][1] = cosr;

    // 平行移動行列の設定 (視点位置 + 画角による前進)
    // スクリーン平面の中心位置(origin)を計算
    vec3d origin = viewpoint + direction * angle;
    
    mT.data[0][3] = origin.x;
    mT.data[1][3] = origin.y;
    mT.data[2][3] = origin.z;

    // 3. 行列の合成 (T * Ry * Rx * Rz)
    // 計算順序は右から左に適用 (Roll -> Pitch -> Yaw -> Translate)
    this->V = mT * mRy * mRx * mRz;
}

vec3d CCamera::ScreenToAbsolute(int x, int y)
{
    // スクリーン上の点 (x, y, 0) を同次座標系のベクトルとして扱う
    // matrixクラスで定義した operator*(const vec3d&) を利用 (w=1 として処理される)
    return V * vec3d((double)x, (double)y, 0.0);
}