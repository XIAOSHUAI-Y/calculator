#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300 + 4;
const int precision3 = 10;

int tmp[MAXN] = {}; // 交换用字符串
int a[MAXN] = {};		// 存储加数A
int b[MAXN] = {};		// 存储加数B
int c[MAXN] = {};		// 存储和B

int compare(int a[], int b[])
{
	// 索引为0的数据为数组长度
	if (a[0] > b[0])
	{
		return 1;
	}
	else if (a[0] < b[0])
	{
		return -1;
	}

	// 逐位比较
	for (int i = a[0]; i > 0; i--)
	{
		if (a[i] > b[i])
		{
			return 1;
		}
		else if (a[i] < b[i])
		{
			return -1;
		}
	}

	return 0;
}

void numcpy(int a[], int b[], int dest)
{
	// 将数组右移，使两个数组右端对齐，形参q数组储存右移后的结果
	for (int i = 1; i <= a[0]; i++)
	{
		b[i + dest - 1] = a[i];
	}
	b[0] = a[0] + dest - 1;
}

string div(string s1, string s2)
{	
	
	// 处理被除数
	int len = s1.size();
	a[0] = len;
	for (int i = 0; i < len; i++)
	{
		a[len - i] = s1[i] - '0';
	}

	// 处理除数
	len = s2.size();
	b[0] = len;
	for (int i = 0; i < len; i++)
	{
		b[len - i] = s2[i] - '0';
	}
	c[0] = a[0] - b[0] + 1;
	for (int i = c[0]; i > 0; i--)
	{
		memset(tmp, 0, sizeof(tmp));
		// 高位对齐
		numcpy(b, tmp, i);

		while (compare(a, tmp) >= 0)
		{
			c[i]++;
			// 减法
			for (int j = 1; j <= a[0]; j++)
			{
				if (a[j] < tmp[j])
				{
					a[j + 1]--;
					a[j] += 10;
				}
				a[j] -= tmp[j];
			}

			int k = a[0];
			while (a[k] == 0)
			{
				k--;
			}
			a[0] = k;
		}
	}

	// 控制最高位的0
	while (c[0] > 0 && c[c[0]] == 0)
	{
		c[0]--;
	}
	string res;
	int j = 0;
	// 逆序打印输出商和余数
	for (int i = c[0]; i > 0; i--)
	{
		res += (c[i] + '0');
		// printf("%d", c[i]);
	}
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	memset(c, 0, sizeof c);
	// printf("\n");
	return res;
}

string Div(string num1, string num2)
{
	int m, n; // 代表被除数和除数在去除小数点时的扩大倍数
	string res;
	bool isNegative1 = false;
	bool isNegative2 = false;
	if (num1 == "0")
	{
		return "0";
	}
	if (num2 == "0")
	{
		return "Input Error";
	}
	if (num1[0] == '-')
	{
		isNegative1 = true;
		num1.erase(0, 1);
	}
	if (num2[0] == '-')
	{
		isNegative2 = true;
		num2.erase(0, 1); // 移除第二个数字的负号
	}
	bool isNegativeres = false;
	if ((isNegative1 && !isNegative2) || (!isNegative1 && isNegative2))
		isNegativeres = true;
	int dot1 = num1.find('.'); // 找到第一个数字的小数点位置
	int dot2 = num2.find('.'); // 找到第二个数字的小数点位置
	int len1 = num1.length();
	int len2 = num2.length();
	if (dot1 == string::npos)
	{
		m = 0;
	}
	else
	{
		m = len1 - dot1 - 1;
		num1.erase(dot1, 1);
	}
	if (dot2 == string::npos)
	{
		n = 0;
	}
	else
	{
		n = len2 - dot2 - 1;
		num2.erase(dot2, 1);
	}
	if (m >= n)
	{
		if (m - n <= precision3)
		{
			num1.append(precision3 - (m - n), '0'); // 在分子后面添0，保证分子扩大倍数是分母的precision3 + 1倍
		}
		else
		{
			num2.append((m - n) - precision3, '0'); // 在分母后面添0，保证分子扩大倍数是分母的precision3 + 1倍
		}
	}
	else
	{
		num1.append(precision3 + (n - m), '0');
	}
	res = div(num1, num2);
	int t = res.size();
	if (t <= precision3)
	{
		int s = precision3 - t + 1;
		while (s--)
		{
			res.insert(0, "0");
		}
	}
	if (isNegativeres)
		res.insert(0, "-");
	res.insert(res.size() - precision3, ".");
	return res;
}
