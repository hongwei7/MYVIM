struct OPDATA
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
