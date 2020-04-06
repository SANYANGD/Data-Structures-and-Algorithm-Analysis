#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
typedef struct {
	char* base;
	char* top;
	int size;
}MyStack;
//初始化
int myStack(MyStack& S) {
	S.base = (char*)malloc(sizeof(char) * 100);
	if (!S.base) exit(0);
	S.top = S.base;
	S.size = 100;
	return 1;
}

//入栈 
int Push(MyStack& S, int e) {
	if (S.top - S.base == S.size) return 0;
	*S.top++ = e;
	return 1;
}
//出栈 
int Pop(MyStack& S, int& e) {
	if (S.top == S.base) return 0;
	e = *--S.top;
	return 1;
}
//取栈顶元素 
int Top(MyStack S) {
	if (S.top != S.base)  return *(S.top - 1);
}

//判断读入字符是否为运算符
int isSym(char e) {
	if (e == '+' || e == '-' || e == '*' || e == '/' || e == '(' || e == ')' || e == '#') return 1;
	else return 0;
}
//运算
int Count(int x, char symbol, int y) {
	int z=0;
	//x = x - '0'; y = y - '0';
	switch (symbol) {
	case '+': z = x + y ; break;
	case '-': z = x - y ; break;
	case '*': z = x * y ; break;
	case '/': z = (float)x/(float)y ; break;
	}
	return z;
}
//比较运算符的优先级 
char Priority(char a, char b, int isbracket) {
	if (a == '#' || a == '(' || b == '(') return '<';
	else if (a == ')' || b == '#') return '>';
	else if (a == '+' || a == '-') {
		if (b == '+' || b == '-' || b == ')' )  return '>';
		else if (b == '*' || b == '/' )  return '<';
	}else if (a == '*' || a == '/') {
		if (b == '+' || b == '-' || b == '*' || b == '/' )  return '>';
		else if (b == '(')  return '<';
	}
}

int Cal(int* ch) {
	MyStack NUM, SYM;
	int symbol, a, b;
	int isbracket = 0;

	myStack(NUM);
	myStack(SYM);
	Push(SYM, '#');

	for (int i = 0; i < 10; i++) {
		if (ch[i] == '(') isbracket++;
		if (ch[i] == ')') isbracket--;
		if (isSym(ch[i]) == 0) {
			Push(NUM, ch[i]);
		}
		else {
			switch (Priority(Top(SYM), ch[i], isbracket)) {
			case '<':
				Push(SYM, ch[i]);
				break;
			case '>':
				Pop(SYM, symbol);
				Pop(NUM, b);
				Pop(NUM, a);
				Push(NUM, Count(a, symbol, b));
				break;
			}
		}
		if (ch[i] == '#') break;
	}
	int out = Top(NUM);
	return out;
}

void test() {
	int total = 0;
	int right = 0;

	total++;
	int ch[100] = { 12,'+',2,'+',2,'#' }; //这里输入算式
	int result = Cal(ch);
	int rightresult=3;
	printf("输入的表达式为：\n");
	printf("预期的结果为："); 
	printf("%d\n", rightresult);
	printf("实际计算的结果为：");
	printf("%d\n", result);
	if (result== rightresult) {
		right++;
		printf("计算正确\n");
	}else printf("计算错误\n\n");

	float rate = (float)right / (float)total;
	printf("此次测试的正确率为：%f\n",rate);
}

int main() {
	int istest = 1;

	if (istest == 0) {
		char ch[100];
		printf("请输入表达式,并以#结束: ");
		gets_s(ch);
		int in[100];
		int i = 0;
		do {
			if (isSym(ch[i]) == 0) {
				ch[i]= ch[i]-'0';
			}
			in[i] = ch[i];
			i++;
		} while (ch[i-1] != '#');
		
		int out = Cal(in);
		printf("结果是: %d\n", out);
	}else test();
	
	return 0;
}