#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define PHONE_LEN 20
#define FILE_NAME "phonebook.txt"

// 电话节点
typedef struct PhoneNode {
  char phone[PHONE_LEN];
  struct PhoneNode *next;
} PhoneNode;

// 联系人节点
typedef struct Contact {
  int id;
  char name[NAME_LEN];
  PhoneNode *phones;
  struct Contact *next;
} Contact;
Contact *head = NULL;
int contact_count = 0, phone_count = 0;

// 创建一个电话号码节点
PhoneNode *createPhoneNode(const char *number) {
  PhoneNode *newNode = (PhoneNode *)malloc(sizeof(PhoneNode));
  strcpy(newNode->phone, number);
  newNode->next = NULL;
  return newNode;
}

// 创建一个联系人节点
Contact *createContact(int id, const char *name) {
  Contact *newContact = (Contact *)malloc(sizeof(Contact));
  newContact->id = id;
  strcpy(newContact->name, name);
  newContact->phones = NULL;
  newContact->next = NULL;
  return newContact;
}

// 添加联系人（支持多个电话号码）
void addContact() {
  int id, phoneNum;
  char name[NAME_LEN];
  char phone[PHONE_LEN];

  printf("输入用户编号: ");
  scanf("%d", &id);
  printf("输入姓名: ");
  scanf("%s", name);

  Contact *contact = createContact(id, name);

  printf("输入电话号码数量: ");
  scanf("%d", &phoneNum);

  for (int i = 0; i < phoneNum; i++) {
    printf("输入电话 #%d: ", i + 1);
    scanf("%s", phone);
    PhoneNode *phoneNode = createPhoneNode(phone);
    phoneNode->next = contact->phones;
    contact->phones = phoneNode;
    phone_count++;
  }

  contact->next = head;
  head = contact;
  contact_count++;

  printf("联系人添加成功！\n");
}

// 按姓名或号码查询
void searchContact() {
  char keyword[NAME_LEN];
  printf("输入姓名或电话号码查询: ");
  scanf("%s", keyword);

  Contact *curr = head;
  while (curr) {
    if (strcmp(curr->name, keyword) == 0) {
      printf("找到联系人: %s (ID: %d)\n", curr->name, curr->id);
      PhoneNode *p = curr->phones;
      while (p) {
        printf("  电话: %s\n", p->phone);
        p = p->next;
      }
    } else {
      PhoneNode *p = curr->phones;
      while (p) {
        if (strcmp(p->phone, keyword) == 0) {
          printf("找到号码所属联系人: %s (ID: %d)\n", curr->name, curr->id);
          printf("  电话: %s\n", p->phone);
          break;
        }
        p = p->next;
      }
    }
    curr = curr->next;
  }
}

// 修改电话
void modifyPhone() {
  char name[NAME_LEN];
  printf("输入要修改电话的联系人姓名: ");
  scanf("%s", name);

  Contact *curr = head;
  while (curr && strcmp(curr->name, name) != 0) {
    curr = curr->next;
  }

  if (!curr) {
    printf("未找到该联系人。\n");
    return;
  }

  char oldPhone[PHONE_LEN], newPhone[PHONE_LEN];
  printf("输入要修改的旧电话: ");
  scanf("%s", oldPhone);

  PhoneNode *p = curr->phones;
  while (p && strcmp(p->phone, oldPhone) != 0) {
    p = p->next;
  }

  if (!p) {
    printf("未找到该电话。\n");
    return;
  }

  printf("输入新电话: ");
  scanf("%s", newPhone);
  strcpy(p->phone, newPhone);
  printf("电话修改成功。\n");
}

// 删除联系人
void deleteContact() {
  char name[NAME_LEN];
  printf("输入要删除的联系人姓名: ");
  scanf("%s", name);

  Contact *curr = head, *prev = NULL;

  while (curr && strcmp(curr->name, name) != 0) {
    prev = curr;
    curr = curr->next;
  }

  if (!curr) {
    printf("未找到联系人。\n");
    return;
  }

  // 删除其所有电话
  PhoneNode *p = curr->phones;
  while (p) {
    PhoneNode *temp = p;
    p = p->next;
    free(temp);
    phone_count--;
  }

  if (prev) {
    prev->next = curr->next;
  } else {
    head = curr->next;
  }

  free(curr);
  contact_count--;
  printf("联系人删除成功。\n");
}

// 显示所有联系人
void displayContacts() {
  Contact *curr = head;
  while (curr) {
    printf("ID: %d, 姓名: %s\n", curr->id, curr->name);
    PhoneNode *p = curr->phones;
    while (p) {
      printf("  电话: %s\n", p->phone);
      p = p->next;
    }
    curr = curr->next;
  }
}

// 显示统计信息
void showStats() {
  printf("总联系人数量: %d\n", contact_count);
  printf("总电话号码数量: %d\n", phone_count);
}

void saveToFile() {
  FILE *fp = fopen(FILE_NAME, "w");
  if (!fp) {
    perror("打开文件失败");
    return;
  }

  Contact *curr = head;
  while (curr) {
    fprintf(fp, "%d %s", curr->id, curr->name);
    PhoneNode *p = curr->phones;
    while (p) {
      fprintf(fp, " %s", p->phone);
      p = p->next;
    }
    fprintf(fp, "\n");
    curr = curr->next;
  }

  fclose(fp);
  printf("已保存到文件。\n");
}

void loadFromFile() {
  FILE *fp = fopen(FILE_NAME, "r");
  if (!fp) {
    printf("未找到存档文件，将创建新电话簿。\n");
    return;
  }

  int id;
  char name[NAME_LEN];
  char line[256];

  while (fgets(line, sizeof(line), fp)) {
    char *token = strtok(line, " \n");
    if (!token)
      continue;

    id = atoi(token);
    token = strtok(NULL, " \n");
    if (!token)
      continue;
    strcpy(name, token);

    Contact *newContact = createContact(id, name);
    token = strtok(NULL, " \n");
    while (token) {
      PhoneNode *p = createPhoneNode(token);
      p->next = newContact->phones;
      newContact->phones = p;
      phone_count++;
      token = strtok(NULL, " \n");
    }

    newContact->next = head;
    head = newContact;
    contact_count++;
  }

  fclose(fp);
  printf("已从文件加载联系人。\n");
}

int main() {
  int choice;
  loadFromFile(); // 加载数据

  while (1) {
    printf("\n==== 电话簿系统 ====\n");
    printf("1. 添加联系人\n");
    printf("2. 查询联系人\n");
    printf("3. 修改电话\n");
    printf("4. 删除联系人\n");
    printf("5. 显示所有联系人\n");
    printf("6. 统计信息\n");
    printf("0. 退出\n");
    printf("请选择: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      addContact();
      break;
    case 2:
      searchContact();
      break;
    case 3:
      modifyPhone();
      break;
    case 4:
      deleteContact();
      break;
    case 5:
      displayContacts();
      break;
    case 6:
      showStats();
      break;
    case 0:
      saveToFile(); // 保存数据
      exit(0);
    default:
      printf("无效选择。\n");
    }
  }
  return 0;
}
