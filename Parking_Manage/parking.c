#define  _CRT_SECURE_NO_WARNINGS 1

#include "parking.h"

//比较两车辆信息结构体是否相同
bool carCmp(carInfo c1, carInfo c2)
{
	return strcmp(c1.ID, c2.ID) == 0;
}


//拷贝车辆信息，将c2信息拷贝至c1
void carCopy(carInfo* p1, carInfo* p2)
{
	strcpy(p1->state, p2->state);
	strcpy(p1->ID, p2->ID);
	p1->arrive = p2->arrive;
	p1->leave = p2->leave;
}


//打印车辆信息结构体
void CNPrint(PLDateType x)
{
	printf("%s %s %lld %lld\n",
		x.state,
		x.ID,
		x.arrive,
		x.leave);
}


//停车场栈初始化
void PLInit(parkingLot* ppl)
{
	carInfo* pnew = (carInfo*)malloc(sizeof(carInfo) * MAX_PARKING);
	if (pnew == NULL)
	{
		perror("malloc fail");
		return;
	}

	ppl->arr = pnew;
	ppl->size = 0;
	ppl->capacity = MAX_PARKING;//容量宏定义，默认为10
}


//停车场栈的销毁
void PLDestroy(parkingLot* ppl)
{
	assert(ppl);

	free(ppl->arr);
	ppl->arr = NULL;

	ppl->size = 0;
	ppl->capacity = 0;
}


//停车场栈的打印
void PLPrint(parkingLot* ppl)
{
	assert(ppl);

	for (int i = 0; i < ppl->size; i++)
	{
		CNPrint(ppl->arr[i]);
	}
	printf("\n");
}


//检测停车场栈是否已满
bool isPLFull(parkingLot* ppl)
{
	assert(ppl);

	return ppl->size == ppl->capacity;
}


//检测停车场栈是否已空
bool isPLEmpty(parkingLot* ppl)
{
	assert(ppl);

	return ppl->size == 0;
}


//入栈，新车辆停入停车场
void PLPush(parkingLot* ppl,carInfo x)
{
	assert(ppl);

	//检测停车场是否已满
	if (isPLFull(ppl))
	{
		printf("停车场已满，请停入便道等待\n");
		return;
	}

	//若停车场栈未满，则车辆入栈
	ppl->arr[ppl->size] = x;
	ppl->size++;
}


//停车场栈顶车辆出栈
void PLPop(parkingLot* ppl) 
{
	assert(ppl);

	//检测停车场栈是否已经为空
	if (isPLEmpty(ppl))
	{
		printf("停车场已空，无法进行出栈操作\n");
		return ;
	}

	ppl->size--;
}


//获取停车场栈栈顶元素
PLDateType getPLTop(parkingLot* ppl)
{
	assert(ppl);

	//assert(ppl->size > 0);
	if (ppl->size == 0)
	{
		printf("栈已空，无法获取栈顶元素\n");
		exit(-1);
	}

	return ppl->arr[ppl->size-1];
}


//查找停车场栈中的特定车辆，返回该车辆的索引下标，若查找不到则返回-1
int FindCar(parkingLot* ppl, carInfo targetCar)
{
	assert(ppl);

	for (int i = 0; i < ppl->size; i++)
	{
		if (carCmp(ppl->arr[i], targetCar))
		{
			return i;
		}
	}

	return -1;
}


//便道队列初始化
void QRInit(QuRoad* pq)
{
	assert(pq);

	pq->head = NULL;
	pq->tail = NULL;
	pq->size = 0;
}


//便道队列销毁
void QRDestroy(QuRoad* pq) 
{
	assert(pq);

	carNode* pcur = pq->head;
	while (pcur)
	{
		carNode* pnext = pcur->next;
		free(pcur);
		pcur = pnext;
	}

	pq->head = pq->tail = NULL;
	pq->size = 0;
}


//便道队列打印
void QRPrint(QuRoad* pq)
{
	carNode* pcur = pq->head;
	while (pcur)
	{
		CNPrint(pcur->val);
		pcur = pcur->next;
	}
	printf("\n");
}


//创建新车辆信息节点，返回节点地址
carNode* CNBuyNode(PLDateType x)
{
	carNode* pnew = (carNode*)malloc(sizeof(carNode));
	if (pnew == NULL)
	{
		perror("malloc fail");
		exit(1);
	}

	strcpy(pnew->val.state, x.state);
	strcpy(pnew->val.ID, x.ID);
	pnew->val.arrive = x.arrive;
	pnew->val.leave = x.leave;
	
	pnew->next = NULL;

	return pnew;
}



//新车辆节点由队尾入队
void QRPush(QuRoad* pq, PLDateType x)
{
	assert(pq);

	//创建新节点，获取新节点地址
	carNode* pnew = CNBuyNode(x);

	//判断原队列是否为空
	if (pq->size == 0)
	{
		pq->head = pnew;
		pq->tail = pnew;
	}
	else
	{
		pq->tail->next = pnew;
		pq->tail = pnew;
	}

	pq->size++;
}


