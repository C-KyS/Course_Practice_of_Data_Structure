#define  _CRT_SECURE_NO_WARNINGS 1

#include"parking.h"

//测试停车场栈初始化
void test01()
{
	parkingLot p1;
	PLInit(&p1);
}


//测试停车场栈入栈
void test02()
{
	parkingLot p1;
	PLInit(&p1);


	carInfo x1;
	strcpy(x1.state, "到达");
	strcpy(x1.ID, "123");
	x1.arrive = 123;

	for (int i = 0; i < 10; i++)
	{
		PLPush(&p1, x1);
	}
	PLPush(&p1, x1);

}


//测试查找
void test03()
{
	parkingLot p1;
	PLInit(&p1);


	carInfo x1;
	strcpy(x1.state, "到达");
	strcpy(x1.ID, "123");
	x1.arrive = 123;

	PLPush(&p1, x1);
	printf("%s\n", getPLTop(&p1).ID);


	carInfo x2;
	strcpy(x2.state, "到达");
	strcpy(x2.ID, "456");
	x2.arrive = 456;

	PLPush(&p1, x2);
	printf("%s\n", getPLTop(&p1).ID);


	printf("%d\n", FindCar(&p1, x2));



	PLDestroy(&p1);
}


//测试perror
void test04()
{
	int a = 0;
	int b = 1;
	if (a == 0)
	{
		perror("a");
		exit(1);
	}

	printf("%d\n", b);
}


//测试车辆离开停车场
void test05()
{
	parkingLot p1;
	PLInit(&p1);
	parkingLot _p1;
	PLInit(&_p1);


	carInfo x1;
	strcpy(x1.state, "到达");
	strcpy(x1.ID, "1");
	x1.arrive = 123;

	carInfo x2;
	strcpy(x2.state, "到达");
	strcpy(x2.ID, "2");
	x2.arrive = 456;

	carInfo x3;
	strcpy(x3.state, "到达");
	strcpy(x3.ID, "3");
	x3.arrive = 456;

	carInfo x4;
	strcpy(x4.state, "到达");
	strcpy(x4.ID, "4");
	x4.arrive = 456;

	carInfo x5;
	strcpy(x5.state, "到达");
	strcpy(x5.ID, "5");
	x5.arrive = 456;

	PLPush(&p1, x1);
	PLPush(&p1, x2);
	PLPush(&p1, x3);
	PLPush(&p1, x4);
	PLPush(&p1, x5);

	for (int i = 0; i < p1.size; i++)
	{
		printf("%s ", p1.arr[i].ID);
	}
	printf("\n");

	while (carCmp(getPLTop(&p1),x3)!=1)
	{
		PLPush(&_p1, getPLTop(&p1));
		PLPop(&p1);
	}
	PLPop(&p1);

	while (!isPLEmpty(&_p1))
	{
		PLPush(&p1, getPLTop(&_p1));
		PLPop(&_p1);
	}


	for (int i = 0; i < p1.size; i++)
	{
		printf("%s ", p1.arr[i].ID);
	}
	printf("\n");
	



	PLDestroy(&p1);
	PLDestroy(&_p1);
}


//测试队列初始化
void test06()
{
	QuRoad q1;
	QRInit(&q1);
}


//测试入队
void test07()
{
	QuRoad q1;
	QRInit(&q1);

	carInfo x1;
	strcpy(x1.state, "到达");
	strcpy(x1.ID, "1");
	x1.arrive = 123;

	carInfo x2;
	strcpy(x2.state, "到达");
	strcpy(x2.ID, "2");
	x2.arrive = 456;

	QRPush(&q1, x1);
	QRPush(&q1, x2);

}


//测试车辆信息拷贝函数
void test08()
{
	carInfo x1;
	strcpy(x1.state, "到达");
	strcpy(x1.ID, "1");
	x1.arrive = 123;

	carInfo tmp;
	carCopy(&tmp, &x1);

	printf("%d\n", carCmp(tmp, x1));
}


