#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define BLOCK_SIZE 20
#define HEIGHT 30
#define WIDTH 40

int Blocks[HEIGHT][WIDTH] = { 0 };
char moveDirection;
int isFailure = 0;
int food_i, food_j;
int mode = 0;
int oldTail_i, oldTail_j, oldHead_i, oldHead_j;
int time = 10;

void start()
{
	

	setbkcolor(WHITE);		
	cleardevice();			
	setbkmode(TRANSPARENT);	//璁剧疆瀛椾綋鑳屾櫙鑹蹭负閫忔槑
	settextcolor(BLACK);		//璁剧疆瀛椾綋棰滆壊涓虹孩鑹?
	
	outtextxy(390, 130, L"功能选择");
	outtextxy(380, 200, L"1.普通模式");
	outtextxy(380, 250, L"2.快速模式");
	outtextxy(380, 300, L"3.穿墙模式");
	outtextxy(280, 330, L"数字键1,2或上下键选择模式，enter键进入游戏");
	outtextxy(280, 350, L"字母键W,S,A,D 方向键上下左右 控制方向");
//	outtextxy(130, 400, L"鐩稿叧鍐呭锛?);
//		outtextxy(160, 380, L"关注微信公众号");
//	outtextxy(160, 410, L"编程学习加群:  879098023");
}
void chose()
{
	int h = 200;
	while (1)
	{
		char input = _getch();
		
		switch (input)
		{
		case '1':
		    start();
			outtextxy(360, 200, L"->");
			h = 200;
			mode = 0;
			break;
		case '2':
			start();
			outtextxy(360, 250, L"->");
			mode = 1;
			h = 250;
			break;
		case '3': 
			start();
			outtextxy(360, 300, L"->");
			mode = 2;
			h = 300;
			break;
		case 13:
			return;
			break;
		case 72:
			start();
			if (h == 200) {
				h = 300;
				outtextxy(360, h, L"->");
				mode = 2;
			}
			else if(h==250){
				h = 200; outtextxy(360, h, L"->");
				mode = 0;
			}
			else {
				h = 250; outtextxy(360, h, L"->");
				mode = 1;
			}
			break;
		case 80:
			start();
			if (h ==200) {
				h = 250;
				outtextxy(360, 250, L"->");
				mode = 1;
			}
			else if (h == 250) {
				h = 300;
				outtextxy(360, 300, L"->");
				mode = 2;
			}
			else  { 
				h = 200; 
			outtextxy(360, 200, L"->"); 
			mode = 0;
			}
			break;
			
		}
		Sleep(100);
		
	}
}


void startup()//初始化函数
{
	int i;
	Blocks[HEIGHT / 2][WIDTH / 2] = 1;
	for (i = 1; i <= 4; i++)
		Blocks[HEIGHT / 2][WIDTH / 2 - i] = i + 1;
	moveDirection = 'D';
	food_i = rand() % (HEIGHT - 5) + 2;
	food_j = rand() % (WIDTH - 5) + 2;
	initgraph(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);
	setlinecolor(RGB(200, 200, 200));
	BeginBatchDraw();
}

void show()
{
	cleardevice();
	int i, j;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if(Blocks[i][j]>0)
			setfillcolor(HSVtoRGB(Blocks[i][j] * 10, 0.9, 1));
		else setfillcolor(RGB(150, 150, 150));

		fillrectangle(j * BLOCK_SIZE, i * BLOCK_SIZE, (j + 1) * BLOCK_SIZE, (i + 1) * BLOCK_SIZE);
		
		}
	}

	setfillcolor(RGB(0, 255, 0));//食物颜色为绿色
	fillrectangle(food_j * BLOCK_SIZE, food_i * BLOCK_SIZE, (food_j + 1) * BLOCK_SIZE, (food_i + 1) * BLOCK_SIZE);

	if (isFailure)
	{
		setbkmode(TRANSPARENT);
		settextcolor(RGB(255, 0, 0));
		settextstyle(80, 0, _T("宋体"));
		outtextxy(240, 220, _T("游戏失败"));
	}

	FlushBatchDraw();
}

