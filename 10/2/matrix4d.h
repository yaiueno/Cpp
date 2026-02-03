#ifndef MATRIX4D_H
#define MATRIX4D_H

#include "vec3d.h"

class matrix4d {
public:
    double data[4][4]; // 4行4列の固定配列

    matrix4d(); // 0行列で初期化
    static matrix4d Identity(); // 単位行列を生成

    // 基本演算
    matrix4d operator+(const matrix4d& op) const; // 行列同士の和
    matrix4d operator-(const matrix4d& op) const; // 行列同士の差
    matrix4d operator*(const matrix4d& op) const; // 行列同士の積
    vec3d operator*(const vec3d& v) const;        // 行列とベクトルの積 (w=1 と仮定)

    // Gauss-Jordan 法
    // b: 4次元の定数項配列, x_out: 解の格納先
    bool SolveGaussJordan(const double b[4], double x_out[4]) const;

    matrix4d Inverse() const; // 逆行列を求める
};

#endif