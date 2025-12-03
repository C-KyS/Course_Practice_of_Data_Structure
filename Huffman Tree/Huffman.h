#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000


//////////////////////////////////////////////////哈夫曼树建立//////////////////////////////////////////////////

//哈夫曼树节点结构体
typedef struct HTNode
{
	char ch;//节点字符
	int weight;//节点字符权重
	int parent;//节点父节点下标
	int lchild;//节点左孩子下标
	int Rchild;//节点右孩子下标
}HTNode;

//哈夫曼树结构体
typedef struct HuffmanTree
{
	HTNode* ht;//节点数组首元素地址
	int htsize;//树中总节点个数
}HuffManTree;


void getCharAndWeight(char* ch, int* weight,int n);//获取字符个数、各字符及各字符权值（字符数组地址，权重数组地址）

void InitHuffmanTree(HuffManTree* pHT, int n);//哈夫曼树初始化（新建哈夫曼树结构体地址，字符个数）
void DestroyHuffmanTree(HuffManTree* pHT);//哈夫曼树销毁（哈夫曼树结构体地址）

int MinVal(HuffManTree* pHT, int i);//在给定的哈夫曼树的字符表中，选择前i个节点中权重最小的字符，返回该字符的下标//（哈夫曼树地址，节点范围i）
void Select(HuffManTree* pHT, int i, int* ps1, int* ps2);//获取两个哈夫曼树中权值最小的两个节点（哈夫曼树地址，前i个字符表，待修改值s1，s2地址（设定s1<s2））
void Create(HuffManTree* pHT, int n, char* ch, int* weight);//哈夫曼树根据各字符、字符权重建树（哈夫曼树地址，字符个数，字符数组，权重数组）
void DisplayInFile(HuffManTree* pHT);//在指定文件hfmTree.txt中显示哈夫曼树，打印包含最终各节点父子关系、权重等信息的表格


/////////////////////////////////////////////字符编码///////////////////////////////////////////

//字符结构体
typedef struct HCNode
{
	char ch;//字符
	char* pstring;//字符编码结果
}HCNode;

//编码表结构体
typedef struct HuffmanCoder
{
	HCNode* hc;//字符结构体数组首元素地址
	int hcsize;//树叶节点个数
}HuffmanCoder;


void InitHuffmanCoder(HuffmanCoder* pHC, int n);//编码表初始化，直接将数组初始化，大小为n
void DestroyHuffmanCoder(HuffmanCoder* pHC);//编码表销毁






