#include "student.h"

void student::calc_ave()
{
    ave = (eng + math) / 2;
}

int  student::get_ave()
{
    return ave;
}

void student::set(string name, int eng, int math){
    student::name = name;
    student::eng = eng;
    student::math = math;
    calc_ave();
}

void student::print(){
    cout << name << " " << eng << " " << math << " " << ave << endl;
}