#define  _CRT_SECURE_NO_WARNINGS 1

#include "Huffman.h"

//////////////////////////////////////////////////哈夫曼树建立//////////////////////////////////

//获取字符个数、各字符及各字符权值（字符数组地址，权重数组地址，总字符个数）
void getCharAndWeight(char* ch , int* weight,int n)
{
	////获取字符个数
	//int n = -1;
	//printf("请输入字符个数：\n");
	//scanf("%d", &n);

	//获取n个字符及权重，并将其存放至相应数组中
	for (int i = 0; i < n; i++)
	{
		
		int inputStatus;

		printf("请输入第%d个字符：\n", i + 1);
		while (1) {
			inputStatus = scanf("%c", ch + i);
			// 清除缓冲区中的多余字符
			while (getchar() != '\n');

			if (inputStatus == 1) {
				// 成功读取一个字符
				break;
			}
			else {
				// 输入错误，提示用户重新输入
				printf("输入错误，请只输入一个字符：\n");
			}
		}


		/*printf("请输入第%d个字符：\n",i+1);
		scanf("\n%c", ch +i);*/

		int input = -1;
		printf("请输入该字符的权重：\n");
		scanf("%d", &input);
		while (input<=0)
		{
			printf("权值需大于0，请重新输入：\n");
			scanf("%d", &input);
		}
		weight[i] = input;
		
	}
}


//哈夫曼树初始化（新建哈夫曼树结构体地址，字符个数）
void InitHuffmanTree(HuffManTree* pHT, int n)
{
	HTNode* pnew = (HTNode*)malloc(sizeof(HTNode) * (2 * n - 1));
	if (pnew == NULL)
	{
		perror("malloc fail");
		exit(1);
	}

	pHT->ht = pnew;
	pHT->htsize = 2 * n - 1;//哈夫曼树中总节点数与叶子节点（编码字符）数的关系
}


//哈夫曼树销毁（哈夫曼树结构体地址）
void DestroyHuffmanTree(HuffManTree* pHT)
{
	free(pHT->ht);
	pHT->ht = NULL;

	pHT->htsize = 0;
}


//在给定的哈夫曼树的字符表中，选择前i个节点中权重最小的字符，返回该字符的下标
//（哈夫曼树地址，节点范围i）
int MinVal(HuffManTree* pHT, int i)
{
	int k = -1;//最小值索引初始化
	int min = MAX;//最小值初始化

	for (int j = 0; j < i; j++)
	{
		//保证节点未被使用 && 权重小于最小值
		if (pHT->ht[j].parent == -1 && pHT->ht[j].weight < min)
		{
			min = pHT->ht[j].weight;
			k = j;
		}
	}

	//将最终选择到的最小节点的parent置为非-1,防止之后被多次选择
	pHT->ht[k].parent = MAX;
	return k;
}


//获取两个哈夫曼树中权值最小的两个节点（哈夫曼树地址，前i个字符表，待修改值s1，s2地址（设定s1<s2））
void Select(HuffManTree* pHT, int i, int* ps1,int* ps2)
{
	*ps1 = MinVal(pHT, i);
	*ps2 = MinVal(pHT, i);

	//假设法，将s1设为权重更小的节点下标
	if (*ps1 > *ps2)
	{
		int tmp = *ps1;
		*ps1 = *ps2;
		*ps2 = tmp;
	}
}


//哈夫曼树根据各字符、字符权重建树（哈夫曼树地址，字符个数，字符数组，权重数组）
void Create(HuffManTree* pHT, int n, char* ch, int* weight)
{

	//检测n是否大于1，若小于等于1则不需要建树
	if (n > 1)
	{
		//初始化字符表
		for (int i = 0; i < n; i++)
		{
			pHT->ht[i].ch = ch[i];
			//strcpy(pHT->ht[i].ch, ch[i]);
			pHT->ht[i].weight = weight[i];
			pHT->ht[i].parent = -1;
			pHT->ht[i].lchild = -1;
			pHT->ht[i].Rchild = -1;
		}

		//在字符表中选择权重最小的两个节点，合成新节点
		int s1 = -1, s2 = -1;

		for (int i = n; i < pHT->htsize; i++)
		{
			Select(pHT, i, &s1, &s2);//按函数设定，s1,s2为前n个字符表中权重最小的两节点下标，且s1<s2

			//填写s1,s2节点的父亲节点信息
			pHT->ht[s1].parent = pHT->ht[s2].parent = i;
			
			//填写当前下标为i的空位置，该节点为s1,s2的父节点
			pHT->ht[i].lchild = s1;
			pHT->ht[i].Rchild = s2;
			pHT->ht[i].weight = pHT->ht[s1].weight + pHT->ht[s2].weight;
			pHT->ht[i].parent = -1;
			pHT->ht[i].ch = 'N';//非叶子节点均无字符
		}

		printf("哈夫曼树建立完毕\n");
	}
	
}


//在指定文件hfmTree.txt中显示哈夫曼树，打印包含最终各节点父子关系、权重等信息的表格
//（哈夫曼树地址）
void DisplayInFile(HuffManTree* pHT )
{
	//打开文件
	FILE* pFile = fopen("hfmTree.txt", "w");

	//将相关信息写入文件
	fprintf(pFile,"所建立的哈夫曼树表如下：\n");
	fprintf(pFile, "下标位置   字符   权值   左孩子   右孩子   双亲\n");

	for (int i = 0; i < pHT->htsize; i++)
	{
		fprintf(pFile, "%10d %10c %10d %10d %10d %10d\n",
			i,
			pHT->ht[i].ch,
			pHT->ht[i].weight,
			pHT->ht[i].lchild,
			pHT->ht[i].Rchild,
			pHT->ht[i].parent);
	}
	fprintf(pFile, "\n");

	//关闭文件
	fclose(pFile);
}


/////////////////////////////////////////////字符编码///////////////////////////////////////////
//编码表初始化，直接将数组初始化，大小为n
void InitHuffmanCoder(HuffmanCoder* pHC,int n)
{
	HCNode* pnew = (HCNode*)malloc(sizeof(HCNode) * n);
	if (pnew == NULL)
	{
		perror("HuffmanCoder malloc fail");
		exit(1);
	}
	pHC->hc = pnew;

	pHC->hcsize = n;
}


//编码表销毁
void DestroyHuffmanCoder(HuffmanCoder* pHC)
{
	for (int i = 0; i < pHC->hcsize; i++)
	{
		free(pHC->hc[i].pstring);
		pHC->hc[i].pstring = NULL;
	}

	free(pHC->hc);
	pHC->hc = NULL;
}


//建立哈夫曼编码表
void CreateBook(HuffmanCoder* pHC, HuffManTree* pHT)
{
	//创建临时字符串存放，用于存放编码结果
	char* cd;
	char* pnew = (char*)malloc(pHC->hcsize * sizeof(char));
	if (pnew == NULL)
	{
		perror("char* cd malloc fail");
		exit(1);
	}
	cd = pnew;
	cd[pHC->hcsize - 1] = '\0';

	//遍历编码表
	for (int i = 0; i < pHC->hcsize; i++)
	{
		int start = pHC->hcsize - 1;//cd编码结果逆序存放起始下标

		//将字符值由哈夫曼树复制到编码表
		pHC->hc[i].ch = pHT->ht[i].ch;

		//逆序编码
		int c, f;
		for (c = i, f = pHT->ht[i].parent; f != -1; c = f, f = pHT->ht[f].parent)
		{
			if (pHT->ht[f].lchild == c)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}

	}

	
	
	


	//将临时字符串中编码记入编码表，并输出至终端


}





















