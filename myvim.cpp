#include <stdio.h>
#include <conio.h>
#include<ctype.h>
#include <windows.h>
#include<fstream>
#include "color.cpp" //控制台光标、颜色控制代码
#include <string>
#include<iostream>
using namespace std;
#define max_size 50
#define LETTER 1
#define OP 0
struct Node //存储文本的节点结构
{
    char data;
    Node * next;
    Node * nextline;
    int length;
};
struct OPDATA //存储操作行为的存储结构（用于撤回和重做）
{
    char name;//操作名 i,b,n,d 输入，删除，回车,删除回车
    int x;
    int y;//操作坐标
    char data;//操作数据
    OPDATA(char n,int _x,int _y,char e){
        name=n;
        x=_x;
        y=_y;
        data=e;
    }
};
//typedef OPDATA OPDATA;

struct stackNode //链栈节点
{
    OPDATA *data;
    stackNode* next;
};
struct stack//链栈 用于撤回重做
{
    stackNode *firstNode;
    int top,now;
    stackNode *nowNode;
};
void Init_stack(stack *& s) //链栈初始化
{
    s=new stack;
    s->firstNode=new stackNode;
    s->top=-1;
    s->now=s->top;
}
void Destroy_Node(stack *& root,stackNode *&s)//删除链栈指定节点以及节点后面的所有节点
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
void Destroy_stack(stack *& s) //删除链栈
{
    Destroy_Node(s,s->firstNode);
    free(s);
}

bool Stack_empty(stack * s) //判断链栈是否位空
{ 
    return s->top==-1;
}
void push(stack *& s,OPDATA *&e)  //往链栈内存储一个操作
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

void Disp_stack(stack *s)  //显示链栈内容（调试用）
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


Node *content=new Node;
Node *pointer_y=content;
Node *pointer_x=content;
int pointer_x_num=0;
int pointer_y_num=0;
int print_area_x,print_area_y;
stack *s;//记录操作的链栈
string title="新文件-未保存";
int INSERTMODE=0;



void add_op(char name,int x,int y,char e) //记录一个操作并存储起来
{
    OPDATA *temp=new OPDATA(name,x,y,e);
    push(s,temp);
}

int paste();
void input(char t,int recored=1)
{
    if(t==13){
        if(recored)
            add_op('n',pointer_x_num,pointer_y_num,13);
    	//printf("get!\n");
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
char wait_for_key() //读取输入
{
    int ch;
    ch=getch();
    //printf("\n%d\n",ch);
    return ch;
}
void cal_show_area() //计算自适应显示范围
{
    int r=0;
    Node* p=content;
    while(p->nextline!=NULL){
        p=p->nextline;
        r++;
    }
    if((rows/2<pointer_y_num) && (r- pointer_y_num )<rows/2){
        print_area_y=r-rows;
        return;
    }
    if(rows/2<pointer_y_num){
        print_area_y=pointer_y_num-rows/2;
    }
    else
        print_area_y=0;
    if(columns/2<pointer_x_num){
        print_area_x=pointer_x_num-columns/2;
    }
    else
        print_area_x=0;
}
void print() //显示的刷新函数
{
    int localx=0,localy=0;
    get_windows_size();
    cal_show_area();
    set_console_color(0);
    Node *q=content;
    while(q!=NULL){
        /*
        if(q==pointer_x){
                ;
                //printf("_");
            }*/
        Node *p=q->next;
        if(localy>=print_area_y&&localy<=print_area_y+rows){
            while(p!=NULL){
                if(localx>=print_area_x&&localx<print_area_x+columns)
                    printf("%c",p->data);
                localx++;
                /*
                if(p==pointer_x){
                    ;
                    //printf("_");
                }*/
                p=p->next;
            }
            if(localy+1<=print_area_y+rows)
                printf("\n");
        }
        localx=0;
        q=q->nextline;
        localy++;
    }
    for(;localy<rows;localy++)
        printf("~\n");
    printf("\n");
    if(INSERTMODE){
        set_console_color(1);
        printf("%10s   ","输入模式");
    }
    else{
        set_console_color(2);
        printf("%10s   ","功能模式");
    }
    set_console_color(0);
    printf("查看帮助(H)  ");
    printf("本行字数:%2d   行:%2d   列:%2d   ",pointer_y-> length,pointer_y_num,pointer_x_num);
    set_console_color(3);
    cout<<title;
    set_console_color(0);
    set_pointer(pointer_x_num- print_area_x ,pointer_y_num -print_area_y );
 }

int check_op=0;
int check(char key,int recored=1) //检查输入操作函数
{
    if(key==3)
        return OP;
    if(key==22&&INSERTMODE)
    {
        paste();
        return OP;
    }
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
        //printf("ESC\n");
        INSERTMODE=0;
        check_op=0;
        return OP;
        }
    }
    check_op=0;
    return LETTER;
}

void roolback_input(int x,int y) //撤回输入字符操作
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

