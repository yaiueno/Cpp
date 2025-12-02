#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>
using namespace std;

class student{
public:
    string name ;
    int eng;
    int math;
    int ave;

    void calc_ave();
    int get_ave();
    void set(string name, int eng, int math);
    void print();
};

#endif