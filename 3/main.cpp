#include <iostream>
#include "counter.h"
using namespace std;

int main(void){
    counter cnt;
    cnt.reset(5);
    cnt.print();

    for (int i=0; i<25; i++){
    cnt.increment();
    cnt.print();
    }

    for(int i=0; i<25; i++){
        cnt.decrement();
        cnt.print();
    }
}