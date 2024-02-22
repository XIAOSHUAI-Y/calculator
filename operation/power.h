#include <bits/stdc++.h>
#include "HighPrecisionAddition.h"
#include "HighPrecisionDivision.h"
#include "HighPrecisionMultiplication.h"
#include "HighPrecisionSubtraction.h"
using namespace std;


string innerQm(string a, long long b){
	if(b == 1){
		return a ;
	}
	else if(b < 0)
	{
		b *= -1;
		string m = innerQm(a, b);
		return Div("1", m);
	}
	else if(b % 2 != 0){
		b /= 2;
		string t = Mul(a, a);
		return Mul(a, innerQm(t, b));
	}
	else{
		
		string t = Mul(a, a);
		return innerQm(t, b / 2);
	}
}

string qm(string a, string b){
	int dot = b.find(".");
	if(dot != string::npos || a[0] > '9' || a[0] < '0') return "Input Error";
	if(b == "0") return "1";
	
	long long numb = stoll(b);
	return innerQm(a, numb);
	
}




