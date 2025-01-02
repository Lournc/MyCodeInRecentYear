#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

using SElemType = int;
using InfoType = char;   // 存储边或者边额外信息的指针变量类型
using VertexType = char; // 顶点信息
int ve[MAX_VERTEX_NUM];  // 事件最早发生时间
int vl[MAX_VERTEX_NUM];  // 事件最晚发生时间
int visited[MAX_VERTEX_NUM];            // DFS 标记数组
int xs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 标记路径 DFS

// 边表结点
typedef struct ArcNode {
  int adjvex;              // 该边指向的顶点位置
  int weight;              // 权值
  struct ArcNode *nextarc; // 指向下一条边的指针
  InfoType *info;          // 该边相关信息的指针
} ArcNode, *ArcNode1;

// 顶点表结点
typedef struct VNode {
  VertexType data;   // 顶点信息
  int in;            // 入度
  ArcNode *firstarc; // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
  AdjList vertices;   // 存储头结点的数组
  int vexnum, arcnum; // 图的当前顶点数和边数
} ALGraph;

// 栈
typedef struct {
  SElemType *base; // 栈底
  SElemType *top;  // 栈顶
  int stacksize;   // 栈内存
  int size;        // 记录栈中元素数量
} SqStack;

// 判断当前输入的顶点在顶点表中的位置
int LocateVex(ALGraph *G, char v) {
  int i = 0;
  for (; i < G->vexnum; i++) {
    if (G->vertices[i].data == v)
      return i;
  }
  return -1;
}

// 创建图
int CreateGraph(ALGraph *G) {
  int i, j, k, b1;
  char a1, a2, a3; // a2 接收换行符
  ArcNode *p;      // 边表结点
  printf("请输入总顶点数和总边数（例如：9 11）：\n");
  scanf("%d%d", &G->vexnum, &G->arcnum);
  printf("请依次输入顶点信息（例如:A B C......）：\n");
  for (i = 0; i < G->vexnum; i++) {
    getchar();
    scanf("%c", &G->vertices[i].data);
    G->vertices[i].firstarc = NULL; // 初始化指针
    G->vertices[i].in = 0;          // 初始化入度
  }
  printf("请输入边（Vi,Vj）上的顶点序号及权值(例如：A C "
         "10(换行继续输入).....)：\n");
  for (k = 0; k < G->arcnum; k++) {
    getchar();
    scanf("%c%c%c%d", &a1, &a2, &a3, &b1);
    // 顶点是否存在，存在返回顶点所在的数组下标，不存在返回-1
    i = LocateVex(G, a1);
    j = LocateVex(G, a3);
    if (i < 0 || j < 0) {
      printf("该顶点不包含在顶点表\n");
      break;
    }
    p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = j;  // 边头顶点
    p->weight = b1; // 权值赋值
    // 逆向添加 ，i为边尾，即统计边头的为j的顶点
    p->nextarc = G->vertices[i].firstarc; // 该顶点i包含的所有边
    G->vertices[i].firstarc = p;          // 挪到边头的位置
  }
  if (k == G->arcnum)
    return 1;
  else
    return 0;
}

// 计算每个点的入度
void FindInDegree(ALGraph *G) {
  int a;
  ArcNode1 p;
  a = G->vexnum; // 顶点数
  int bs[MAX_VERTEX_NUM];
  for (int i = 0; i < a; i++) {
    bs[i] = 0; // 保存每个结点的入度
  }
  for (int i = 0; i < a; i++) {
    p = G->vertices[i].firstarc;
    while (p != NULL) {
      bs[p->adjvex]++;
      p = p->nextarc;
    }
  }
  for (int i = 0; i < a; i++) // 将入度存入结点中
  {
    G->vertices[i].in = bs[i];
  }
}

// 创建栈
int InitStack(SqStack *s) {
  s->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
  if (!s->base)
    exit(0);
  s->top = s->base;
  s->stacksize = STACK_INIT_SIZE; // 100
  s->size = 0;
  return 1;
}

// 入栈
int Push(SqStack *s, SElemType e) {
  if (s->top - s->base >= s->stacksize) // 栈顶元素比最高位元素多一
  {
    s->base = (SElemType *)realloc(s->base, (s->stacksize + STACK_INIT_SIZE) *
                                                sizeof(SElemType)); // 空间扩大
    if (!s->base)
      exit(0);
    s->top = s->base + s->stacksize;
    s->stacksize += STACKINCREMENT;
  }
  *(s->top++) = e; // 若栈不为空，用 e 返回其值
  s->size++;
  return 1;
}

// 出栈
int Pop(SqStack *s, SElemType *e) {
  if (s->top == s->base)
    return 0;
  *e = *--(s->top);
  s->size--;
  return 1;
}

// 获取栈顶元素
void GetTop(SqStack *s, SElemType *e) {
  if (s->top == s->base)
    return;
  *e = *(s->top - 1);
}

// 判空
int StackEmpty(SqStack *s) {
  if (s->base == s->top) {
    return 1;
  } else {
    return 0;
  }
}

