#include "vec3d.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    cout << fixed << setprecision(2);

    vec3d vec1(-8.4, 3.4, -13.6);

    vec3d veclu = vec1;
    veclu.UnitVec();
    cout << veclu.x << " " << veclu.y << " " << veclu.z << endl;

    vec3d vecli = vec1;
    vecli.InverseVec();
    cout << vecli.x << " " << vecli.y << " " << vecli.z << endl;

    double lenlu = veclu.Length();
    cout << lenlu << endl;

    vec3d vec2;
    vec2.x = 100; vec2.y = 100; vec2.z = 300;

    if(vec1 == vec2) { cout << "vec1 == vec2" << endl; }
    else { cout << "vec1 != vec2" << endl; }

    vec2 = vec1;

    if(vec1 == vec2) { cout << "vec1 == vec2" << endl; }
    else { cout << "vec1 != vec2" << endl; }

    vec3d vec3 = vec1 + vec2;
    vec3 += vec1;
    cout << vec3.x << " " << vec3.y << " " << vec3.z << endl;

    vec3d vec4 = vec1 - vec2;
    vec4 -= vec1;
    cout << vec4.x << " " << vec4.y << " " << vec4.z << endl;

    vec3d vec5 = vec1 * 2.0;
    vec5 *= 2.0;
    cout << vec5.x << " " << vec5.y << " " << vec5.z << endl;

    vec3d vec6 = vec1 / 2.0;
    vec6 /= 2.0;
    cout << vec6.x << " " << vec6.y << " " << vec6.z << endl;

    vec3d vec7(0.4, -3.2, 9.3);

    double dot = vec1.InnerProduct(vec7);
    cout << dot << endl;

    vec3d cross = vec1.OuterProduct(vec7);
    cout << cross.x << " " << cross.y << " " << cross.z << endl;

    return 0;
}