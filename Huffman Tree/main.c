#define  _CRT_SECURE_NO_WARNINGS 1

#include "Huffman.h"

//测试哈夫曼树初始化，销毁
void test01()
{
	HuffManTree h1;
	InitHuffmanTree(&h1,1);
	DestroyHuffmanTree(&h1);
}


//测试获取各字符及权重
void test02()
{
	char ch[256];
	int weight[256];

	getCharAndWeight(ch, weight,4);
}


//测试文件中打印哈夫曼树表
void test03()
{

	int n = -1;
	printf("请输入字符个数：\n");
	scanf("%d", &n);

	char ch[256];
	int weight[256];

	getCharAndWeight(ch, weight,n);

	HuffManTree h1;
	InitHuffmanTree(&h1, n);

	Create(&h1, n, ch, weight);
	DisplayInFile(&h1);

	DestroyHuffmanTree(&h1);
}

///////////////////////////////////////////////////////////////////////////////







int main()
{
	//test01();//测试哈夫曼树初始化，销毁
	test02();//测试获取各字符及权重
	//test03();//测试文件中打印哈夫曼树表

	/////////////////////////////////////////////////////////////////
	



	return 0;
}

