void movesnake()
{
	int i, j;
	for (i = 0; i < HEIGHT; i++)
		for (j = 0; j < WIDTH; j++)
			if (Blocks[i][j] > 0)//大于0的为蛇元素
				Blocks[i][j]++;

	
	int max = 0;
	if (j > 30)j = 0;
	if (i > 30)i = 0;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (max < Blocks[i][j])
			{
				max = Blocks[i][j];
				oldTail_i = i;
				oldTail_j = j;
			}
			if (Blocks[i][j] == 2)
			{
				oldHead_i = i;//数值为2是旧蛇头的位置
				oldHead_j = j;
			}
		}
	}
	
	
	int newHead_i = oldHead_i;
	int newHead_j = oldHead_j;
//	newHead_j = oldHead_j + 1;
	if (mode == 2)
	{
		if (newHead_j >= 39 && moveDirection == 'D')
			newHead_j = -1;
		else if ((oldHead_j < 1) && moveDirection == 'A')
			oldHead_j = 40;

		if (newHead_i <= 0 && moveDirection == 'W')
			newHead_i = 30;
		else if (newHead_i >= 29 && moveDirection == 'S')
			newHead_i = -1;

		time = 5;
	}
	else if (mode == 1)time = 5;

	if (moveDirection == 'A')
		newHead_j = oldHead_j - 1;
	else if (moveDirection == 'D')
		newHead_j = newHead_j + 1;
	else if (moveDirection == 'W')
		newHead_i = newHead_i - 1;
	else if (moveDirection == 'S')
		newHead_i = newHead_i + 1;
	if (mode == 1) {
		if (newHead_i >= HEIGHT || newHead_i < 0 || newHead_j >= WIDTH || newHead_j < 0)
		{

			isFailure = 1;
			return;
		}
	}
	else {
		if (Blocks[newHead_i][newHead_j] > 2)
		{
			
			isFailure = 1;
			return;
		}
	}
	
	Blocks[newHead_i][newHead_j] = 1;
	if (newHead_i == food_i && newHead_j == food_j)
	{
		food_i = rand() % (HEIGHT - 5) + 2;
		food_j = rand() % (WIDTH - 5) + 2;
	}
	else Blocks[oldTail_i][oldTail_j] = 0;
//	Blocks[newHead_i][newHead_j] = 1;
//	Blocks[oldTail_i][oldTail_j] = 0;
	
}

void updateWithoutInput()
{
	if (isFailure)
		return;

	
	static int waitIndex = 1;
	waitIndex++;
	if(waitIndex==time)
	{
		movesnake();
		waitIndex = 1;
	}
	
	Sleep(2);
//	movesnake();
}

void updateWithInput()
{
	if (_kbhit()&&isFailure==0)
	{
		char input = _getch();
		
		switch (input)
		{
		case'A':
		case'a':
		case 75:
			if (moveDirection != 'D')
				moveDirection = 'A';
			break;
		case'D':
		case'd':
		case 77:
			if (moveDirection != 'A')		
				moveDirection = 'D';
			break;
		case'W':
		case'w':
		case 72:
			if (moveDirection != 'S')
				moveDirection = 'W';
			break;
		case'S':
		case's':
		case 80:
			if (moveDirection != 'W')
				moveDirection = 'S';
			break;
		}
	//	movesnake();
/*		if (input == 'A' || input == 'S' || input == 'D' || input == 'W')
		{
			moveDirection = input;
			movesnake();
		}
		*/
		
	}

}

void regame()
{
	initgraph(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);
	setbkcolor(RGB(0, 0, 0));
	cleardevice();
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 0, 0));
	settextstyle(80, 0, _T("宋体"));
	outtextxy(240, 220, _T("是否重新开始"));

}

int main()
{
	initgraph(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);
	start();
	outtextxy(360, 200, L"->");
	mode = 1;
	chose();
	
	startup();
	while (1)
	{
		
		show();
		if (isFailure == 1)
		{
			_getch();
			break;
		}
		updateWithoutInput();
		updateWithInput();
		
	}
	
//	_getch();
	closegraph();
	return 0;
}