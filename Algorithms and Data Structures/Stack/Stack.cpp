#include <stdlib.h>
#include "Stack.h"
#include <iostream>

Stack::Stack() {
    st = new(int[1]);
    sp = 0;
    length = 1;
}

Stack::~Stack() {

}

void    Stack::add(int item) {
    if (sp == length)
        Stack::resizeStack(&st, &length, 1);
    st[sp++] = item;
}

int     Stack::pop() {
    int item;
    item = st[--sp];
    if (length > 0 and sp == length / 4)
    {
        length /= 2;
        realloc(st, sizeof(int) * length);
    }
    return item;
}

bool    Stack::isEmpty() {
    return sp;
}

int     Stack::getStackSize() {
    return length;
}

void    Stack::resizeStack(int **st, int *length, bool a) {
    if (a == 1)
        *length *= 2;
    else
        *length /= 2;
    *st = (int*) realloc(*st, sizeof(int) * (*length));
}
