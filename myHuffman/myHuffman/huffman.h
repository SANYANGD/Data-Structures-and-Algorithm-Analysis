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

//定义huffman的节点
typedef struct huffmanNode {
	int weight;
	int parent, leftChild, rightChild;
}huffmanNode, * huffmanTree;

//定义每种字符的节点
typedef struct node {
	char* word;
	int* num;
	int length;
}node;

//定义huffman编码节点
typedef char** huffmanCode;

//读取test.txt文件到容器中
void readFile(vector<char>& vector);

//查找某个字符之前是否已经存在
bool find(const char ch, node node);
//计算每种字符的权重
void nodeCount(node& node, vector<char> vector);

//选择出权重最小的两个节点
void selectMinTwo(huffmanTree& huffmantree, int a, int& b, int& c);
//创建huffman树
void buildHuffmanTree(huffmanTree& huffmantree, node node, int n);

//根据huffman树创建huffman编码
void huffmanEncoding(huffmanTree huffmantree, huffmanCode& huffmancode, int n);

//根据huffman编码将文件编码成test.huf.temp
void compressionFile(huffmanCode huffmancode, vector<char> vector, node node);
//将test.huf.temp文件转换为二进制文件test.huf
void compressionFileToBin(huffmanCode huffmancode, vector<char> vector, node node);

//将test.huf解压至test.de.txt
void decompressionFile(map<string, char> huffmanmap, int length);

//初始化存放每种字符的节点
void initNode(node& tnod);

//保存huffman编码信息，以供解压时使用
void initMap(map<string, char>& huffmanmap, huffmanCode huffmancode, int n, node node, int& codelength);

void getMap(map<string, char>& huffmanmap, int& codelength);