//测试入队出队
void test09()
{
	QuRoad q1;
	QRInit(&q1);

	carInfo x1;
	strcpy(x1.state, "到达");
	strcpy(x1.ID, "1");
	x1.arrive = 123;

	carInfo x2;
	strcpy(x2.state, "到达");
	strcpy(x2.ID, "2");
	x2.arrive = 456;

	carInfo x3;
	strcpy(x3.state, "到达");
	strcpy(x3.ID, "3");
	x3.arrive = 456;

	carInfo x4;
	strcpy(x4.state, "到达");
	strcpy(x4.ID, "4");
	x4.arrive = 456;

	carInfo x5;
	strcpy(x5.state, "到达");
	strcpy(x5.ID, "5");
	x5.arrive = 456;

	QRPush(&q1, x1);
	QRPush(&q1, x2);
	QRPush(&q1, x3);
	QRPush(&q1, x4);
	QRPush(&q1, x5);

	QRPrint(&q1);

	QRPop(&q1);
	QRPrint(&q1);

	QRPop(&q1);
	QRPrint(&q1);

	QRPop(&q1);
	QRPrint(&q1);

	QRPop(&q1);
	QRPrint(&q1);

	QRPop(&q1);
	QRPrint(&q1);

	QRPop(&q1);
	QRPrint(&q1);

	QRDestroy(&q1);
}


//测试主菜单函数
void test10()
{
	mainMenu();
}


//测试车辆到达总函数
void test11()
{
	//停车场栈初始化
	parkingLot p;
	PLInit(&p);

	//便道队列初始化
	QuRoad r;
	QRInit(&r);

	carArrive(&p, &r);

	PLDestroy(&p);//停车场栈销毁
	QRDestroy(&r);//便道队列销毁
}


//测试车辆离开总函数
void test12()
{
	//停车场栈初始化
	parkingLot p;
	PLInit(&p);

	//便道队列初始化
	QuRoad r;
	QRInit(&r);

	carArrive(&p, &r);
	printf("\n");
	carLeave(&p, &r);

	PLDestroy(&p);//停车场栈销毁
	QRDestroy(&r);//便道队列销毁
}


///////////////////////////////////////////////////////////////////////////////////////

//显示主菜单界面
void mainMenu()
{
	printf("**********************************************\n");
	printf("请选择车辆状态：\n");
	printf("1.到达                                 2.离开\n");
	printf("3.查看停车场停车情况（左边为栈底，右边为栈顶）\n");
	printf("4.查看便道停车情况（左边为队首，右边为队尾）\n");
	printf("0.退出\n");
	printf("**********************************************\n");
}


//获取操作数，执行相关操作
void operateNum(parkingLot* p, QuRoad* r )
{
	//获取用户输入的操作数
	int inputNum = -1;
	
	do
	{
		mainMenu();//展示主菜单
		scanf("%d", &inputNum);//获取用户输入的操作数

		switch (inputNum)
		{
		case 1://车辆到达
			carArrive(p, r);
			break;

		case 2://车辆离开
			carLeave(p, r);
			break;

		case 3://打印停车场栈
			PLPrint(p);
			break;

		case 4://打印便道队列
			QRPrint(r);
			break;

		case 0:
			break;

		default:
			printf("输入错误，请重新输入。\n");
			break;
		}
	} while (inputNum);
}


void maintest()
{
	//停车场栈初始化
	parkingLot p;
	PLInit(&p);

	//便道队列初始化
	QuRoad r;
	QRInit(&r);

	operateNum(&p, &r);

	PLDestroy(&p);//停车场栈销毁
	QRDestroy(&r);//便道队列销毁
}

int main()
{
	//test01();//测试停车场栈初始化
	//test02();//测试停车场栈入栈
	//test03();//测试查找
	//test04();//测试perror
	//test05();//测试车辆离开停车场
	//test06();//测试队列初始化
	//test07();//测试入队
	//test08();//测试车辆信息拷贝函数
	//test09();//测试入队出队
	//test10();//测试主菜单函数
	//test11();//测试车辆到达总函数
	//test12();//测试车辆离开总函数
	maintest();
	//////////////////////////////////////////////////////////////////////////////////////

	

	return 0;
}











