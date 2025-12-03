#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATE 20//车辆状态字符串长度，“到达”或“离去
#define MAX_ID 20//车牌照号码字符串长度
#define MAX_PARKING 5//设置停车场最大容量
#define PRICE 10//设置停车场每小时单价


//车辆信息结构体
typedef struct carInfo {
	char state[MAX_STATE];//车辆状态
	char ID[MAX_ID];//车牌照号码
	time_t arrive;//车辆到达时间
	time_t leave;//车辆离开时间
}carInfo;




typedef carInfo PLDateType;//将车辆信息结构体定义为项目数据元素


//停车场栈的结构体,顺序存储
typedef struct parkingLot {
	PLDateType* arr;//顺序表首元素地址
	int size;//顺序表长度
	int capacity;//顺序表容量，由宏定义
}parkingLot;


bool carCmp(carInfo c1, carInfo c2);//比较两车辆信息结构体是否相同
void carCopy(carInfo* p1, carInfo* p2);//拷贝车辆信息，将c2信息拷贝至c1
void CNPrint(PLDateType x);//打印车辆信息结构体


void PLInit(parkingLot* ppl);//停车场栈初始化
void PLDestroy(parkingLot* ppl);//停车场栈的销毁
void PLPrint(parkingLot* ppl);//停车场栈的打印

bool isPLFull(parkingLot* ppl);//检测停车场栈是否已满
bool isPLEmpty(parkingLot* ppl);//检测停车场栈是否已空

void PLPush(parkingLot* ppl, carInfo x);//入栈，车辆停入停车场

void PLPop(parkingLot* ppl);//停车场栈顶车辆出栈

PLDateType getPLTop(parkingLot* ppl);//获取停车场栈栈顶元素

int FindCar(parkingLot* ppl, carInfo targetCar);//查找停车场栈中的特定车辆，返回该车辆的索引下标，若查找不到则返回-1


//便道车辆节点结构体
typedef struct roadCarNode {
	PLDateType val;//节点数据，即车辆信息carInfo
	struct roadCarNode* next;//下一节点地址
}carNode;


//便道队列结构体
typedef struct QueueRoad {
	carNode* head;//队首地址
	carNode* tail;//队尾地址
	int size;//队列长度
}QuRoad;


void QRInit(QuRoad* pq);//便道队列初始化
void QRDestroy(QuRoad* pq);//便道队列销毁
void QRPrint(QuRoad* pq);//便道队列打印

carNode* CNBuyNode(PLDateType x);//创建新车辆信息节点，返回节点地址

void QRPush(QuRoad* pq, PLDateType x);//新车辆节点入队
PLDateType QRPop(QuRoad* pq);//队列队首元素出队 ，返回出队节点

void mainMenu();

void getArriveCarInfo(carInfo* x);//获取输入的到达车辆信息，将相关信息记录在传入结构体上
void carArrive(parkingLot* p, QuRoad* r);//车辆到达总函数



void getLeaveCarInfo(carInfo* x);//获取输入的离开车辆信息，将相关信息记录在传入结构体上
int FindCarInParkingLot(parkingLot* ppl, char* targetCarID);//查找停车场栈中的特定车辆，返回该车辆的索引下标，若查找不到则返回-1
carNode* FindCarInQuRoad(QuRoad* pr, carInfo targetCar);//查找便道队列中的特定车辆，返回该车辆节点的地址，若查找不到则返回NULL
void carLeave(parkingLot* ppl, QuRoad* pqr);//车辆离开总函数












