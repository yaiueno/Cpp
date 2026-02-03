#include <iostream>
#include <iomanip>
#include "matrix4d.h"
#include "vec3d.h"

using namespace std;

// 行列の中身を表示する補助関数(4x4固定)
void PrintMatrix(const matrix4d& m, const string& name) {
    cout << "-" << name << " " << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << setw(10) << fixed << setprecision(4) << m.data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    // 1. 行列の加減算のテスト
    matrix4d A = matrix4d::Identity();
    matrix4d B = matrix4d::Identity();
    
    // Bを少し書き換える
    B.data[0][0] = 2.0;
    B.data[1][1] = 2.0;

    matrix4d Sum = A + B;
    matrix4d Diff = B - A;
    PrintMatrix(Sum, "Matrix A+B");
    PrintMatrix(Diff, "Matrix B-A");

    // 2. 行列の積のテスト
    // 回転や移動を模した行列の合成
    matrix4d M1 = matrix4d::Identity();
    M1.data[0][3] = 10.0; // X方向へ10 移動

    matrix4d M2 = matrix4d::Identity();
    M2.data[0][0] = 0.0; M2.data[0][1] = -1.0; // Z軸周り90度回転を模す
    M2.data[1][0] = 1.0; M2.data[1][1] = 0.0;

    matrix4d M_combined = M1 * M2;
    PrintMatrix(M_combined, "Combined Matrix (M1*M2)");

    // 3. Gauss-Jordan 法による連立一次方程式の解法テスト
    // 2x + y + z = 1
    // x + 2y + z = 2
    // x + y + 2z = 5
    // (w=1)
    matrix4d Eq;
    Eq.data[0][0] = 2; Eq.data[0][1] = 1; Eq.data[0][2] = 1;
    Eq.data[1][0] = 1; Eq.data[1][1] = 2; Eq.data[1][2] = 1;
    Eq.data[2][0] = 1; Eq.data[2][1] = 1; Eq.data[2][2] = 2;
    Eq.data[3][3] = 1; // 4行4列目

    double b[4] = { 1.0, 2.0, 5.0, 1.0 };
    double x_out[4];

    PrintMatrix(Eq, "Equation Matrix (4x4)");

    if (Eq.SolveGaussJordan(b, x_out)) {
        cout << "Solve Ax = b:" << endl;
        cout << "x = " << x_out[0] << ", y = " << x_out[1] << ", z = " << x_out[2] << endl;
        cout << "Expected: x=-1, y=0, z=3" << endl;
    } else {
        cout << "Failed to solve." << endl;
    }
    cout << endl;

    // 4. 逆行列のテスト
    matrix4d Eq_inv = Eq.Inverse();
    matrix4d IdentityCheck = Eq * Eq_inv;

    PrintMatrix(Eq_inv, "Equation Matrix Inverse");
    PrintMatrix(IdentityCheck, "Check: Eq * Eq_inv (Should be Identity)");

    return 0;
}