#define  _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 10 // 最大景点数量
#define INF INT_MAX // 无穷大表示不可达

// 景点结构体
typedef struct {
    char name[50]; // 景点名称
    char code[10]; // 景点代号
    char description[200]; // 景点简介
} Spot;

// 邻接矩阵表示图
int graph[MAX_VERTICES][MAX_VERTICES];
Spot spots[MAX_VERTICES];
int numSpots = 0;




// 添加景点函数
void addSpot(const char* name, const char* code, const char* description) {
    strcpy(spots[numSpots].name, name);
    strcpy(spots[numSpots].code, code);
    strcpy(spots[numSpots].description, description);
    numSpots++;
}

// 添加路径函数
void addPath(int from, int to, int length) {
    graph[from][to] = length;
    graph[to][from] = length; // 假设路径是双向的
}

// 显示景点信息函数
void displaySpotInfo(int index) {
    printf("\n景点名称: %s\n", spots[index].name);
    printf("代号: %s\n", spots[index].code);
    printf("简介: %s\n", spots[index].description);
}

// 查找最短路径函数（Dijkstra算法）
void findShortestPath(int start, int end) {
    int dist[MAX_VERTICES]; // 存储start点到各个顶点的最短距离
    int visited[MAX_VERTICES] = { 0 }; // 标记已访问的顶点
    int prev[MAX_VERTICES]; // 存储前驱节点

    for (int i = 0; i < numSpots; i++) {
        dist[i] = INF; // 初始化距离为无穷大
        prev[i] = -1; // 初始化前驱为-1（无前驱）
    }

    dist[start] = 0; // 起始节点到自身距离为0

    for (int count = 0; count < numSpots - 1; count++) {
        int minDist = INF;
        int minIndex;

        /*找到最近的未访问点*/
        for (int v = 0; v < numSpots; v++) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        visited[minIndex] = 1;

        /*对于每个未访问的顶点v，如果通过minIndex顶点到达v的距离比当前记录的距离更短，则更新*/
        for (int v = 0; v < numSpots; v++) {
            if (!visited[v] && graph[minIndex][v] && dist[minIndex] != INF &&
                dist[minIndex] + graph[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + graph[minIndex][v];
                prev[v] = minIndex;
            }
        }
    }

    // 输出最短路径和距离
    if (dist[end] == INF) {
        printf("从%s到%s没有可达路径。\n", spots[start].name, spots[end].name);
        return;
    }

    printf("\n从%s到%s的最短路径长度为:%d\n路径为:", spots[start].name, spots[end].name, dist[end]);

    int path[MAX_VERTICES];
    int pathLength = 0;

    for (int v = end; v != -1; v = prev[v]) {
        path[pathLength++] = v;
    }

    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%s%s", spots[path[i]].name,spots[path[i]].code);
        //if (i > 0) printf("-> ");
        if (i > 0) printf(" ->(%d) ", graph[path[i]][path[i - 1]]);

    }

    printf("\n");
}

int main() {
    // 添加景点信息
    addSpot("图书馆", "A", "校园内最大的图书馆，藏书丰富。");
    addSpot("体育馆", "B", "供学生进行各种体育活动的场所。");
    addSpot("实验楼", "C", "进行科学实验的教学楼。");
    addSpot("教学楼", "D", "主要用于课堂教学的建筑。");
    addSpot("食堂", "E", "提供多种美食的餐饮场所。");
    addSpot("宿舍楼", "F", "学生住宿的地方。");
    addSpot("操场", "G", "供学生课外活动和锻炼的场地。");
    addSpot("艺术中心", "H", "进行艺术学习和展览的场所。");
    addSpot("会议中心", "I", "举办各类会议和活动的地方。");
    addSpot("学生活动中心", "J", "供学生休闲和聚会的开放空间。");

    // 添加路径信息
    addPath(0, 1, 200); // 图书馆 -> 体育馆
    addPath(0, 2, 300); // 图书馆 -> 实验楼
    addPath(0, 9, 200); // 图书馆 -> 学生活动中心
    addPath(1, 3, 150); // 体育馆 -> 教学楼
    addPath(2, 3, 100); // 实验楼 -> 教学楼
    addPath(3, 4, 250); // 教学楼 -> 食堂
    addPath(4, 5, 100); // 食堂 -> 宿舍楼
    addPath(5, 6, 300); // 宿舍楼 -> 操场
    addPath(5, 8, 500); // 宿舍楼 -> 会议中心
    addPath(6, 7, 200); // 操场 -> 艺术中心
    addPath(7, 8, 400); // 艺术中心 -> 会议中心
    addPath(8, 9, 150); // 会议中心 -> 学生活动中心

    printf("--所有景点信息已加载完成--");

    int choice=3;

    system("start D:\\CYH\\A75D23CACFA5561D718A4BAE68F2A582.png");

    while (1) {
        printf("\n欢迎使用校园导游程序!\n");
        printf("1. 查询景点信息\n");
        printf("2. 查询最短路径\n");
        printf("3. 退出\n");
        printf("请选择操作：");
        scanf("%d", &choice);

        if (choice == 1) {
            char code[10];
            printf("请输入景点代号：");
            scanf("%s", code);
            int isFound = -1;
            for (int i = 0; i < numSpots; i++) {
                if (strcmp(spots[i].code, code) == 0) {
                    isFound = i;
                    break;
                }
            }
            if (isFound != -1)
            {
                displaySpotInfo(isFound);
            }
            else {
                printf("未找到代号为 %s 的景点。", code);
            }
        }
        else if (choice == 2) {
            char startCode[10], endCode[10];
            printf("请输入起始景点代号：");
            scanf("%s", startCode);
            printf("请输入终止景点代号：");
            scanf("%s", endCode);
            int startIndex = -1;
            int endIndex = -1;
            for (int i = 0; i < numSpots; i++) {
                if (strcmp(spots[i].code, startCode) == 0) {
                    startIndex = i;
                }
                if (strcmp(spots[i].code, endCode) == 0) {
                    endIndex = i;
                }
            }
            if (startIndex != -1 && endIndex != -1) {
                findShortestPath(startIndex, endIndex);
            }
            else {
                printf("不存在最短路径/无效的景点代号！\n");
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            printf("无效选择，请重试。\n");
        }
    }

    return 0;
}