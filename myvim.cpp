#include <stdio.h>
#include <conio.h>
using namespace  std;
#include "stack.h"
#include "linklist.h"
#define LETTER 1
#define OP 0
#define LINENUM 20
//#include <unistd.h>
//#include <sys/ioctl.h>

//struct winsize w;

Node *content=new Node;

Node *pointer_y=content;
Node *pointer_x=content;
int pointer_x_num=0;
int pointer_y_num=0;

int INSERTMODE=0;

void input(char t)
{
    if(t==13){
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
    //ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);//获取窗口大小
   // printf ("lines %d\n", w.ws_row);
    //printf ("columns %d\n", w.ws_col);
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
int check(char key)
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
            return OP;
        }
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

int main()
{
    content->next=NULL;
    content->nextline=NULL;
    content->length=0;
    char key;
    while(1){
        system("cls");
        print();
        key=wait_for_key();
        if(INSERTMODE)
            if(check(key)){
                input(key);
            }
            else{}
        else{
            check(key);
            if(key=='i')
                INSERTMODE=1;
        }
    }
    return 0;
}