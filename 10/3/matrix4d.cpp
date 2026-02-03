#include "matrix4d.h"
#include <cmath>
#include <algorithm> // std::swap 用

matrix4d::matrix4d() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = 0.0;
        }
    }
}

matrix4d matrix4d::Identity() {
    matrix4d res;
    for (int i = 0; i < 4; i++) res.data[i][i] = 1.0;
    return res;
}

// 行列同士の足し算
matrix4d matrix4d::operator+(const matrix4d& op) const {
    matrix4d res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.data[i][j] = data[i][j] + op.data[i][j];
        }
    }
    return res;
}

// 行列同士の引き算
matrix4d matrix4d::operator-(const matrix4d& op) const {
    matrix4d res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res.data[i][j] = data[i][j] - op.data[i][j];
        }
    }
    return res;
}

// 行列同士の積
matrix4d matrix4d::operator*(const matrix4d& op) const {
    matrix4d res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                res.data[i][j] += data[i][k] * op.data[k][j];
            }
        }
    }
    return res;
}

// 行列とベクトルの積
vec3d matrix4d::operator*(const vec3d& v) const {
    double vin[4] = { v.x, v.y, v.z, 1.0 };
    double vout[4] = { 0, 0, 0, 0 };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            vout[i] += data[i][j] * vin[j];
        }
    }
    // w成分(vout[3])は無視し、x, y, zを返す
    return vec3d(vout[0], vout[1], vout[2]);
}

// --- Gauss-Jordan 法 ---
bool matrix4d::SolveGaussJordan(const double b[4], double x_out[4]) const {
    double a[4][4];
    // コピーと初期化
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) a[i][j] = data[i][j];
        x_out[i] = b[i];
    }

    // kは講義資料の「第k段階」に対応 (0~3)
    for (int k = 0; k < 4; k++) {
        // --- pivot の入れ替え ---
        int pivot = k;
        for (int j = k + 1; j < 4; j++) {
            if (std::abs(a[j][k]) > std::abs(a[pivot][k])) pivot = j;
        }

        std::swap(x_out[k], x_out[pivot]);
        for (int j = 0; j < 4; j++) std::swap(a[k][j], a[pivot][j]);

        if (std::abs(a[k][k]) < 1e-10) return false;

        // 講義資料の更新式に基づく処理
        // 1. 第k行の正規化
        double a_kk_prev = a[k][k];
        for (int j = k + 1; j < 4; j++) {
            a[k][j] = a[k][j] / a_kk_prev;
        }
        x_out[k] = x_out[k] / a_kk_prev;
        a[k][k] = 1.0; // 正規化の結果、対角成分は1になる

        // 2. 第k行以外からx_kの係数を消去
        for (int i = 0; i < 4; i++) {
            if (i != k) {
                double a_ik_prev = a[i][k];
                x_out[i] -= a_ik_prev * x_out[k];
                
                a[i][k] = 0.0; // 消去の結果、k列の他成分は0になる
                for (int j = k + 1; j < 4; j++) {
                    a[i][j] -= a_ik_prev * a[k][j];
                }
            }
        }
    }
    return true;
}

// Gauss-Jordan 法による逆行列計算
matrix4d matrix4d::Inverse() const {
    matrix4d res = matrix4d::Identity();
    double a[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) a[i][j] = data[i][j];
    }

    // kは講義資料の「第k段階」に対応 (0~3)
    for (int k = 0; k < 4; k++) {
        // --- 1. pivot の入れ替え (部分ピボット選択) ---
        int pivot = k;
        for (int j = k + 1; j < 4; j++) {
            if (std::abs(a[j][k]) > std::abs(a[pivot][k])) pivot = j;
        }

        // a行列と単位行列(res)の両方の行を入れ替える
        for (int j = 0; j < 4; j++) {
            std::swap(a[k][j], a[pivot][j]);
            std::swap(res.data[k][j], res.data[pivot][j]);
        }

        // 軸要素が0に近い場合は計算不能
        if (std::abs(a[k][k]) < 1e-10) return matrix4d();

        // - 2. 講義資料の更新式に基づく処理 -
        // ① 第k行の正規化
        double a_kk_prev = a[k][k];
        for (int j = 0; j < 4; j++) {
            a[k][j] /= a_kk_prev;
            res.data[k][j] /= a_kk_prev;
        }
        a[k][k] = 1.0;

        // ② 第k行以外からx_kの係数を消去
        for (int i = 0; i < 4; i++) {
            if (i != k) {
                double a_ik_prev = a[i][k];
                for (int j = 0; j < 4; j++) {
                    a[i][j] -= a_ik_prev * a[k][j];
                    res.data[i][j] -= a_ik_prev * res.data[k][j];
                }
                a[i][k] = 0.0;
            }
        }
    }
    return res;
}