#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include<math.h>
#include <stdlib.h>
#include <easyx.h>
#include "Calculation.h"
#include "History.h"
#define OK    1
#define ERROR	 0

void Paint();            //页面绘制
double dis(int x1, int y1, int x2, int y2);
string displayAnswer(string infixExpression);

//绘制历史记录界面
void Paint2()
{
	initgraph(300, 600);
	setbkcolor(RGB(51, 51, 51));
//	setfillcolor();
	for (int y = 0; y < 20; y++) {
		setcolor(RGB(51, 51, 51));   //设置线条颜色为灰色
		line(0, y, 400, y);      //用循环语句画平行直线Line（x1,y1）（x2,y2）为直线的两个端点的坐标
	}
	settextcolor(WHITE);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(10, 0, "历史记录");
	
	settextcolor(WHITE);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(230, 570, "下一页");
	
	settextcolor(WHITE);
	settextstyle(20, 0, _T("宋体"));
	outtextxy(10, 570, "上一页");
	
	showHistory();
	printCurrPage();
	MOUSEMSG m;
	while(1)
	{
		m = GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			while(m.x >= 10 && m.x <= 300 && m.y >= 570 && m.y <= 600)
			{
				//清空上一次记录界面
				for (int y = 30; y < 550; y++) {
					setcolor(BLACK);
					line(0, y, 400, y);
				}
				//点击”下一页“
				if(m.x >= 230 && m.x <= 300){
					if(!current->next){
						settextcolor(WHITE);
						settextstyle(25, 0, "黑体");
						outtextxy(15, 520, "这是最后一页");
					}
					else current = current->next;
					printCurrPage();
//					shownext();
				}
				if(m.x >= 10 && m.x <= 80){
					if(!current->prev){
						settextcolor(WHITE);
						settextstyle(25, 0, "黑体");
						outtextxy(15, 520, "这是第一页");
					}
					else current = current->prev;
					printCurrPage();
//					showprev();
				}
				break;
			}
			break;
		}
	}	
}


