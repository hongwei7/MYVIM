#include <stdio.h>
#include <conio.h>
#include "OP_struct.h"
typedef OPDATA selem;
#include "stack.h"
#include "linklist.h"
#define LETTER 1
#define OP 0
#define LINENUM 20

Node *content=new Node;
Node *pointer_y=content;
Node *pointer_x=content;
int pointer_x_num=0;
int pointer_y_num=0;
stack *s;//记录操作的链栈

int INSERTMODE=0;

void add_op(char name,int x,int y,char e)
{
    OPDATA *temp=new OPDATA(name,x,y,e);
    push(s,temp);
}
void input(char t,int recored=1)
{
    if(t==13){
        if(recored)
            add_op('n',pointer_x_num,pointer_y_num,13);
    	printf("get!\n");
        Node *p=new Node;
        Node *q=pointer_x->next;
        Node *r=pointer_y->nextline;
        int newlength=pointer_y->length - pointer_x_num;
        pointer_y->length=pointer_x_num;
        pointer_x->next=NULL;
        pointer_x=p;
        pointer_y->nextline=p;
        pointer_y=p;
        pointer_y_num++;
        pointer_x_num=-1;
        pointer_x->next=q;
        pointer_y->length=newlength-1;
        pointer_y->nextline=r;
    }
    if(t!=13){
        if(recored)
            add_op('i',pointer_x_num,pointer_y_num,t);
        Node* p=pointer_x->next;
        pointer_x->next=new Node;
        pointer_x=pointer_x->next;
        pointer_x->data=t;
        pointer_x->next=p;
    }
    pointer_y->length++;
    pointer_x_num++;
}
char wait_for_key()
{
    int ch;
    ch=getch();
    printf("\n%d\n",ch);
    return ch;
}

void print()
{
    Node *q=content;
    while(q!=NULL){
        if(q==pointer_x)
                printf("_");
        Node *p=q->next;
        while(p!=NULL){
            printf("%c",p->data);
            if(p==pointer_x)
                printf("_");
            p=p->next;
        }
        q=q->nextline;
        printf("\n");
    }
    printf("\n");
    if(INSERTMODE)
        printf("%10s   ","INSERTMODE");
    else
        printf("%10s   ","");
    printf("Length:%8d Pointer_y:%8d Pointer_x:%8d\n",pointer_y-> length,pointer_y_num,pointer_x_num);
}

int check_op=0;
int check(char key,int recored=1)
{
    //输入退回
    if(key==8){  
        if(pointer_x_num==0){
            if(pointer_y_num==0)
                return OP;
            Node * t=content;
            Node * l;
            while(t->nextline!=pointer_y)
                t=t->nextline;
            t->nextline=pointer_y->nextline;
            t->length+=pointer_y->length;
            pointer_x_num=0;
            l=t;
            while(t->next!=NULL){
                t=t->next;
                pointer_x_num++;
            }
            t->next=pointer_y;
            pointer_x=t;
            pointer_y=l;
            pointer_y_num--;
            t=pointer_x->next;
            pointer_x->next=t->next;
            free(t);
            if(recored)
                add_op('d',pointer_x_num,pointer_y_num,8);
            return OP;
        }
        if(recored)
            add_op('b',pointer_x_num,pointer_y_num,pointer_x->data);
        Node *p=pointer_y;
        while(p->next!=pointer_x)
            p=p->next;
        p->next=pointer_x->next;
        free(pointer_x);
        pointer_x=p;
        pointer_y->length--;
        pointer_x_num--;
        return OP;
    }
    if(key== -32){
        check_op=1;
        //printf("get!\n");
    }
    if(check_op>0){
    	key=getch();
        switch(key){
            case 'H':{ //上
                if(pointer_y_num!=0){
                    pointer_y_num--;
                    Node *s=content;
                    while(s->nextline!=pointer_y)
                        s=s->nextline;
                    pointer_y=s;
                    Node *p=pointer_y;
                    pointer_x=p;
                    int i=0;
                    for(;i<pointer_x_num;i++){
                        if(p->next!=NULL){
                            p=p->next;
                        }
                        else{
                            break;
                        }
                    }
                    pointer_x_num=i;
                    pointer_x=p;
                }
            }break;
            case 'P':{
                if(pointer_y->nextline!=NULL)
                {
                    pointer_y_num++;
                    pointer_y=pointer_y->nextline;
                    Node *p=pointer_y;
                    pointer_x=p;
                    int i=0;
                    for(;i<pointer_x_num;i++){
                        if(p->next!=NULL){
                            p=p->next;
                        }
                        else{
                            break;
                        }
                    }
                    pointer_x_num=i;
                    pointer_x=p;
                }
            }break;
            case 'M':{
                if(pointer_x->next!=NULL){
                    pointer_x=pointer_x->next;
                    pointer_x_num++;
                }
            }break;
            case 'K':{
                if(pointer_x_num==0)
                    break;
                Node*p=pointer_y;
                while(p->next!=pointer_x)
                    p=p->next;
                pointer_x=p;
                pointer_x_num--;
                }break;
            default:break;
        }
        check_op=0;
        return OP;
    }
    else{
        if(key==27){
        printf("ESC\n");
        INSERTMODE=0;
        check_op=0;
        return OP;
        }
    }
    check_op=0;
    return LETTER;
}

