#include <iostream>
#include <stdio.h>
#include <cstring>
#include <map> 
#include <bitset>
#include <algorithm>
#include <Windows.h>
#include <fstream>
#include <vector>

using namespace std;

//����huffman�Ľڵ�
typedef struct huffmanNode {
	int weight;
	int parent, leftChild, rightChild;
}huffmanNode, * huffmanTree;

//����ÿ���ַ��Ľڵ�
typedef struct node {
	char* word;
	int* num;
	int length;
}node;

//����huffman����ڵ�
typedef char** huffmanCode;

//��ȡtest.txt�ļ���������
void readFile(vector<char>& vector);

//����ĳ���ַ�֮ǰ�Ƿ��Ѿ�����
bool find(const char ch, node node);
//����ÿ���ַ���Ȩ��
void nodeCount(node& node, vector<char> vector);

//ѡ���Ȩ����С�������ڵ�
void selectMinTwo(huffmanTree& huffmantree, int a, int& b, int& c);
//����huffman��
void buildHuffmanTree(huffmanTree& huffmantree, node node, int n);

//����huffman������huffman����
void huffmanEncoding(huffmanTree huffmantree, huffmanCode& huffmancode, int n);

//����huffman���뽫�ļ������test.huf.temp
void compressionFile(huffmanCode huffmancode, vector<char> vector, node node);
//��test.huf.temp�ļ�ת��Ϊ�������ļ�test.huf
void compressionFileToBin(huffmanCode huffmancode, vector<char> vector, node node);

//��test.huf��ѹ��test.de.txt
void decompressionFile(map<string, char> huffmanmap, int length);

//��ʼ�����ÿ���ַ��Ľڵ�
void initNode(node& tnod);

//����huffman������Ϣ���Թ���ѹʱʹ��
void initMap(map<string, char>& huffmanmap, huffmanCode huffmancode, int n, node node, int& codelength);

void getMap(map<string, char>& huffmanmap, int& codelength);