#ifndef VEC3D_H
#define VEC3D_H

class vec3d
{
public:
    double x; // X座標
    double y; // Y座標
    double z; // Z座標

    vec3d(double ax, double ay, double az);
    vec3d();
    ~vec3d();

    void UnitVec();              // 単位ベクトルに変換
    void InverseVec();           // 逆ベクトルに変換
    double Length();             // ベクトルの大きさ
    double InnerProduct(vec3d op) const; // 内積
    vec3d OuterProduct(vec3d op) const;  // 外積

public:
    // 等号,不等号
    bool operator ==(vec3d op) const;
    bool operator !=(vec3d op) const;

    // 加算
    vec3d operator +(vec3d op) const;
    void operator +=(vec3d op);

    // 減算
    vec3d operator -(vec3d op) const;
    void operator -=(vec3d op);

    // 逆ベクトル (単項演算子 -)
    vec3d operator -() const;

    // 実数倍
    vec3d operator *(double k) const;
    void operator *=(double k);
    vec3d operator /(double k) const;
    void operator /=(double k);

    // 代入
    void operator =(vec3d op);

    // index によるアクセス
    double& operator [](int i);
};

#endif