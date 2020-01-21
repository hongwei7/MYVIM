#include <iostream>
using namespace std;
struct stackNode
{
    selem data;
    stackNode* next;
};
struct stack//链栈
{
    stackNode *firstNode;
    int top,now;
    stackNode *nowNode;
};
void Init_stack(stack *& s)
{
    s=new stack;
    s->firstNode=new stackNode;
    s->top=-1;
    s->now=s->top;
}
void Destroy_stack(stack *& s)
{
    free(s);
}
void Destroy_Node(stack *& root,stackNode *&s)
{
    if(s==NULL)return;
    stackNode* p=s,*q=s->next;
    while(q!=NULL){
        root->top--;
        free(q);
        p=q;
        q=q->next;
    }
    free(q);
    root->top--;
    return ;
}
bool Stack_empty(stack * s)
{
    return s->top==-1;
}
void push(stack *& s,selem e)
{
    if(s->top==-1){
        s->firstNode=new stackNode;
        s->top++;
        s->now++;
        s->nowNode=s->firstNode;
        s->nowNode->data=e;
        s->nowNode->next=NULL;
        return;
    }
    Destroy_Node(s,s->nowNode->next);
    s->nowNode->next=new stackNode;
    stackNode *p=s->nowNode;
    s->nowNode=s->nowNode->next;
    s->now++;
    s->top++;
    s->nowNode->data=e;
    s->nowNode->next=NULL;
    return ;
}
/*
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
*/
void roolback(stack *&s)
{
    if(s->now==-1)return;
    printf("roolback:%c\n", s->nowNode->data);
    s->nowNode=s->firstNode;
    for(int i=0;i<s->now-1;i++){
        s->nowNode=s->nowNode->next;
    }
    s->now--;
    return;
}
void redo(stack *&s)
{
    if(s->nowNode==NULL||s->nowNode->next==NULL)return;
    if(s->now==-1){
        printf("redo:%c\n",s->firstNode->data );
        s->nowNode=s->firstNode;
        s->now++;
        return;
    }
    printf("redo:%c\n",s->nowNode->next->data );
    s->nowNode=s->nowNode->next;
    s->now++;
    return;
}