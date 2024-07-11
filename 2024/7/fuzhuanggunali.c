#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
// 用枚举量表示衣服尺码
enum fitting { null, S, M, L, XL, XXL, XXXL };
struct Close {
  unsigned int id;
  char name[20];
  enum fitting fitting;
  unsigned int price;
  unsigned int amount;
};
// 顺序表
struct CloseList {
  struct Close *closes;
  // 当前长度
  unsigned int length;
  // 表容量
  unsigned int capacity;
} close_list;

// 将字符串转为枚举量
enum fitting a2e(char *fitting) {
  // strcmp返回0代表两个字符串相同
  if (strcmp(fitting, "S") == 0) {
    return S;
  } else if (strcmp(fitting, "M") == 0) {
    return M;
  } else if (strcmp(fitting, "L") == 0) {
    return L;
  } else if (strcmp(fitting, "XL") == 0) {
    return XL;
  } else if (strcmp(fitting, "XXL") == 0) {
    return XXL;
  } else if (strcmp(fitting, "XXXL") == 0) {
    return XXXL;
  }
  return null;
}

char *e2a(enum fitting fitting) {
  if (fitting == S) {
    return "S";
  } else if (fitting == M) {
    return "M";
  } else if (fitting == L) {
    return "L";
  } else if (fitting == XL) {
    return "XL";
  } else if (fitting == XXL) {
    return "XXL";
  } else if (fitting == XXXL) {
    return "XXXL";
  }
  return "NULL";
}

void expansion() {
  // 每次扩容一倍大小
  if (close_list.capacity == 0) {
    close_list.closes = (struct Close *)malloc(sizeof(struct Close) * 8);
    close_list.capacity = 8;
    // 将close记录都初始化为0
    memset(close_list.closes, 0, sizeof(struct Close) * 8);
    return;
  }
  struct Close *temp = close_list.closes;
  // 申请更大的空间
  close_list.closes = (struct Close *)malloc(close_list.capacity * 2);
  // 拷贝数据
  memcpy(close_list.closes, temp, close_list.capacity);
  close_list.capacity *= 2;
  free(temp);
}

// 1. 输入记录模块
// 逐个从文件中读取消费记录，用该数据初始化数组结构。
// 服装基本信息包含：编号，名称(hat,skirt,short sleeve
// ...)，尺码，价格，库存数量等
void input(unsigned int id, char name[20], enum fitting fitting,
           unsigned int price, unsigned int amount) {
  if (fitting == null) {
    printf("输入的尺寸有误\n");
    return;
  }
  // 顺序表满了需要扩容
  if (close_list.length >= close_list.capacity) {
    expansion();
  }
  // 更新数据
  close_list.closes[close_list.length].id = id;
  memcpy(close_list.closes[close_list.length].name, name, 20);
  close_list.closes[close_list.length].fitting = fitting;
  close_list.closes[close_list.length].price = price;
  close_list.closes[close_list.length].amount = amount;
  close_list.length++;
}

// 2. 查询记录模块
// 可以通过服装编号和尺码查找服装记录
// 分别把满足条件的学生信息显示出来。
void find() {
  unsigned int c, len = close_list.length;
  printf("输入1使用标号查询服装信息,输入2使用尺码查询服装信息\n");
  scanf("%u", &c);
  if (c == 1) {
    printf("输入id:");
    unsigned int id;
    scanf("%u", &id);
    while (len--) {
      if (close_list.closes[len].id == id) {
        printf("%u %s %s %u %u\n", close_list.closes[len].id,
               close_list.closes[len].name, e2a(close_list.closes[len].fitting),
               close_list.closes[len].price, close_list.closes[len].amount);
      }
    }
  } else if (c == 2) {
    char fitting[5];
    scanf("%s", fitting);
    while (len--) {
      if (close_list.closes[len].fitting == a2e(fitting)) {
        printf("%u %s %s %u %u\n", close_list.closes[len].id,
               close_list.closes[len].name, e2a(close_list.closes[len].fitting),
               close_list.closes[len].price, close_list.closes[len].amount);
      }
    }
  } else {
    printf("输入错误\n");
    return;
  }
}

