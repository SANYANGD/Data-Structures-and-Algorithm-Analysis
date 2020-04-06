#include <iostream>
#include <cmath>//isdigit() 介于0~9的数字时，返回一个非零值，否则返回零
#include <stack>
#include <string>
using namespace std;

//转换为后缀表达式
string transform(string str){
	stack<char> ope;
	string exp = "";
	for (int i = 0; i<int(str.size()); i++){
		if (str[i] == '.' || isdigit(str[i])){
			exp += str[i];
		}
		else if (str[i] == '+' || str[i] == '-'){
			if (isdigit(str[i-1])){
				exp += " ";//每个数字的后面都加一个空格加以区分
				if (ope.empty() || ope.top() == '('){
					ope.push(str[i]);
				}else{
					while (!ope.empty() && ope.top() != '('){
						exp += ope.top();
						ope.pop();
					}
					ope.push(str[i]);
				}
			}
			else{
				if (ope.empty() || ope.top() == '('){
					ope.push(str[i]);
				}else{
					while (!ope.empty() && ope.top() != '('){
						exp += ope.top();
						ope.pop();
					}
					ope.push(str[i]);
				}
			}
		}else if (str[i] == '*' || str[i] == '/' || str[i] == '%'){
			if (isdigit(str[i-1])){
				exp += " ";
				if (ope.empty() || ope.top() == '(' || ope.top() == '+' || ope.top() == '-'){
					ope.push(str[i]);
				}else{
					while (!ope.empty() && ope.top() != '(' && ope.top() != '+' && ope.top() != '-'){
						exp += ope.top();
						ope.pop();
					}
					ope.push(str[i]);
				}
			}else{
				if (ope.empty() || ope.top() == '(' || ope.top() == '+' || ope.top() == '-'){
					ope.push(str[i]);
				}else{
					while (!ope.empty() && ope.top() != '(' && ope.top() != '+' && ope.top() != '-'){
						exp += ope.top();
						ope.pop();
					}
					ope.push(str[i]);
				}
			}
		}else if (str[i] == '^'){
			if (str[i-1] != ')'){
				exp += " ";
			}
			ope.push(str[i]);
		}else if (str[i] == '('){
			ope.push(str[i]);
		}else if (str[i] == ')'){
			exp += " ";
			while (ope.top() != '('){
				exp += ope.top();
				ope.pop();
			}
			ope.pop();
		}else{
			return "有错误";
		}
	}
	while (!ope.empty()){//遍历完表达式将堆栈中的所有运算符输出
		if (isdigit(exp[exp.length() - 1])){
			exp = exp + " " + ope.top();
			ope.pop();
		}else{
			exp = exp + ope.top();
			ope.pop();
		}
	}
	return exp;
}

//检查输入的表达式是否有误
int examine(string str){
	if ((isdigit(str[str.length() - 1]) != 0 || str[str.length() - 1] == ')') && 
		(isdigit(str[0]) != 0 || str[0] == '+' || str[0] == '-' || str[0] == '(')){
		for (int i = 0; i<int(str.length()); i++){
			if (str[i] == '/' || str[i] == '%' || str[i] == '*' || str[i] == '^'){
				if (str[i+1] == '/' || str[i + 1] == '*' || str[i + 1] == '%' || str[i + 1] == ')' || str[i + 1] == '.'){
					cout << "表达式有错误" << endl;
					return 1;
					break;
				}
			}else if (str[i] == '+' || str[i] == '-'){
				if (str[i+1] == '/' || str[i+1] == '*' || str[i+1] == '%' || str[i+1] == ')' || str[i+1] == '.' || str[i+1] == '^'){
					cout << "表达式有错误" << endl;
					return 1;
					break;
				}
			}else if (isdigit(str[i]) != 0){
				if (str[i+1] == '('){
					cout << "表达式有错误" << endl;
					return 1;
					break;
				}
			}else if (isdigit(str[i]) == 0 && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' 
				&& str[i] != '^' && str[i] != '%' && str[i] != '(' && str[i] != ')' && str[i] != '.'){
				cout << "表达式有错误" << endl;
				return 1;
				break;
			}else if (str[i] == '.'){
				if (isdigit(str[i+1]) == 0){
					cout << "表达式有错误" << endl;
					return 1;
					break;
				}
			}
			while (i == str.length() - 1){
				//cout << "表达式正确" << endl;
				return 2;
				break;
			}
		}
	}else
		cout << "表达式有错误" << endl;
	return 1;
}

//对后缀表达式进行求值
double calculate(string exp){
	stack<double> number;
	double digit;
	string str = "";
	for (int i = 0; i<int(exp.length()); i++){
		if (isdigit(exp[i]) || exp[i] == '.'){
			str = str + exp[i];
		}else if (exp[i] == ' '){
			const char* p = str.c_str();
			digit = atof(p);//string转换为double
			number.push(digit);
			str = "";
		}else{//(exp[i]!='.'&&exp[i]!=' '&&!isdigit(exp[i])&&number.size()>=2)
			double result;
			double right;
			double left;
			right = number.top();
			number.pop();
			left = number.top();
			number.pop();
			switch (exp[i]){
			case '+':result = left + right; number.push(result); break;
			case '-':result = left - right; number.push(result); break;
			case '*':result = left * right; number.push(result); break;
			case '/':result = left / right; number.push(result); break;
			case '%': {int(result) = int(left) % int(right); number.push(result); break; }
			case '^':result = pow(left, right); number.push(result); break;
			}
		}
	}
	double finalresult = number.top();
	number.pop();
	return finalresult;
}

void main(){
	while (1){
		cout << "/*******************表达式求值*******************/" << endl;
		cout << "/**********支持 + - * / % ^ ()等运算符***********/" << endl << endl;
		string str;
		cout <<endl<< "请输入表达式：" ;
		cin >> str;
		string exp;
		int a = examine(str);
		if (a == 2){
			exp = transform(str);
			cout << str << "=" << calculate(exp) << endl;
		}
		cout << "继续运算请输入y，否则退出:" ;
		char ch;
		cin >> ch;
		if (ch != 'Y' && ch != 'y')   break;
		system("cls");
	}
	system("pause");
}
