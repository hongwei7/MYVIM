#include<iostream>
using namespace std;
#define max_size 50
typedef char elem;

struct Node
{
    elem data;
    Node * next;
    Node * nextline;
    int length;
};

