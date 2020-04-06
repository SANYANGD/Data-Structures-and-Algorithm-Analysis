#include "huffman.h"


//��ȡtest.txt�ļ���������
void readFile(vector<char>& vector){
	char ch;
	ifstream infile("test.txt", ios::in);
	if (!infile){//���ļ�����ʱ����
		cout << "open error" << endl;
		exit(1);
	}
	while (infile.peek() != EOF){
		infile.get(ch);
		vector.push_back(ch);
	}
	infile.close();
}

//����ĳ���ַ�֮ǰ�Ƿ��Ѿ�����
bool find(const char ch, node node){
	for (int i = 0; i < node.length; i++){
		if (node.word[i] == ch)	return true;
	}
	return false;
}
//����ÿ���ַ���Ȩ��
void nodeCount(node& node, vector<char> vector){
	int m = vector.size(), j = 0;
	char ch;
	for (int i = 0; i < m; i++){
		ch = vector[i];
		if (!find(ch, node)){
			node.word[j] = ch;
			node.num[j] = count(vector.begin(), vector.end(), ch);//������һ�����ַ����������ֵĴ���
			node.length++;
			j++;
		}
	}
}

//ѡ���Ȩ����С�������ڵ�
void selectMinTwo(huffmanTree& huffmantree, int a, int& b, int& c){
	int min1, min2, minweight = 10000;
	for (int i = 1; i <= a; i++){
		if (huffmantree[i].parent == 0){
			if (huffmantree[i].weight < minweight){
				minweight = huffmantree[i].weight;
				min1 = i;
			}
		}
	}
	huffmantree[min1].parent = 1;//��.parent��Ϊ1�����ڲμ�֮�������
	minweight = 10000;
	for (int i = 1; i <= a; i++){
		if (huffmantree[i].parent == 0){
			if (huffmantree[i].weight < minweight){
				minweight = huffmantree[i].weight;
				min2 = i;
			}
		}
	}
	huffmantree[min2].parent = 1;
	b = min1;
	c = min2;
}
//����huffman��
void buildHuffmanTree(huffmanTree& huffmantree, node node, int n){
	if (n <= 1)	return;
	int m = 2 * n - 1;
	huffmantree = new huffmanNode[m + 1];
	for (int i = 1; i <= m; i++){//0��ʾû�����ҽڵ㣬���ڵ�
		huffmantree[i].leftChild = 0;
		huffmantree[i].parent = 0;
		huffmantree[i].rightChild = 0;
	}
	for (int i = 1; i <= n; i++)  huffmantree[i].weight = node.num[i - 1];
	int s1, s2;
	for (int i = n + 1; i <= m; i++){
		selectMinTwo(huffmantree, i - 1, s1, s2);
		huffmantree[s1].parent = i;
		huffmantree[s2].parent = i;
		huffmantree[i].leftChild = s1;
		huffmantree[i].rightChild = s2;
		huffmantree[i].weight = huffmantree[s1].weight + huffmantree[s2].weight;
	}
}

//����huffman������huffman����
void huffmanEncoding(huffmanTree huffmantree, huffmanCode& huffmancode, int n){
	int parent, child, start;
	huffmancode = new char* [n + 1];
	char* cd = new char[n];
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; i++){
		start = n - 1;
		child = i;
		parent = huffmantree[i].parent;
		while (parent != 0){
			start--;
			if (child == huffmantree[parent].leftChild)	cd[start] = '0';//��Ϊ0����Ϊ1
			else	cd[start] = '1';
			child = parent;
			parent = huffmantree[child].parent;
		}
		huffmancode[i] = new char[n - start];
		strcpy(huffmancode[i], &cd[start]);
	}
	delete cd;
}