//队列队首元素出队 ，返回出队节点
PLDateType QRPop(QuRoad* pq)
{
	//检测队列是否已空
	if (pq->size == 0)
	{
		
		perror("QuRoad empty");
		exit(1);
	}

	PLDateType ret;

	//检测队列是否只有一个节点
	if (pq->size == 1)
	{
		carCopy(&ret, &(pq->head->val));

		free(pq->head);
		pq->head = NULL;
		pq->tail = NULL;
	}
	else
	{
		carNode* tmp = pq->head->next;
		carCopy(&ret, &(tmp->val));

		free(pq->head);
		pq->head = tmp;
	}
	
	pq->size--;
	return ret;
}


//获取输入的到达车辆信息，将相关信息记录在传入结构体上
void getArriveCarInfo(carInfo* x)
{
	strcpy(x->state, "到达");

	//获取车牌号码
	printf("请输入车牌号码：\n");
	scanf("%s", x->ID);
	
	//获取到达时间
	x->arrive = time(NULL);
}


//车辆到达总函数
void carArrive(parkingLot* p, QuRoad* r)
{
	//获取输入的到达车辆信息
	carInfo tmp;
	getArriveCarInfo(&tmp);

	//尝试能否停入停车场
	//若停车场未满，则停入停车场
	if (!isPLFull(p))
	{
		printf("停车场还有余位！\n");

		PLPush(p, tmp);
		printf("成功停入停车场！\n");
		printf("\n");
	}
	else//若无法停入停车场，则停入便道
	{
		printf("停车场已满，需停放至便道！\n");
		
		QRPush(r, tmp);
		printf("成功停入便道！\n");
		printf("\n");
	}
}


//获取输入的离开车辆信息，将相关信息记录在传入结构体上
void getLeaveCarInfo(carInfo* x)
{
	strcpy(x->state, "离开");

	//获取车牌号码
	printf("请输入车牌号码：\n");
	scanf("%s", x->ID);

	//获取离开时间
	x->leave = time(NULL);
}



//查找停车场栈中的特定车辆，返回该车辆的索引下标，若查找不到则返回-1
int FindCarInParkingLot(parkingLot* ppl, char* targetCarID)
{
	assert(ppl);

	for (int i = 0; i < ppl->size; i++)
	{
		if (strcmp(ppl->arr[i].ID, targetCarID)==0)
		{
			return i;
		}
	}

	return -1;
}


//查找便道队列中的特定车辆，返回该车辆节点的地址，若查找不到则返回NULL
carNode* FindCarInQuRoad(QuRoad* pr , carInfo targetCar)
{
	carNode* pcur = pr->head;
	while (pcur)
	{
		if (strcmp(pcur->val.ID, targetCar.ID) == 0)
		{
			return pcur;
		}

		pcur = pcur->next;
	}

	return NULL;
}


//车辆离开总函数
void carLeave(parkingLot* ppl, QuRoad* pqr)
{
	//获取离开车辆信息
	char inputID[MAX_ID];

	printf("请输入车牌号码：\n");
	scanf("%s", inputID);

	//查找停车场栈中是否有该辆车
	if (FindCarInParkingLot(ppl, inputID)==-1)
	{
		printf("停车场中无该车辆，请重新输入。\n");
		return;
	}
	else
	{
		//构建辅助栈，将目标车辆前面的车辆先出栈，进入辅助栈。最后再从辅助栈出栈，进入原停车场栈
		parkingLot _p;
		PLInit(&_p);//辅助栈初始化

		//前面的车辆先出栈，进入辅助栈
		while (strcmp(getPLTop(ppl).ID,inputID)!=0)
		{
			PLPush(&_p, getPLTop(ppl));
			PLPop(ppl);
		}

		//打印相关信息
		PLDateType x = getPLTop(ppl);
		x.leave = time(NULL);
		int costHour = (int)(x.leave - x.arrive)/3600+1;
		int costMoney = costHour * PRICE;
		printf("车牌号：%s\n", inputID);
		printf("停车时长：%d小时\n", costHour);
		printf("收费：%d\n", costMoney);
		printf("\n");
		//目标车辆出栈
		PLPop(ppl);

		//前面车辆返回
		while (!isPLEmpty(&_p))
		{
			PLPush(ppl, getPLTop(&_p));
			PLPop(&_p);
		}

		PLDestroy(&_p);//辅助栈销毁


		//若此时队列非空，则队首元素可进入停车场栈
		if (pqr->size != 0)
		{
			//记录队首车辆入栈时间
			pqr->head->val.arrive = time(NULL);

			//队首元素入栈
			PLPush(ppl, pqr->head->val);

			//队首元素出队
			QRPop(pqr);
		}
	}
}



















