#ifndef COUNTER_H
#define COUNTER_H

#include <iostream>
using namespace std;

class counter
{
    public:
        unsigned val;
        unsigned val_max;

        void reset(unsigned val_max);
        void increment();
        void decrement();
        void print();
};

#endif