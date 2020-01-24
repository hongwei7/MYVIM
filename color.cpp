#include "stdio.h"
#include "windows.h"
 int columns, rows;
 void set_pointer(int x,int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(hOut,pos);
}
void set_console_color(unsigned short color_index)
{
	if(color_index==0)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	if(color_index==1)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
FOREGROUND_RED);

	if(color_index==2)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
FOREGROUND_BLUE);
if(color_index==3)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY |
FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
FOREGROUND_GREEN);
}


int get_windows_size()
{

 CONSOLE_SCREEN_BUFFER_INFO csbi;
 GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
 columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
 rows = csbi.srWindow.Bottom - csbi.srWindow.Top -1;

/*

 printf("columns: %dn", columns);


 printf("rows: %dn", rows);

*/
 return 0;

}