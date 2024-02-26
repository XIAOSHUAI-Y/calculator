#include <iostream>
#include <vector>
#include <fstream>
#include <easyx.h>
#include <graphics.h>
#include <conio.h>
using namespace std;

const int recordsPerPage = 12;

// 定义历史记录节点
struct HistoryPage
{
	vector<string> entry; // 历史记录内容
	
	HistoryPage* next; // 指向下一个历史记录节点的指针
	HistoryPage* prev;
};

// 定义保存历史记录的文件路径
const string history_file = "C:\\Users\\86191\\Documents\\Project\\Calculator\\history.txt";

// 保存历史记录到文件
void saveHistory(const std::string& entry)
{
	ofstream file(history_file, ios::app); // 以追加模式打开历史记录文件
	if (file.is_open())
	{
		file << entry << endl; // 将历史记录写入文件
		file.close(); // 关闭文件
	}
	else
	{
		cout << "Unable to open history file" << endl; // 无法打开历史记录文件
	}
}

int totalPages = 1; // 总页数
int currentPage = 1; // 当前页数
HistoryPage* head = new HistoryPage; // 头节点指针
HistoryPage* current = head; // 当前节点指针

void shownext();

// 显示历史记录
void showHistory()
{
	
	ifstream file(history_file); // 打开历史记录文件
	if (file.is_open())
	{
//		HistoryNode* head = nullptr; // 头节点指针
//		HistoryNode* current = nullptr; // 当前节点指针
		
		string line;
		// 创建新的历史记录节点
		
		
		// 读取全部历史进链表
		string currLine;  
		for (int i = 0;  std::getline(file, currLine); i++){
			if (i == recordsPerPage){
				HistoryPage* newPage = new HistoryPage;
				newPage->next = nullptr;
				current->next = newPage;
				newPage->prev = current;
				current = newPage;
				totalPages++;
				i = 0;
			}
			current->entry.push_back(currLine);
		}
		
		file.close();
	}
	current = head;
}

void printCurrPage(){
	int y = 30;
	for(int i = 0; i < current->entry.size(); i++){
		settextcolor(WHITE);
		settextstyle(30, 0, _T("宋体"));
		outtextxy(15, y, current->entry[i].c_str());
		y += 40;
	}
}
void shownext()
{		
	if(!current->next){
		settextcolor(WHITE);
		settextstyle(25, 0, "黑体");
		outtextxy(5, 520, "这是最后一页");
	}
	else current = current->next;
	printCurrPage();
}

void showprev()
{
	if(!current->prev){
		settextcolor(WHITE);
		settextstyle(25, 0, "黑体");
		outtextxy(5, 520, "这第一页");
	}
	else current = current->prev;
	printCurrPage();
}