// 3. 更新记录模块
// 修改某一个服装信息，插入一个服装信息，删除一个服装的信息等功能
void update() {
  unsigned int c, id;
  printf("输入1修改某一服装信息,输入2删除一个服装信息\n");
  scanf("%d", &c);
  if (c != 1 && c != 2) {
    printf("输入错误\n");
    return;
  }
  printf("输入对应服装的id:");
  scanf("%d", &id);
  unsigned int len = close_list.length;
  while (len--) {
    if (close_list.closes[len].id == id) {
      if (c == 1) {
        char fitting[5];
        printf("输入服装的 编号 名称 尺码 价格 库存数量\n");
        scanf("%u %s %s %u %u", &close_list.closes[len].id,
              close_list.closes[len].name, fitting,
              &close_list.closes[len].price, &close_list.closes[len].amount);
        close_list.closes[len].fitting = a2e(fitting);
      } else {
        memmove(&close_list.closes[len], &close_list.closes[len + 1],
                (close_list.length - len + 1) * sizeof(struct Close));
        close_list.length--;
      }
      return;
    }
  }
  printf("不存在这个id的服装\n");
}

// 4. 统计记录模块
// 统计出库存服装数最多的服装，显示其信息
// 统计库存不足（库存数<=3）的服装信息
void total() {
  unsigned int len = close_list.length, max_amount = 0;
  // 第一遍找到最多的数量
  for (int i = 0; i < len; i++) {
    if (close_list.closes[i].amount > max_amount) {
      max_amount = close_list.closes[i].amount;
    }
  }
  printf("库存服装数量最多的服装信息:\n");
  // 第二遍输出所有数量最多的服装信息
  for (int i = 0; i < len; i++) {
    if (close_list.closes[i].amount == max_amount) {
      printf("%u %s %s %u %u\n", close_list.closes[i].id,
             close_list.closes[i].name, e2a(close_list.closes[i].fitting),
             close_list.closes[i].price, close_list.closes[i].amount);
    }
  }
  printf("库存数量不足的服装信息:\n");
  // 第三遍输出库存数量不足的
  for (int i = 0; i < len; i++) {
    if (close_list.closes[i].amount < 4) {
      printf("%u %s %s %u %u\n", close_list.closes[i].id,
             close_list.closes[i].name, e2a(close_list.closes[i].fitting),
             close_list.closes[i].price, close_list.closes[i].amount);
    }
  }
}

// 5. 输出记录模块
// 显示所有服装的信息。
void output() {
  unsigned int len = close_list.length;
  while (len--) {
    printf("%u %s %s %u %u\n", close_list.closes[len].id,
           close_list.closes[len].name, e2a(close_list.closes[len].fitting),
           close_list.closes[len].price, close_list.closes[len].amount);
  }
}

// 6. 能够将所有服装信息保存到文件中
void save() {
  FILE *file;
  file = fopen("close.dat", "w");
  fprintf(file, "%d\n", close_list.length);
  while (close_list.length--) {
    fprintf(file, "%u %s %s %u %u\n", close_list.closes[close_list.length].id,
            close_list.closes[close_list.length].name,
            e2a(close_list.closes[close_list.length].fitting),
            close_list.closes[close_list.length].price,
            close_list.closes[close_list.length].amount);
  }
  fclose(file);
}

// 初始化系统,读取文件信息
void init() {
  FILE *file;
  file = fopen("close.dat", "r");
  // 文件不存在,创建新文件输入数据大小为0,重新打开文件
  if (!file) {
    int fd = creat("close.dat", S_IRUSR | S_IWUSR);
    if (write(fd, "0\n", 2) == -1) {
      printf("write error\n");
      exit(1);
    }
    file = fopen("close.dat", "r");
  }
  int len;
  // 文件的第一个数据是数据大小也就是保存的服装的数据的数量
  fscanf(file, "%d", &len);
  for (int i = 0; i < len; i++) {
    unsigned int id, amount, price;
    char name[20], fitting[5];
    fscanf(file, "%u %s %s %u %u", &id, name, fitting, &price, &amount);
    input(id, name, a2e(fitting), price, amount);
  }
  fclose(file);
}

int main() {
  init();
  int c;
  unsigned int id, amount, price;
  char name[20], fitting[5];
  while (1) {
    printf("输入你的操作:\n1.输入新服装信息\n2.查找服装信息\n3.更新服装信息\n4."
           "统计记录\n5.显示所有服装信息\n6.退出系统\n");
    scanf("%d", &c);
    switch (c) {
    case 1:
      printf("输入服装的 编号 名称 尺码 价格 库存数量\n");
      scanf("%u %s %s %u %u", &id, name, fitting, &price, &amount);
      input(id, name, a2e(fitting), price, amount);
      break;
    case 2:
      find();
      break;
    case 3:
      update();
      break;
    case 4:
      total();
      break;
    case 5:
      output();
      break;
    case 6:
      goto out;
    default:
      printf("输入错误\n");
    }
  }
out:
  save();
  free(close_list.closes);
  return 0;
}
