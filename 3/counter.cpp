#include "counter.h"

void counter::reset(unsigned val_max){
    val = 0;
    this -> val_max = val_max;
}

void counter::increment(){
    val = (val < val_max) ? val+1 : 0;
}

void counter::decrement(){
    val = (0 < val) ? val-1 : val_max;
}

void counter::print(){
    cout << val <<endl;
}