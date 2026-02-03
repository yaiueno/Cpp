// obj_list.cpp
#include "obj_list.h"

CObjectList* CObjectList::insert(CObject* obj)
{
    CObjectList* new_node = new CObjectList();
    new_node->next = this->next;
    this->next = new_node;
    new_node->obj = obj;
    return new_node;
}

void CObjectList::draw_all(CObjectList* head, CBitmap& image)
{
    CObjectList* current = head;
    while (current != NULL) {
        if (current->obj != NULL) {
            current->obj->draw(image);
        }
        current = current->next;
    }
}

void CObjectList::remove_all(CObjectList* head)
{
    CObjectList* current = head;
    while (current != NULL) {
        CObjectList* current_buf = current->next;
        if (current->obj != NULL) {
            delete current->obj;
        }
        delete current;
        current = current_buf;
    }
}