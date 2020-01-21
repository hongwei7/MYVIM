typedef char selem;
#include "stack.h"
void Disp_stack(stack *s)
{
    stackNode *p=s->firstNode;
    if(p==NULL)return;
    for(int i=0;i<=s->top;i++)
    {
        cout<<p->data<<" ";
        p=p->next;
    }cout<<endl;
}
int main()
{
    stack *s;
    Init_stack(s);
    push(s,'A');
    Disp_stack(s);
    push(s,'B');
    Disp_stack(s);
    roolback(s);
    Disp_stack(s);
    push(s,'C');
    Disp_stack(s);
    roolback(s);
    Disp_stack(s);
    push(s,'D');
    Disp_stack(s);
    push(s,'E');
    Disp_stack(s);
    roolback(s);
    Disp_stack(s);
    roolback(s);
    Disp_stack(s);
    roolback(s);
    Disp_stack(s);
    redo(s);
    Disp_stack(s);
    printf("nowNode: %c top: %d now: %d\n", s->nowNode->data,s->top,s->now);
    redo(s);
    Disp_stack(s);
    printf("nowNode: %c top: %d now: %d\n", s->nowNode->data,s->top,s->now);
    redo(s);
    Disp_stack(s);
    printf("nowNode: %c top: %d now: %d\n", s->nowNode->data,s->top,s->now);
}