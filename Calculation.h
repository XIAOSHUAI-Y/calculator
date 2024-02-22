#include <stack>
#include <string>
#include <cmath>

#include "operation/power.h"
using namespace std;

bool isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// 定义函数来获取运算符的优先级
int getPriority(char op) {
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
	else
		return 0;
}

// 将中缀表达式转换为后缀表达式

string infixToPostfix(string infix)
{
	stack<char> opStack; // 运算符栈
	string postfix = ""; // 后缀表达式
	
	for (int i = 0; i < infix.length(); i++)
	{
		char ch = infix[i];
		
		if (isdigit(ch) || ch == '.')
		{ // 如果是数字，将连续的数字字符组合成完整数字，并将其作为字符串表示
			string numStr = "";
			while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.'))
			{
				numStr += infix[i];
				i++;
			}
			postfix += numStr;
			postfix += " "; // 在数字后面加上空格，用于区分多位数字
			i--;            // 回退一位，因为for循环会自增
		}
		else if (ch == '(')
		{ // 如果是左括号，入栈
			opStack.push(ch);
		}
		else if (ch == ')')
		{ // 如果是右括号，将栈内运算符弹出加入后缀表达式，直到遇到左括号
			while (!opStack.empty() && opStack.top() != '(')
			{
				postfix += opStack.top();
				postfix += " "; // 在运算符后面加上空格，用于区分多位数字
				opStack.pop();
			}
			if (!opStack.empty() && opStack.top() == '(')
			{
				opStack.pop(); // 弹出左括号
			}
		}
		else
		{
			if(ch != '-')
			{
				while (!opStack.empty() && opStack.top() != '(' && getPriority(opStack.top()) >= getPriority(ch))
				{
					postfix += opStack.top();
					postfix += " "; // 在运算符后面加上空格，用于区分多位数字
					opStack.pop();
				}
				opStack.push(ch); // 将当前操作符压入栈中
			}
			else
			{
				if(i == 0 || infix[i - 1] == '(')
					// 如果当前字符是负号且位于表达式开头或者前面是左括号，则视为负数处理
					postfix += '-';
				else
				{
					// 否则，视为减法运算符，将栈中优先级高于或等于当前操作符的操作符弹出并添加到后缀表达式中
					while (!opStack.empty() && opStack.top() != '(' && getPriority(opStack.top()) >= getPriority(ch))
					{
						postfix += opStack.top();
						postfix += " "; // 在运算符后面加上空格，用于区分多位数字
						opStack.pop();
					}
					opStack.push(ch); // 将当前操作符压入栈中
				}
			}
		}
	}
	
	while (!opStack.empty())
	{ // 将栈内剩余的运算符加入后缀表达式
		postfix += opStack.top();
		postfix += " "; // 在运算符后面加上空格，用于区分多位数字
		opStack.pop();
	}
	
	return postfix;
}

// 计算后缀表达式的值
string evaluatePostfix(string postfix) 
{
	
	stack<string> operandStack; // 操作数栈
	bool negative = false;//判断是否为负数
	for (int i = 0; i < postfix.length(); i++) 
	{
		if (postfix[i] == ' ') 
		{ // 跳过空格
			continue;
		}
		if (isdigit(postfix[i]) || postfix[i] == '.') 
		{ // 如果是数字，将连续的数字字符组合成完整数字，并将其作为字符串表示
			string numStr = "";
			if(negative == true) 
			{
				numStr += '-';
				negative = false;
			}
			while (i < postfix.length() && (isdigit(postfix[i]) || postfix[i] == '.')) {
				numStr += postfix[i];
				i++;
			}
			operandStack.push(numStr);
			i--; // 回退一位，因为for循环会自增
		} 
		else 
		{ // 如果是运算符，从栈中弹出两个操作数进行运算后再将结果入栈
			if(postfix[i] == '-' && (i == 0 || isdigit(postfix[i + 1]))) negative = true;
			else
			{
				string operand2 = operandStack.top();
				operandStack.pop();
				string operand1 = operandStack.top();
				operandStack.pop();
				string result;
				switch (postfix[i]) {
				case '+':
					result = Add(operand1, operand2);
					break;
				case '-':
					result = Sub(operand1, operand2);
					break;
				case '*':
					result = Mul(operand1, operand2);
					break;
				case '/':
					if(operand2 == "0") return "Input Error";
					result = Div(operand1, operand2);
					break;
				case '^':
					result = qm(operand1, operand2);
					break;
				default:
					return "Input Error";
				}
				operandStack.push(result); // 运算结果入栈
			}
		}
	}
	string res = operandStack.top();
	
	//去除末尾多余的0
	int dot = res.find('.');
	if(dot != string::npos)
	{
		int j = res.size();
		while(j--)
		{
			if(res[j] == '0') res.erase(j,1);
			else if(res[j] == '.'){
				res.erase(j, 1);
				break;
			}
			else if(res[j] != '0' || res[j] != '.') break;	
		}
	}
	return res; // 返回最终计算结果
}