//����huffman���뽫�ļ������test.huf.temp
void compressionFile(huffmanCode code, vector<char> vector, node node){
	int i, j, k;
	ofstream outfile("test.huf.temp", ios::out);
	if (!outfile){//���ļ�����ʱ����
		cerr << "open error" << endl;
		exit(1);
	}
	for (i = 0; i < vector.size(); i++){
		for (j = 0; j < node.length; j++) {
			if (node.word[j] == vector[i])	break;
		}
		for (k = 0; code[j + 1][k] != '\0'; k++)	
			outfile << code[j + 1][k];
	}
	outfile.close();
	//cout << "ѹ���ɹ�! ѹ����test.huf.temp" << endl;
	Sleep(500);
}
//��test.huf.temp�ļ�ת��Ϊ�������ļ�test.huf
void compressionFileToBin(huffmanCode code, vector<char> vector, node node){
	int i, j, k;
	ifstream infile("test.huf.temp", ios::in);
	ofstream outfile("test.huf", ios::binary);
	if (!outfile){//���ļ�����ʱ����
		cerr << "open error" << endl;
		exit(1);
	}
	if (!infile){//���ļ�����ʱ����
		cerr << "open error" << endl;
		exit(1);
	}
	char a = 0;
	int point = 0;
	for (i = 0; i < vector.size(); i++)	{
		for (j = 0; j < node.length; j++)	{
			if (node.word[j] == vector[i])  break;
		}
		for (k = 0; code[j + 1][k] != '\0'; k++) {
			if (code[j + 1][k] == '0')  a &= ~(1 << (7 - point));
			if (code[j + 1][k] == '1')  a |= (1 << (7 - point));
			point++;
			if (point == 8) {
				outfile.write((char*)& a, sizeof(char));
				point = 0;
				a = 0;
			}
		}
	}
	if (point != 0)  outfile.write((char*)& a, sizeof(char));
	outfile.close();
	cout << "ѹ���ļ��ɹ�! ѹ����test.huf" << endl;
	Sleep(500);
}

//��test.huf��ѹ��test.de.txt
void decompressionFile(map<string, char> huffmanmap, int length) {
	char a[30];
	char ch;
	ofstream outfile("test.de.txt", ios::out);
	ifstream infile("test.huf", ios::binary);
	if (!outfile){//���ļ�����ʱ����
		cerr << "open error" << endl;
		exit(1);
	}
	if (!infile)	{//���ļ�����ʱ����
		cerr << "open error" << endl;
		exit(1);
	}
	char m = 0;
	int point = 7;
	string s = "";
	while (length >= 0){
		if (point == 7){
			infile.read((char*)& m, sizeof(char));
			length -= 8;
		}
		char ch = m;
		ch &= 1 << point;
		if (ch == 0)  s += '0';
		else  s += '1';
		point--;
		if (point < 0)  point = 7;
		while (huffmanmap.count(s) == 0){
			if (point == 7) {
				infile.read((char*)& m, sizeof(char));
				length -= 8;
			}
			char ch = m;
			ch &= 1 << point;
			if (ch == 0)  s += '0';
			else  s += '1';
			point--;
			if (point < 0)  point = 7;
		}
		char t = huffmanmap[s];
		outfile << t;
		s = "";
	}
	cout << "��ѹ�ɹ�����ѹ��test.de.txt" << endl;
}


//��ʼ�����ÿ���ַ��Ľڵ�
void initNode(node& node){
	node.word = new char[256];
	node.num = new int[256];
	if (node.word == NULL || node.num == NULL)	{
		cout << "��������" << endl;
		exit(1);
	}
	node.length = 0;
}

//����huffman������Ϣ���Թ���ѹʱʹ��
void initMap(map<string, char>& huffmanmap, huffmanCode huffmancode, int n, node node, int& codelength){
	ofstream out("test.map",ios::out);
	ofstream outlen("test.len", ios::out);
	for (int i = 1; i <= n; i++)	{
		string str = huffmancode[i];
		huffmanmap.insert(pair<string, char>(str, node.word[i - 1]));
		codelength = str.size() * node.num[i - 1] + codelength;
		out << str<< ' ' << node.word[i - 1] << endl;
	}
	outlen << codelength;
	outlen.close();
	out.close();
}

void getMap(map<string, char>& huffmanmap, int& codelength) {
	string key;
	char value;
	ifstream in("test.map", ios::in);
	ifstream inlen("test.len", ios::in);
	while (!in.eof()) {
		in >> key >> value;
		huffmanmap.insert(pair<string, char>(key, value));
	}
	inlen >> codelength;
	inlen.close();
	in.close();
}
