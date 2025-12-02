#include <iostream>
#include "list.h"
using namespace std;

int main(void){

    list* head = new list;
    head -> set_item("山田一郎", 60, 70);
    head -> next =NULLl

    list* node2 = head -> insert();
    node2->set_item("加藤次郎", 50, 40);

    list* node3= node2 -> insert();
    node3->set_intem("高木三郎", 80, 60);

    list::print_all(head);

    list::remove_all(head);
}