void Paint() {
	int number;
	// 初始化图形模式
	initgraph(300, 600);   //初始化一个300*600的画布
	// 设置背景为深灰色
	setbkcolor(RGB(51, 51, 51));    //设置背景为深灰色
	int c;
	for (int y = 0; y < 20; y++) {
		setcolor(RGB(51, 51, 51));   //设置线条颜色为灰色
		line(0, y, 400, y);      //用循环语句画平行直线Line（x1,y1）（x2,y2）为直线的两个端点的坐标
	}
	//设置文本颜色
	settextcolor(WHITE);      //设置当前文字颜色
	//输出文本信息
	settextstyle(20, 0, _T("宋体"));
	//settextstyle(20, 10, L"宋体");//字体的宽+字体的高+字体样式
	//输出文本信息
	outtextxy(10, 0, "计算器");//文本坐标+文本内容（在指定位置输出字符串）
	outtextxy(210, 0, "历史记录");
	settextstyle(40, 0, "黑体");
	setbkmode(TRANSPARENT); //这个函数用于设置当前设备图案填充和文字输出时的背景模式。背景是透明的。
	//画橙色圆
	setcolor(RGB(220, 95, 8));//设置前景颜色
	setfillcolor(RGB(220, 95, 8));  //设置充填颜色 
	setbkcolor(BLACK);  //背景颜色
	fillcircle(255, 550, 30);  //画有边框的充填原圆（x,y,z）为坐标
	settextcolor(WHITE);      //设置当前文字颜色
	outtextxy(245, 533, "=");
	setcolor(RGB(247, 143, 0));
	setfillcolor(RGB(247, 143, 0));
	setbkcolor(BLACK);
	settextcolor(WHITE);
	fillcircle(255, 480, 30);
	outtextxy(245, 463, "+");
	fillcircle(255, 410, 30);
	outtextxy(245, 393, "-");
	fillcircle(255, 340, 30);
	settextstyle(30, 0, "黑体");
	outtextxy(240, 325, "×");
	fillcircle(255, 270, 30);
	outtextxy(240, 255, "/");
	//画深色圆
	setcolor(RGB(51, 51, 51));
	setfillcolor(RGB(51, 51, 51));
	setbkcolor(BLACK);
	//右边
	settextcolor(WHITE);
	settextstyle(40, 0, "黑体");
	fillcircle(185, 550, 30);   //圆
	outtextxy(180, 530, ")");
	fillcircle(185, 480, 30);
	outtextxy(175, 460, "3");
	fillcircle(185, 410, 30);
	outtextxy(175, 390, "6");
	fillcircle(185, 340, 30);
	outtextxy(175, 320, "9");
	/*fillcircle(185, 270, 30);*/
	//中间
	fillcircle(115, 550, 30);
	outtextxy(105, 530, "0");
	fillcircle(115, 480, 30);
	outtextxy(105, 460, "2");
	fillcircle(115, 410, 30);
	outtextxy(105, 390, "5");
	fillcircle(115, 340, 30);
	outtextxy(105, 320, "8");
	//左边
	fillcircle(45, 550, 30);
	outtextxy(35, 530, "(");
	fillcircle(45, 480, 30);
	outtextxy(35, 460, "1");
	fillcircle(45, 410, 30);
	outtextxy(35, 390, "4");
	fillcircle(45, 340, 30);
	outtextxy(35, 320, "7");
	//画浅色圆
	setcolor(RGB(165, 165, 165));
	setfillcolor(RGB(165, 165, 165));
	setbkcolor(BLACK);
	settextcolor(WHITE);
	fillcircle(185, 270, 30);
	outtextxy(175, 252, "C");
	fillcircle(115, 270, 30);
	settextstyle(40, 0, "黑体");
	outtextxy(105, 265, "^");
	fillcircle(45, 270, 30);
	outtextxy(20, 255, "·");
	
	/*Stack num, opt;*/
	char str[4000] = { 0 };
	int i = 0, tmp = 0, j;
	int count = 0;
	MOUSEMSG m;
	int temp = 0, k = 255, go = 0;
	//设置文本颜色
	settextcolor(WHITE);
	//设置文本样式
	settextstyle(40, 0, "黑体");//字体的宽+字体的高+字体样式
	while (go == 0)
	{
		m = GetMouseMsg();// 获取鼠标事件
		switch (m.uMsg)
		{
			case WM_LBUTTONDOWN:// 当左键按下时
			while (m.x >=15 && m.x <= 300 && m.y >= 0 && m.y <= 580)
			{
				// 根据鼠标点击的位置判断用户输入的内容
				if (dis(m.x, m.y, 45, 480) <= 30) {
					str[i] = '1';
				}
				if (dis(m.x, m.y, 115, 480) <= 30) {
					str[i] = '2';
				}
				if (dis(m.x, m.y, 185, 480) <= 30) {
					str[i] = '3';
				}
				if (dis(m.x, m.y, 45, 410) <= 30) {
					str[i] = '4';
				}
				if (dis(m.x, m.y, 115, 410) <= 30) {
					str[i] = '5';
				}
				if (dis(m.x, m.y, 185, 410) <= 30) {
					str[i] = '6';
				}
				if (dis(m.x, m.y, 45, 340) <= 30) {
					str[i] = '7';
				}
				if (dis(m.x, m.y, 115, 340) <= 30) {
					str[i] = '8';
				}
				if (dis(m.x, m.y, 185, 340) <= 30) {
					str[i] = '9';
				}
				if (dis(m.x, m.y, 45, 550) <= 30) {
					str[i] = '(';
				}
				if (dis(m.x, m.y, 115, 550) <= 30) {
					str[i] = '0';
				}
				if (dis(m.x, m.y, 185, 550) <= 30) {
					str[i] = ')';
				}
				if (dis(m.x, m.y, 255, 550) <= 30) {
					string expression(str);
					string result = displayAnswer(expression);
					expression += "=";
					expression += result;
					saveHistory(expression);
					memset(str, '\0',sizeof str);
					strcpy(str, result.c_str());
					i = result.size();
					count = i;
					break;
				}
				if (dis(m.x, m.y, 255, 480) <= 30) {
					str[i] = '+';
				}
				if (dis(m.x, m.y, 255, 410) <= 30) {
					str[i] = '-';
				}
				if (dis(m.x, m.y, 255, 340) <= 30) {
					str[i] = '*';
				}
				if (dis(m.x, m.y, 255, 270) <= 30) {
					str[i] = '/';
				}
				if (dis(m.x, m.y, 45, 270) <= 30) {
					str[i] = '.';
				}
				if (dis(m.x, m.y, 115, 270) <= 30) {
					str[i] = '^';
				}
				//点击“历史记录”
				if((m.x >= 195 && m.x <= 285) && (m.y >= 0 && m.y <= 10)){
					Paint2();
				}
				if (dis(m.x, m.y, 185, 270) <= 30) {
					return;
				}
				
				/*setbkcolor(BLACK);*/
				// 清空上次绘制的内容，设置新的绘制颜色和字体样式
				for (int y = 20; y < 200; y++) {
					setcolor(BLACK);
					line(0, y, 400, y);
				}
				settextcolor(WHITE);
				for (j = 0; j <= i; j++)
				{
					if (count < 12) {
						outtextxy(k - 20 * (count - j), 50, str[j]);
					}
					else if (count < 17) {
						settextstyle(30, 0, "黑体");
						outtextxy(k - 15 * (count - j), 50, str[j]);
					}
					else if (count < 22){
						settextstyle(24, 0, "黑体");
						outtextxy(k - 12 * (count - j), 50, str[j]);
					}else if(count < 26){
						settextstyle(20, 0, "黑体");
						outtextxy(k - 10 * (count - j), 50, str[j]);
					}else{
						settextstyle(16, 0, "黑体");
						outtextxy(k - 8 * (count - j), 50, str[j]);
					}
					
				}
				
//				Sleep(1000);
				i++;
				count++;
				break;
			}
			break;
			
		}
	}
	
	getchar();
}

string displayAnswer(string infixExpression){
	for (int y = 150; y < 200; y++) {
		setcolor(BLACK);
		line(0, y, 300, y);
	}
	string postfixExpression = infixToPostfix(infixExpression);
	
	string result = evaluatePostfix(postfixExpression);
	
	int resultLen = result.size(), fontSize = 40, step = 20;
	
	if(resultLen <= 17 && resultLen > 12) {
		fontSize =30;
		step = 15;
	}
	else if(resultLen < 22 && resultLen > 17 ){
		fontSize = 24;
		step = 12;
	}
	else if(resultLen >= 22){
		fontSize = 16;
		step = 8;
	}
	
	settextcolor(WHITE);
	settextstyle(fontSize, 0, "黑体");
	outtextxy(255 - step * (result.size() - 1), 150, result.c_str());
	return result;
}

//判断距离

double dis(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
	while(true){
		Paint();	
	}
	return 0;
}
