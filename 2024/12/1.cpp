#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESS_NUM 10
#define MAX_RESOURCE_NUM 10
#define NAMESIZE 20

// 银行家算法的结构体设计
typedef struct BankAlgorithm {
  char **process_name;  // 进程名称
  char **resource_name; // 资源名称
  int **max;            // 每个进程对资源的最大需求
  int **allocation;     // 每个进程已经分配的资源数
  int **need;           // 每个进程还需要的资源数
  int *total_resources; // 每种资源的总数
  int *available;       // 每种资源当前可用的数量
  int process_num;      // 当前进程数
  int resource_num;     // 当前资源种类数
} BankAlgorithm;

// 初始化函数，动态分配空间
BankAlgorithm *Init_BankAlgorithm() {
  BankAlgorithm *pba = (BankAlgorithm *)malloc(sizeof(BankAlgorithm));
  if (!pba)
    exit(EXIT_FAILURE);

  pba->process_name = NULL;
  pba->resource_name = NULL;
  pba->max = NULL;
  pba->allocation = NULL;
  pba->need = NULL;
  pba->total_resources = NULL;
  pba->available = NULL;

  pba->process_num = 0;
  pba->resource_num = 0;

  return pba;
}

// 打印资源分配信息
void Show(BankAlgorithm *pba) {
  if (pba->process_num == 0 || pba->resource_num == 0) {
    printf("数据未初始化！\n");
    return;
  }

  printf("\n当前资源分配状态:\n");
  printf("进程名   | MAX               | Allocation       | Need             | "
         "Available\n");
  printf("---------+--------------------+------------------+------------------+"
         "------------------\n");

  for (int i = 0; i < pba->process_num; i++) {
    // 打印进程名
    printf("%-8s | ", pba->process_name[i]);

    // 打印 MAX
    for (int j = 0; j < pba->resource_num; j++) {
      printf("%-4d", pba->max[i][j]);
    }
    printf(" | ");

    // 打印 Allocation
    for (int j = 0; j < pba->resource_num; j++) {
      printf("%-4d", pba->allocation[i][j]);
    }
    printf(" | ");

    // 打印 Need
    for (int j = 0; j < pba->resource_num; j++) {
      printf("%-4d", pba->need[i][j]);
    }
    printf(" | ");

    // 打印 Available（仅第一行）
    if (i == 0) {
      for (int j = 0; j < pba->resource_num; j++) {
        printf("%-4d", pba->available[j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}

// 安全性检查
bool Is_safe(BankAlgorithm *pba, int *safe_sequence) {
  int *work = (int *)malloc(pba->resource_num * sizeof(int));
  bool *finish = (bool *)malloc(pba->process_num * sizeof(bool));

  // 初始化 work 和 finish 数组
  for (int i = 0; i < pba->resource_num; i++) {
    work[i] = pba->available[i];
  }
  for (int i = 0; i < pba->process_num; i++) {
    finish[i] = false;
  }

  int count = 0;
  while (count < pba->process_num) {
    bool progress = false;
    for (int i = 0; i < pba->process_num; i++) {
      if (!finish[i]) {
        bool can_finish = true;
        for (int j = 0; j < pba->resource_num; j++) {
          if (pba->need[i][j] > work[j] || pba->need[i][j] < 0) {
            can_finish = false;
            break;
          }
        }

        if (can_finish) {
          for (int j = 0; j < pba->resource_num; j++) {
            work[j] += pba->allocation[i][j];
          }
          safe_sequence[count++] = i;
          finish[i] = true;
          progress = true;
          break;
        }
      }
    }

    if (!progress) {
      free(work);
      free(finish);
      return false; // 无法找到安全序列
    }
  }

  free(work);
  free(finish);
  return true; // 找到安全序列
}

// 初始化数据
void Init_Data(BankAlgorithm *pba) {
  // 初始化资源种类数
  printf("请输入资源种类数: ");
  scanf("%d", &pba->resource_num);

  // 初始化资源名称
  pba->resource_name = (char **)malloc(pba->resource_num * sizeof(char *));
  printf("请输入资源名称:\n");
  for (int i = 0; i < pba->resource_num; i++) {
    pba->resource_name[i] = (char *)malloc(NAMESIZE * sizeof(char));
    printf("资源 %d 名称: ", i + 1);
    scanf("%s", pba->resource_name[i]);
  }

  // 输入资源的总数
  pba->total_resources = (int *)malloc(pba->resource_num * sizeof(int));
  printf("请输入每种资源的总数:\n");
  for (int i = 0; i < pba->resource_num; i++) {
    printf("%s: ", pba->resource_name[i]);
    scanf("%d", &pba->total_resources[i]);
  }

  // 初始化可用资源数组
  pba->available = (int *)malloc(pba->resource_num * sizeof(int));
  for (int i = 0; i < pba->resource_num; i++) {
    pba->available[i] = pba->total_resources[i];
  }

  // 初始化进程数组
  printf("请输入进程数: ");
  scanf("%d", &pba->process_num);

  pba->process_name = (char **)malloc(pba->process_num * sizeof(char *));
  pba->max = (int **)malloc(pba->process_num * sizeof(int *));
  pba->allocation = (int **)malloc(pba->process_num * sizeof(int *));
  pba->need = (int **)malloc(pba->process_num * sizeof(int *));

  for (int i = 0; i < pba->process_num; i++) {
    pba->process_name[i] = (char *)malloc(NAMESIZE * sizeof(char));
    pba->max[i] = (int *)malloc(pba->resource_num * sizeof(int));
    pba->allocation[i] = (int *)malloc(pba->resource_num * sizeof(int));
    pba->need[i] = (int *)malloc(pba->resource_num * sizeof(int));

    printf("请输入进程 %d 的名称: ", i + 1);
    scanf("%s", pba->process_name[i]);

    printf("请输入进程 %s 的资源最大需求和已分配资源数量:\n",
           pba->process_name[i]);

    printf("最大需求: ");
    for (int j = 0; j < pba->resource_num; j++) {
      scanf("%d", &pba->max[i][j]);
    }

    printf("已分配: ");
    for (int j = 0; j < pba->resource_num; j++) {
      scanf("%d", &pba->allocation[i][j]);
      pba->need[i][j] = pba->max[i][j] - pba->allocation[i][j];
    }
  }

  // 更新可用资源
  for (int i = 0; i < pba->resource_num; i++) {
    int sum_allocated = 0;
    for (int j = 0; j < pba->process_num; j++) {
      sum_allocated += pba->allocation[j][i];
    }
    pba->available[i] = pba->total_resources[i] - sum_allocated;
  }
}

// 打印安全序列
void Print_Safe_Sequence(BankAlgorithm *pba) {
  int *safe_sequence = (int *)malloc(pba->process_num * sizeof(int));
  if (Is_safe(pba, safe_sequence)) {
    printf("系统处于安全状态，安全序列为: ");
    for (int i = 0; i < pba->process_num; i++) {
      printf("P%d", safe_sequence[i] + 1);
      if (i != pba->process_num - 1) {
        printf(" -> ");
      }
    }
    printf("\n");
  } else {
    printf("系统当前不安全！\n");
  }
  free(safe_sequence);
}

// 添加新进程
void Add_Process(BankAlgorithm *pba) {
  if (pba->process_num >= MAX_PROCESS_NUM) {
    printf("进程数已达到最大限制，无法添加新进程。\n");
    return;
  }

  pba->process_num++;
  pba->process_name =
      (char **)realloc(pba->process_name, pba->process_num * sizeof(char *));
  pba->max = (int **)realloc(pba->max, pba->process_num * sizeof(int *));
  pba->allocation =
      (int **)realloc(pba->allocation, pba->process_num * sizeof(int *));
  pba->need = (int **)realloc(pba->need, pba->process_num * sizeof(int *));

  pba->process_name[pba->process_num - 1] =
      (char *)malloc(NAMESIZE * sizeof(char));
  pba->max[pba->process_num - 1] =
      (int *)malloc(pba->resource_num * sizeof(int));
  pba->allocation[pba->process_num - 1] =
      (int *)malloc(pba->resource_num * sizeof(int));
  pba->need[pba->process_num - 1] =
      (int *)malloc(pba->resource_num * sizeof(int));

  printf("请输入新进程的名称: ");
  scanf("%s", pba->process_name[pba->process_num - 1]);

  printf("请输入新进程的最大资源需求和已分配资源数量:\n");

  printf("最大需求: ");
  for (int i = 0; i < pba->resource_num; i++) {
    scanf("%d", &pba->max[pba->process_num - 1][i]);
  }

  printf("已分配: ");
  for (int i = 0; i < pba->resource_num; i++) {
    scanf("%d", &pba->allocation[pba->process_num - 1][i]);
    pba->need[pba->process_num - 1][i] =
        pba->max[pba->process_num - 1][i] -
        pba->allocation[pba->process_num - 1][i];
  }

  // 计算并更新可用资源
  for (int i = 0; i < pba->resource_num; i++) {
    int sum_allocated = 0;
    for (int j = 0; j < pba->process_num; j++) {
      sum_allocated += pba->allocation[j][i];
    }
    pba->available[i] = pba->total_resources[i] - sum_allocated;
  }

  int *safe_sequence = (int *)malloc(pba->process_num * sizeof(int));
  if (Is_safe(pba, safe_sequence)) {
    printf("进程添加成功，系统处于安全状态，安全序列为: ");
    for (int i = 0; i < pba->process_num; i++) {
      printf("P%d", safe_sequence[i] + 1);
      if (i != pba->process_num - 1) {
        printf(" -> ");
      }
    }
    printf("\n");
  } else {
    printf("进程添加失败，系统处于不安全状态，数据未更新。\n");
    // 如果不安全，撤销进程的添加
    pba->process_num--;
  }

  free(safe_sequence);
}

// 更新已分配资源
// 更新已分配资源
// 更新已分配资源
void Update_Allocation(BankAlgorithm *pba) {
  int process_id;
  printf("请输入要更新的进程编号（1-%d）：", pba->process_num);
  scanf("%d", &process_id);
  process_id--; // 使得进程编号从0开始

  if (process_id < 0 || process_id >= pba->process_num) {
    printf("无效的进程编号！\n");
    return;
  }

  // 记录更新前的已分配资源和需求（用于回滚）
  int *previous_allocation = (int *)malloc(pba->resource_num * sizeof(int));
  int *previous_need = (int *)malloc(pba->resource_num * sizeof(int));

  for (int i = 0; i < pba->resource_num; i++) {
    previous_allocation[i] = pba->allocation[process_id][i];
    previous_need[i] = pba->need[process_id][i];
  }

  // 输入新的已分配资源数
  printf("请输入新的已分配资源数:\n");
  for (int i = 0; i < pba->resource_num; i++) {
    scanf("%d", &pba->allocation[process_id][i]);
    pba->need[process_id][i] =
        pba->max[process_id][i] - pba->allocation[process_id][i];
  }

  // 更新可用资源
  for (int i = 0; i < pba->resource_num; i++) {
    int sum_allocated = 0;
    for (int j = 0; j < pba->process_num; j++) {
      sum_allocated += pba->allocation[j][i];
    }
    pba->available[i] = pba->total_resources[i] - sum_allocated;
  }

  // 检查系统是否处于安全状态
  int *safe_sequence = (int *)malloc(pba->process_num * sizeof(int));
  if (Is_safe(pba, safe_sequence)) {
    // 安全状态，更新成功
    printf("资源分配更新成功，系统处于安全状态，安全序列为: ");
    for (int i = 0; i < pba->process_num; i++) {
      printf("P%d", safe_sequence[i] + 1);
      if (i != pba->process_num - 1) {
        printf(" -> ");
      }
    }
    printf("\n");
  } else {
    // 不安全状态，撤销更新
    printf("资源分配更新失败，系统处于不安全状态，数据未更新。\n");

    // 撤销已分配资源和需求的更新
    for (int i = 0; i < pba->resource_num; i++) {
      pba->allocation[process_id][i] =
          previous_allocation[i];                  // 恢复已分配的资源
      pba->need[process_id][i] = previous_need[i]; // 恢复需求
    }

    // 更新可用资源
    for (int i = 0; i < pba->resource_num; i++) {
      int sum_allocated = 0;
      for (int j = 0; j < pba->process_num; j++) {
        sum_allocated += pba->allocation[j][i];
      }
      pba->available[i] = pba->total_resources[i] - sum_allocated;
    }
  }

  // 释放之前分配的内存
  free(previous_allocation);
  free(previous_need);

  free(safe_sequence);
}

int main() {
  BankAlgorithm *pba = Init_BankAlgorithm();

  while (1) {
    // 提供选择菜单
    printf("\n请选择操作:\n");
    printf("1) 初始化数据并检查安全性\n");
    printf("2) 检查当前安全性\n");
    printf("3) 添加新进程\n");
    printf("4) 更新已分配资源\n");
    printf("5) 退出\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
      Init_Data(pba);
      Show(pba);
      Print_Safe_Sequence(pba);
    } else if (choice == 2) {
      Show(pba);
      Print_Safe_Sequence(pba);
    } else if (choice == 3) {
      Add_Process(pba);
      Show(pba);
      Print_Safe_Sequence(pba);
    } else if (choice == 4) {
      Update_Allocation(pba);
      Show(pba);
      Print_Safe_Sequence(pba);

    } else if (choice == 5) {
      break;
    }
  }

  free(pba->process_name);
  free(pba->resource_name);
  free(pba->total_resources);
  free(pba->available);
  for (int i = 0; i < pba->process_num; i++) {
    free(pba->max[i]);
    free(pba->allocation[i]);
    free(pba->need[i]);
  }
  free(pba->max);
  free(pba->allocation);
  free(pba->need);
  free(pba);

  return 0;
}
