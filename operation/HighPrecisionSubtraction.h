#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std;

const int precision = 10;

// 判断num1和num2的大小，如果num1>num2，返回1， num1<num2返回2， num1 = num2 返回0
int cmp(string num1, string num2)
{
	if (num1.size() != num2.size())
	{
		if (num1.size() > num2.size())
			return 1;
		else
			return 2;
	}
	for (int i = 0; i < num1.size(); i++)
	{
		if (num1[i] != num2[i])
		{
			if (num1[i] > num2[i])
				return 1;
			else
				return 2;
		}
	}
	return 0;
}

string sub(string num1, string num2)
{
	string res;
	int borrow = 0;
	int i = num1.length() - 1;
	int j = num2.length() - 1;

	// 从最低位开始逐位相减
	while (i >= 0 || j >= 0)
	{
		int digit1 = i >= 0 ? num1[i--] - '0' : 0; // 获取第一个数字的当前位数
		int digit2 = j >= 0 ? num2[j--] - '0' : 0; // 获取第二个数字的当前位数

		int diff = digit1 - digit2 - borrow; // 当前位数的差，减去借位
		if (diff < 0)
		{ // 如果差值小于 0，则需要向前借位
			diff += 10;
			borrow = 1;
		}
		else
		{
			borrow = 0;
		}

		res.push_back(diff + '0'); // 将当前位的差值添加到结果字符串中
	}

	reverse(res.begin(), res.end()); // 翻转结果字符串，得到最终的高精度减法结果

	return res;
}

string add(string num1, string num2)
{
	string res;		 // 存储计算结果的字符串
	int carry = 0; // 进位值的初始值为0
	int i = num1.length() - 1;
	int j = num2.length() - 1;

	// 从最低位开始逐位相加
	while (i >= 0 || j >= 0)
	{
		int digit1 = i >= 0 ? num1[i--] - '0' : 0; // 获取第一个数字的当前位数
		int digit2 = j >= 0 ? num2[j--] - '0' : 0; // 获取第二个数字的当前位数

		int sum = digit1 + digit2 + carry; // 当前位数的和，加上进位值
		carry = sum / 10;									 // 计算新的进位值
		res.push_back(sum % 10 + '0');		 // 将当前位的和的个位数添加到结果字符串中
	}

	// 如果最高位有进位，则将进位值添加到结果字符串中
	if (carry != 0)
	{
		res.push_back(carry + '0');
	}

	reverse(res.begin(), res.end()); // 翻转结果字符串，得到最终的高精度加法结果

	return res;
}

string Sub(string num1, string num2)
{
	int dot1 = num1.find('.'); // 找到第一个数字的小数点位置
	int dot2 = num2.find('.'); // 找到第二个数字的小数点位置
	int len1 = num1.length();
	int len2 = num2.length();

	// 将小数点后的位数补齐
	if (dot1 == string::npos)
	{
		num1.append(precision, '0'); // 在第一个数字后面添加相应数量的 0
	}
	else
	{
		num1.append(precision - (len1 - dot1 - 1), '0'); // 将第一个数字的小数点后的位数补齐为指定精度
		num1.erase(dot1, 1);														 // 删除第一个数字中的小数点
	}

	if (dot2 == string::npos)
	{
		num2.append(precision, '0'); // 在第二个数字后面添加相应数量的 0
	}
	else
	{
		num2.append(precision - (len2 - dot2 - 1), '0'); // 将第二个数字的小数点后的位数补齐为指定精度
		num2.erase(dot2, 1);														 // 删除第二个数字中的小数点
	}

	string res;
	bool isNegative1 = false;
	bool isNegative2 = false;

	// 判断两个数字的符号
	if (num1[0] == '-')
	{
		isNegative1 = true;
		num1.erase(0, 1); // 移除第一个数字的负号
	}

	if (num2[0] == '-')
	{
		isNegative2 = true;
		num2.erase(0, 1); // 移除第二个数字的负号
	}

	// 根据两个数字的符号确定最终结果的符号
	bool isNegativeres = false;
	if (isNegative1 && !isNegative2)
	{
		res = add(num1, num2);
		isNegativeres = true;
	}
	else if (!isNegative1 && isNegative2)
	{
		res = add(num1, num2);
		isNegativeres = false;
	}
	else if (!isNegative1 && !isNegative2)
	{
		if (cmp(num1, num2) < 2)
		{
			isNegativeres = false;
		}
		else
		{
			isNegativeres = true;
			swap(num1, num2);
		}
		res = sub(num1, num2);
	}
	else if (isNegative1 && isNegative2)
	{
		if (cmp(num1, num2) != 1)
		{
			isNegativeres = false;
			swap(num1, num2);
		}
		else
		{
			isNegativeres = true;
		}
		res = sub(num1, num2);
	}
	res.insert(res.length() - precision, ".");
	for (int i = 0; i < res.length();)
	{
		if (res[i] == '0' && res[i + 1] != '.')
		{
			res.erase(0, 1);
		}
		if (res[i] == '0' && res[i + 1] == '.')
			break;
		if (res[i] != '0')
			break;
	}
	if(isNegativeres) res.insert(0, "-");
	return res;
}