void roolback_back(int x,int y,char e) //撤回删除字符操作
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
void roolback_enter(int y) //撤回换行操作
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
void roolback_delenter(int x,int y) //撤回删除换行操作
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
    //printf("operate_OP\n");
    if(mode==1)//撤回模式
    {
        //printf("%c\n",opdata->name );
        switch(opdata->name){
            case 'i':roolback_input(opdata->x,opdata->y); break;
            case 'b':roolback_back(opdata->x,opdata->y,opdata->data);pointer_x=pointer_x->next;pointer_x_num++;break;
            case 'n':roolback_enter(opdata->y);break;
            case 'd':roolback_delenter(opdata->x,opdata->y);break;
            default:printf("error!\n");break;
        }
    }
    else//重做模式
    {
        //printf("get\n");
        switch(opdata->name){
            case 'i':roolback_back(opdata->x+1,opdata->y,opdata->data);pointer_x=pointer_x->next;pointer_x_num++; break;
            case 'b':roolback_input(opdata->x-1,opdata->y);break;
            case 'n':roolback_delenter(opdata->x,opdata->y);break;
            case 'd':roolback_enter(opdata->y);break;
            default:printf("error!\n");break;
        }
    }
}
void roolback(stack *&s) //从链栈中读取数据撤回
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
void redo(stack *&s) //从链栈中读取数据重做
{
    if(s->top==-1)return;
    if(s->nowNode==NULL||s->nowNode->next==NULL)return;
    if(s->now==-1){
        operate_OP(0,s->firstNode->data );
        s->nowNode=s->firstNode;
        s->now++;
        return;
    }
    operate_OP(0,s->nowNode->next->data );
    s->nowNode=s->nowNode->next;
    s->now++;
    return;
}
int paste() //Ctrl+V快捷键粘贴支持
{
    char *pbuf=NULL;
    HANDLE hclip;
    //打开剪切板，获取里面的数据
    if(OpenClipboard(NULL)==0)
    {
        printf("打开剪切板失败！\n");
        return -1;
    }
    //剪切板当中的数据是不是文本类型的
    if(!IsClipboardFormatAvailable(CF_TEXT))
    {
        printf("剪切板当中的数据类型不匹配!\n");
        CloseClipboard();//关闭剪切板，不然其他程序无法正常0使用剪切板
        return -1;
    }
    //获取剪切板里面的数据
    hclip=GetClipboardData(CF_TEXT);
    pbuf=(char *)GlobalLock(hclip);//加锁，返回一个VOID类型的指针
    GlobalUnlock(hclip);//解锁
   //printf("%s\n",pbuf);
    while(*pbuf!='\0')
    {
        //printf("%c\n",*pbuf);
        if(*pbuf!='\n')
            input(*pbuf);
        pbuf++;
    }
    CloseClipboard();//关闭剪切板，不然其他程序无法正常0使用剪切板
    return 0;
}
void save() //文件保存函数
{
    string file;
    system("cls");
    if(title!="新文件-未保存"){
        char choice;
        printf("是否要保存（y/n）\n");
        cin>>choice;
        switch(choice){
            case 'y':;
            case 'Y':file.assign(title); break;
            case 'n':;
            case 'N':return;
            default:save();return;
        }
    }
    else{
        printf("输入要保存的文件名（或保存路径+文件名）若不保存则输入0:\n");
        cin>>file;
        if(file=="0")
            return;
    }
    ofstream outfile;
    outfile.open(file,ios::out);
    
    Node *q=content;
    while(q!=NULL){
        Node *p=q->next;
        while(p!=NULL){
            //printf("%c",p->data);
            outfile<<p->data;
            p=p->next;
        }
        q=q->nextline;
        //printf("\n");
        if(q!=NULL)
            outfile<<'\n';
    }

    cout<<"文件已保存 "<<endl;
    title.assign(file);
    outfile.close();
    system("pause");
    return;
}
void read() //文件读取函数
{
    string file;
    system("cls");
    printf("输入要打开的文件名（或加载路径+文件名）:\n");
    cin>>file;
    char ch[200],*p;
    //printf("%s\n", file);
    ifstream infile(file,ios::in);
    if(!infile){
        printf("打开失败！文件不存在!\n");
        system("pause");
        return;
    }
    while(!infile.eof()){
        infile.getline(ch,200,'\n');
        p=ch;
        while(*p!='\0'){
            input(*(p++));
        }
        if(!infile.eof())
            input(13);
    }
    infile.close();
    printf("打开成功!\n");
    title.assign(file);
    system("pause");
}
void help() //帮助函数
{
    set_console_color(0);
    system("cls");
    char sss[]="文本输入使用说明：\n\n 功能模式（默认）\n\n- i 进入输入模式\n- u 撤回此前操作\n- r 重做已撤回的操作\n- h 帮助\n- q 退出\n\n 输入模式（INSERTMODE）\n\n- Esc 返回功能模式\n- 输入任意字符\n- Backspace 删除字符\n- Enter 换行\n- 方向键 移动光标\n- Ctrl+V 粘贴";
    printf("%s\n", sss);
    getch();
}
int main() //程序主函数
{
    system("chcp 65001"); //设置字符集 
    help();
	Init_stack(s);
    content->next=NULL;
    content->nextline=NULL;
    content->length=0;
    char key;
    int in=1;
    //system("pause");
    while(in){
        set_console_color(0);
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
	            case 'i':INSERTMODE=1;break;
	            case 'u':roolback(s);break;
	            case 'r':redo(s);break;
                case 's':save();break;
                case 'o':read();break;
                case 'h':help();break;
                case 'q':{
                    system("cls");
                    printf("你是否要退出？未保存的文件都将丢失（y/n）\n");
                    char choice;
                    cin>>choice;
                    switch(choice){
                            case 'y':;
                            case 'Y':in=0; break;
                            case 'n':;
                            case 'N':break;
                            default:break;
                        }
                }
	            default:break;
	        }
        }
    }
    return 0;
}