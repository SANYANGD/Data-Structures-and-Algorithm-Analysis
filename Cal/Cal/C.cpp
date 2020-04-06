#include <iostream>
#include <cmath>//isdigit() ����0~9������ʱ������һ������ֵ�����򷵻���
#include <stack>
#include <string>
using namespace std;

//ת��Ϊ��׺���ʽ
string transform(string str){
	stack<char> ope;
	string exp = "";
	for (int i = 0; i<int(str.size()); i++){
		if (str[i] == '.' || isdigit(str[i])){
			exp += str[i];
		}
		else if (str[i] == '+' || str[i] == '-'){
			if (isdigit(str[i-1])){
				exp += " ";//ÿ�����ֵĺ��涼��һ���ո��������
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
			return "�д���";
		}
	}
	while (!ope.empty()){//��������ʽ����ջ�е�������������
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

//�������ı��ʽ�Ƿ�����
int examine(string str){
	if ((isdigit(str[str.length() - 1]) != 0 || str[str.length() - 1] == ')') && 
		(isdigit(str[0]) != 0 || str[0] == '+' || str[0] == '-' || str[0] == '(')){
		for (int i = 0; i<int(str.length()); i++){
			if (str[i] == '/' || str[i] == '%' || str[i] == '*' || str[i] == '^'){
				if (str[i+1] == '/' || str[i + 1] == '*' || str[i + 1] == '%' || str[i + 1] == ')' || str[i + 1] == '.'){
					cout << "���ʽ�д���" << endl;
					return 1;
					break;
				}
			}else if (str[i] == '+' || str[i] == '-'){
				if (str[i+1] == '/' || str[i+1] == '*' || str[i+1] == '%' || str[i+1] == ')' || str[i+1] == '.' || str[i+1] == '^'){
					cout << "���ʽ�д���" << endl;
					return 1;
					break;
				}
			}else if (isdigit(str[i]) != 0){
				if (str[i+1] == '('){
					cout << "���ʽ�д���" << endl;
					return 1;
					break;
				}
			}else if (isdigit(str[i]) == 0 && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' 
				&& str[i] != '^' && str[i] != '%' && str[i] != '(' && str[i] != ')' && str[i] != '.'){
				cout << "���ʽ�д���" << endl;
				return 1;
				break;
			}else if (str[i] == '.'){
				if (isdigit(str[i+1]) == 0){
					cout << "���ʽ�д���" << endl;
					return 1;
					break;
				}
			}
			while (i == str.length() - 1){
				//cout << "���ʽ��ȷ" << endl;
				return 2;
				break;
			}
		}
	}else
		cout << "���ʽ�д���" << endl;
	return 1;
}

//�Ժ�׺���ʽ������ֵ
double calculate(string exp){
	stack<double> number;
	double digit;
	string str = "";
	for (int i = 0; i<int(exp.length()); i++){
		if (isdigit(exp[i]) || exp[i] == '.'){
			str = str + exp[i];
		}else if (exp[i] == ' '){
			const char* p = str.c_str();
			digit = atof(p);//stringת��Ϊdouble
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
		cout << "/*******************���ʽ��ֵ*******************/" << endl;
		cout << "/**********֧�� + - * / % ^ ()�������***********/" << endl << endl;
		string str;
		cout <<endl<< "��������ʽ��" ;
		cin >> str;
		string exp;
		int a = examine(str);
		if (a == 2){
			exp = transform(str);
			cout << str << "=" << calculate(exp) << endl;
		}
		cout << "��������������y�������˳�:" ;
		char ch;
		cin >> ch;
		if (ch != 'Y' && ch != 'y')   break;
		system("cls");
	}
	system("pause");
}