// 拓扑排序
int TopologicalOrder(ALGraph *G, SqStack *T) {
  ArcNode1 p;
  int count, e, k;
  FindInDegree(G); // 求入度
  SqStack S;       // 栈
  InitStack(&S);   // 创建空栈
  for (int j = 0; j < G->vexnum; j++) {
    if (G->vertices[j].in == 0) // 若入度=0，压入s栈中
    {
      Push(&S, j);
    }
  }
  count = 0;                          // 计数器
  for (int i = 0; i < G->vexnum; i++) // 初始化
    ve[i] = 0;                        // 事件最早发生时间初始全为0
  while (!StackEmpty(&S))             // 栈s不为空
  {
    Pop(&S, &e); // 出s栈
    Push(T, e);  // 压入t栈 -->
    count++;     // 记录入度为0的点的个数
    for (p = G->vertices[e].firstarc; p;
         p = p->nextarc) // 遍历邻接表入度为0的这一顶点的邻接点
    {
      k = p->adjvex;
      G->vertices[k].in--;        // 入度-1
      if (G->vertices[k].in == 0) // 若为0，压入栈中
        Push(&S, k);
      if (ve[e] + p->weight > ve[k]) // v[k]的最早发生时间的更新---->取最大
      {
        ve[k] = ve[e] + p->weight;
      }
    }
  }
  if (count < G->vexnum) // 记录入度为0的点的个数，小于n,有回路
    return 0;
  else
    return 1;
}

// 栈元素输出
void PrintPath(ALGraph *G, SqStack *T) {
  for (int i = 0; i < T->size; i++)
    printf("%c ", G->vertices[T->base[i]].data);
}

// DFS查找关键路径
void DFS(ALGraph *G, int v, SqStack *T) {
  int e, i;
  GetTop(T, &e);
  if (xs[e][v] == 1)
    Push(T, v); // 路径e-v是关键路径
  else
    return;
  visited[v] = 2; // 标记访问过
  ArcNode *p;
  for (i = 0, p = G->vertices[v].firstarc; p; p = p->nextarc, i++) {
    if (visited[p->adjvex] == 1)
      DFS(G, p->adjvex, T);
  }
  if (!p && i == 0) // 访问到最后一个顶点时上面循环执行0次
  {
    PrintPath(G, T);
    printf("\n");
  }
  // 路径存储方式还原
  Pop(T, &e);     // 栈存
  visited[e] = 1; // 数组标记
}

// 深度优先遍历以邻接表存储的图
void DFSTraverse(ALGraph *G) {
  ArcNode *p;
  SqStack T;
  InitStack(&T);
  int i;
  for (i = 0; i < G->vexnum; i++) {
    if (visited[i] == 1) {
      Push(&T, i);
      visited[i] = 2; // 该点是关键路径输出标记的点
      break;
    }
  } // 找到起始的第一个点，标记为2
  for (p = G->vertices[i].firstarc; p; p = p->nextarc) {
    if (visited[p->adjvex] == 1) // i点的邻接点是关键点
      DFS(G, p->adjvex, &T);
  }
}

// 关键路径
void Criticalpath(ALGraph *G, SqStack *T) {
  int e, k, dut, ee, el, k1 = 0, x1 = 100, n1 = 0;
  ArcNode1 p;
  if (!TopologicalOrder(G, T)) {
    printf("有向网存在回路！");
    return;
  }
  printf("\n 拓扑序列：");
  for (int i = 0; i < G->vexnum; i++) {
    printf("%c ", G->vertices[i].data);
  }
  printf("\n");
  for (int i = 0; i < G->vexnum; i++)
    for (int j = 0; j < G->vexnum; j++)
      xs[i][j] = 0; // 初始化
  for (int a = 0; a < G->vexnum; a++)
    vl[a] = ve[G->vexnum - 1]; // 初始化为该顶点的最晚发生时间
  while (!StackEmpty(T)) {
    Pop(T, &e); // 逆序弹出拓扑序列
    for (p = G->vertices[e].firstarc; p; p = p->nextarc) {
      k = p->adjvex;
      dut = p->weight;
      if (vl[k] - dut < vl[e])
        vl[e] = vl[k] - dut;
    }
  }
  for (int i = 0; i < G->vexnum; i++) // 初始化
  {
    visited[i] = 0;
  }
  printf("\n 关键活动：");
  for (int j = 0; j < G->vexnum; j++) {
    for (p = G->vertices[j].firstarc; p; p = p->nextarc) {
      k = p->adjvex;
      dut = p->weight;
      ee = ve[j];
      el = vl[k] - dut;
      if (ee == el) {
        visited[j] = 1; // DFS 标记数组
        visited[k] = 1;
        xs[j][k] = 1; // 标记路径
        xs[k][j] = 1;
        printf("\n %c->%c", G->vertices[j].data, G->vertices[k].data);
      }
    }
  }
  printf("\n 花费的时间至少为：%d \n", ve[G->vexnum - 1]);
  printf("\n 关键路径:");
  DFSTraverse(G);
}

int main() {
  ALGraph G; // 图
  SqStack T; // 栈
  // CreateGraph(&G); //创建邻接表
  if (!CreateGraph(&G))
    return 0;
  InitStack(&T);        // 创建栈
  Criticalpath(&G, &T); // 关键路径
  printf("\n");
  system("pause");
  return 0;
}