void roolback_input(int x,int y)
{

    pointer_x_num=x;
    pointer_y_num=y;
    //printf("%d %d\n",pointer_x_num,pointer_y_num);
    Node *p=content,*q;
    for(int i=0;i<y;i++)
        p=p->nextline;
    pointer_y=p;
    for(int i=0;i<x;i++)
        p=p->next;
    pointer_x=p;
    q=p->next;
    p->next=q->next;
    free(q);
    pointer_y->length--;
}

void roolback_back(int x,int y,char e)
{
    pointer_x_num=x-1;
    pointer_y_num=y;
    //printf("%d %d  \n",pointer_x_num,pointer_y_num);
    //system("pause");
    Node *p=content,*q;
    for(int i=0;i<y;i++)
        p=p->nextline;
    pointer_y=p;
    for(int i=0;i<x-1;i++){
        p=p->next;
        //printf("%c\n",p->data );
    }
    //system("pause");
    pointer_x=p;
    q=p->next;
    p->next=new Node;
    p=p->next;
    p->data=e;
    p->next=q;
    pointer_y->length++;
}
void roolback_enter(int y)
{
    pointer_x_num=0;
    pointer_y_num=y+1;
    Node *p=content,*q;
    for(int i=0;i<y+1;i++)
        p=p->nextline;
    pointer_y=p;
    pointer_x=p;
    check(8,0);
}
void roolback_delenter(int x,int y)
{
    pointer_x_num=x;
    pointer_y_num=y;
    Node *p=content,*q;
    for(int i=0;i<y;i++)
        p=p->nextline;
    pointer_y=p;
    for(int i=0;i<x;i++)
        p=p->next;
    pointer_x=p;
    input(13,0);
    return;
}
void operate_OP(int mode,OPDATA* opdata)//执行撤回或重做
{
    if(mode==1)//撤回模式
    {
        //printf("%c\n",opdata->name );
        switch(opdata->name){
            case 'i':roolback_input(opdata->x,opdata->y); break;
            case 'b':roolback_back(opdata->x,opdata->y,opdata->data);break;
            case 'n':roolback_enter(opdata->y);break;
            case 'd':roolback_delenter(opdata->x,opdata->y);break;
            default:printf("error!\n");break;
        }
    }
    else
    {
        switch(opdata->name){
            case 'i':roolback_back(opdata->x,opdata->y,opdata->data); break;
            case 'b':roolback_input(opdata->x,opdata->y);break;
            case 'n':roolback_delenter(opdata->x,opdata->y);break;
            case 'd':roolback_enter(opdata->y);break;
            default:printf("error!\n");break;
        }
    }
}
void roolback(stack *&s)
{
    if(s->now==-1)return;
    if(s->now==0){
        s->nowNode=s->firstNode;
        operate_OP(1,s->nowNode->data);
        s->now=-1;
        return;
    }
    operate_OP(1,s->nowNode->data);
    s->nowNode=s->firstNode;
    for(int i=0;i<s->now-1;i++){
        s->nowNode=s->nowNode->next;
    }
    s->now--;
    return;
}
void redo(stack *&s)
{
    if(s->top==-1)return;
    if(s->nowNode==NULL||s->nowNode->next==NULL)return;
    if(s->now==-1){
        operate_OP(0,s->firstNode->data );
        s->nowNode=s->firstNode;
        s->now++;
        return;
    }
    operate_OP(1,s->nowNode->next->data );
    s->nowNode=s->nowNode->next;
    s->now++;
    return;
}
int main()
{
	Init_stack(s);
    content->next=NULL;
    content->nextline=NULL;
    content->length=0;
    char key;
    while(1){
        system("cls");
        print();
        //Disp_stack(s);
        key=wait_for_key();
        if(INSERTMODE)
            if(check(key)){
                input(key);
            }
            else{}
        else{
            check(key);
            switch(key){
	            case 'i':
	                INSERTMODE=1;break;
	            case 'u':
	            	roolback(s);break;
	            case 'r':
	            	redo(s);break;
	            default:break;
	        }
        }
    }
    return 0;
}