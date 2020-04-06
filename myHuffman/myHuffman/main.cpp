#include "huffman.h"

int main(){
	fstream f;
	vector<char> str;
	map<string, char> huffmanmap;
	int number = 0; int n = 0; int codelength = 0;
	huffmanTree huffmantree;
	huffmanCode huffmancode;
	node node;
	initNode(node);
	
	while (1){
		cout << "请输入选择的功能：" << endl;
		cout << "1. 压缩文件" << endl;
		cout << "2. 解压文件" << endl;
		cin >> number;
		switch (number){
		case 1:
			readFile(str);
			nodeCount(node, str);
			n = node.length;
			buildHuffmanTree(huffmantree, node, n);
			huffmanEncoding(huffmantree, huffmancode, n);
			compressionFile(huffmancode, str, node);
			compressionFileToBin(huffmancode, str, node);
			initMap(huffmanmap, huffmancode, n, node, codelength);
			system("pause");
			break;
		case 2:
			getMap(huffmanmap, codelength);
			decompressionFile(huffmanmap, codelength);
			system("pause");
			break;
		default:
			cout << "输入错误！请重新输入";
			system("pause");
			break;
		}
		system("cls");
	}
	return 0;
}