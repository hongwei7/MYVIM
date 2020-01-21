typedef char elem;
#define stackmaxsize 1000

struct stack
{
    elem data[stackmaxsize];
    int top;
};
#include <iostream>

void Init_stack(stack *& s)
{
    s=new stack;
    s->top=-1;
}
void Destroy_stack(stack *& s)
{
    free(s);
}
bool Stack_empty(stack * s)
{
    return s->top==-1;
}
bool push(stack *& s,elem e)
{
    if(s->top>=stackmaxsize-1)return false;
    s->top++;
    s->data[s->top]=e;
    return true;
}
bool pop(stack *& s,elem & e)
{
    if(s->top==-1)return false;
    e=s->data[s->top--];
    return true;
}
bool Get_top(stack * s,elem &e)
{
    if(s->top==-1)return false;
    e=s->data[s->top];
    return true;
}
void Disp_stack(stack *s)
{
    for(int i=0;i<=s->top;i++)
    {
        cout<<s->data[i]<<" ";
    }cout<<endl;
}