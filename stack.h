#include <iostream>
using namespace std;
struct stackNode
{
    selem *data;
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
void Destroy_Node(stack *& root,stackNode *&s)//删除节点以及节点后面的所有节点
{
    if(s==NULL)return;
    stackNode* p=s,*q=s->next;
    while(q!=NULL){
        //printf("%d\n", root->top);
        root->top--;
        p=q->next;
        free(q);
        q=p;
    }
    free(q);
    root->top--;
    return ;
}
void Destroy_stack(stack *& s)
{
    Destroy_Node(s,s->firstNode);
    free(s);
}

bool Stack_empty(stack * s)
{
    return s->top==-1;
}
void push(stack *& s,selem *&e)
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
    if(s->now==-1){
        Destroy_Node(s,s->nowNode->next);
        free(s->nowNode);
        s->firstNode=new stackNode;
        s->top=0;
        s->now=0;
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

void Disp_stack(stack *s)
{
    stackNode *p=s->firstNode;
    if(p==NULL)return;
    for(int i=0;i<=s->top;i++)
    {
        cout<<p->data->name<<" "<<p->data->x<<" "<<p->data->y<<" "<<p->data->data<<endl;
        p=p->next;
    }cout<<endl;
    printf("top: %d now:%d \n",s->top ,s->now);
}
