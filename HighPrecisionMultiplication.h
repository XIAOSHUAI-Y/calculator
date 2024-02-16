#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int precision = 10;

string mul(string num1, string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	vector<int> res(len1 + len2, 0);
	// 从最低位开始逐位相乘
	for (int i = len1 - 1; i >= 0; i--)
	{
		for (int j = len2 - 1; j >= 0; j--)
		{
			int digit1 = num1[i] - '0'; // 获取第一个数字的当前位数
			int digit2 = num2[j] - '0'; // 获取第二个数字的当前位数
			
			int product = digit1 * digit2; // 当前位数的乘积
			
			// 将乘积与对应的进位值相加
			res[i + j + 1] += product;
			res[i + j] += res[i + j + 1] / 10;
			res[i + j + 1] %= 10;
		}
	}
	// 将计算结果转换为字符串
	string res1;
	for (int i = 0; i < res.size() - precision; i++)
	{
		if (res1.empty() && res[i] == 0)
			continue; // 去除前导0
		res1.push_back(res[i] + '0');
	}
	return res1.empty() ? "0" : res1;
}

string Mul(string num1, string num2)
{
	int dot1 = num1.find('.');
	int dot2 = num2.find('.');
	int len1 = num1.size();
	int len2 = num2.size();
	
	// 如果其中一个数为0，则直接返回0
	if (num1 == "0" || num2 == "0")
	{
		return "0";
	}
	
	// 将小数点后的位数补齐
	if (dot1 == string::npos)
	{
		num1.append(precision, '0');
	}
	else
	{
		num1.append(precision - (len1 - dot1 - 1), '0');
		num1.erase(dot1, 1);
	}
	if (dot2 == string::npos)
	{
		num2.append(precision, '0');
	}
	else
	{
		num2.append(precision - (len2 - dot2 - 1), '0');
		num2.erase(dot2, 1);
	}
	
	string res;
	bool isNegative1 = false;
	bool isNegative2 = false;
	if (num1[0] == '-')
	{
		isNegative1 = true;
		num1.erase(0, 1);
	}
	if (num2[0] == '-')
	{
		isNegative2 = true;
		num2.erase(0, 1);
	}
	bool isNegativeres = false;
	if ((isNegative1 && !isNegative2) || (!isNegative1 && isNegative2))
		isNegativeres = true;
	res = mul(num1, num2);
	if (isNegativeres)
		res.insert(0, "-");
	res.insert(res.size() - precision, ".");
	return res;
}

