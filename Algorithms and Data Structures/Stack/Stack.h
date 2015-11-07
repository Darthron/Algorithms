#ifndef STACK_H
#define STACK_H

class Stack {
public :

    Stack();
    ~Stack();
    void    add(int);
    int     pop();
    bool    isEmpty();
    int     getStackSize();
    void    resizeStack(int**, int*, bool);
private :
    int *st;
    int sp;
    int length;
};

#endif // STACK_H
