#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE* StuInfo;
typedef struct Student {
	char name[20];
	char number[20];
	int math, chinese, english;
	int score;
	struct Student* next;
}Student;
void initiation_system();
void add_student();
void find_student();
void update_student_information();
void delete_stu(Student*);
void total();
void save_data();
void main_gui();
Student* first = NULL,* end = NULL;
int main()
{
	initiation_system();
	while (1) main_gui();
	return 0;
}
void initiation_system()//初始化系统
{
	StuInfo = fopen("information.txt", "a+");
    Student* thisp;
    char name[20], number[20];
    int math, chinese, english, score;
    while (fscanf(StuInfo, "%s %s %d %d %d %d", &name, &number, &math, &chinese, &english, &score) != EOF)//创建链表
    {
        Student* node = (Student*)malloc(sizeof(Student));
        {
            strcpy(node->name, name);
            strcpy(node->number, number);
            node->math = math;
            node->chinese = chinese;
            node->english = english;
            node->score = score;
            node->next = NULL;
        }
        if (!first)
            first = node;
        else
            thisp->next = node;
			end = thisp = node;
		}
	fclose(StuInfo);
}
void add_student() {
	int a = 1;
	char name[20];
	char number[20];
	int math, chinese, english;
	printf("请输入学生的学号、姓名、数学、语文、英语成绩\n");
	while(a){
		scanf("%20s %20s %d %d %d", &number, &name, &math, &chinese, &english);
        Student* node = (Student*)malloc(sizeof(Student));
        strcpy(node->name, name);
        strcpy(node->number, number);
        node->math = math;
        node->chinese = chinese;
        node->english = english;
        node->score = math + chinese + english;
        node->next = NULL;
        if(first)
        {
            end->next = node;
            end = node;
        }
        else
        {
            first = end = node;
        }
		printf("添加成功，输入1继续添加，输入0退出。");
		scanf("%d", &a);
	}
	system("cls");
}
void find_student() {
    int a,b = 0;
    printf("输入查询方式    1.学号  2.姓名");
    scanf("%d",&a);
    if(a-2)
    {
        printf("请输入你要查找的人的学号\n");
        char number[20];
        scanf("%s", &number);
        Student *thisp = first;
        while (thisp)
        {
            if (!strcmp(thisp->number, number))
            {
                b++;
                printf("该生以下信息在这：\n%20s%7s%6d%6d%6d%6d\n", thisp->number, thisp->name, thisp->math,thisp->chinese, thisp->english, thisp->score);
                break;
            } else thisp = thisp->next;
        }
    }
    else
    {
        printf("请输入你要查找的人的姓名\n");
        char name[20];
        scanf("%s",&name);
        Student *thisp = first;
        while(thisp)
        {
            if(!strcmp(thisp->name,name))
            {
                b++;
                printf("该生以下信息在这：\n%20s%7s%6d%6d%6d%6d\n", thisp->number, thisp->name, thisp->math,thisp->chinese, thisp->english, thisp->score);
            }
            thisp = thisp->next;
        }
    }
    if(!b) printf("没找到此人\n");
    printf("再次回车退出……");
    getchar();
    getchar();
}
void update_student_information() {
    printf("输入你要修改的学生学号\n");
    char number[20];
    int b = 0;
    scanf("%s", &number);
    Student *thisp = first;
    while (thisp)
    {
        if (!strcmp(thisp->number, number))
        {
            int cho;
            printf("已找到该生请选择操作     1.更改信息  2.删除该生");
            scanf("%d",&cho);
            if(cho-2){
                char name[20];
                char number[20];
                int math, chinese, english;
                b++;
                printf("重新输入该生信息：\n");
                scanf("%20s %20s %d %d %d", &number, &name, &math, &chinese, &english);
                strcpy(thisp->name, name);
                strcpy(thisp->number, number);
                thisp->math = math;
                thisp->chinese = chinese;
                thisp->english = english;
                thisp->score = math + chinese + english;
                break;
            }
            else
            {
                b++;
                delete_stu(thisp);//这找到就把找到的节点传进去
                break;
            }
        } else thisp = thisp->next;
    }
    if(!b) printf("没找到该生\n");
    printf("再次回车退出……");
    getchar();
    getchar();
}
void delete_stu(Student* p)
{
    if(p == first){
        first = first->next;
    }
    else{
        Student *pre = first;
        while (pre->next != p);//找到要删除的节点的上一个节点
        pre->next = p->next;
    }
    free(p);
}
int max(int a,int b){return a>b?a:b;}
void total() {

    int ma = 0,ch = 0,en = 0;
    int ma1 = 0,ch1 = 0,en1 = 0;
    Student *thisp = first;
    while(thisp)
    {
        if(thisp->math<60) ma1++;
        if(thisp->chinese<60) ch1++;
        if(thisp->english<60) en1++;
        ma = max(ma,thisp->math);
        ch = max(ch,thisp->chinese);
        en = max(en,thisp->english);
        thisp = thisp->next;
    }
    printf("数学不合格人数%d，语文不合格人数%d，英语不合格人数%d\n数学最高分%d，语文最高分%d，英语最高分%d\n",ma1,ch1,en1,ma,ch,en);
    printf("再次回车退出……");
    getchar();
    getchar();
}
void show_information(){
	Student* thisp = first;
	printf("           学号        姓名   数学  语文  英语  总分\n");
	while (thisp)
	{
		printf("%20s%7s%6d%6d%6d%6d\n", thisp->number, thisp->name, thisp->math, thisp->chinese, thisp->english, thisp->score);
		thisp = thisp->next;
	}
	printf("再次回车退出……");
    getchar();
    getchar();
}
void save_data() {
	Student* thisp = first;
    StuInfo = fopen("information.txt","w+");
	while (thisp)
	{
		fprintf(StuInfo, "%s %s %d %d %d %d\n", thisp->name, thisp->number, thisp->math, thisp->chinese, thisp->english, thisp->score);
		thisp = thisp->next;
	}
    fclose(StuInfo);
}
void main_gui()
{
    system("cls");
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*          1.添加学生信息         *\n");
    printf("*          2.查找学生信息         *\n");
    printf("*          3.修改学生信息         *\n");
    printf("*          4.统计学生信息         *\n");
    printf("*          5.显示学生信息         *\n");
    printf("*          6.退出系统             *\n");
    printf("*                                 *\n");
    printf("***********************************\n");
	switch (getchar() - '0')
	{
	case 1: add_student();
		break;
	case 2: find_student();
		break;
	case 3: update_student_information();
		break;
	case 4: total();
		break;
	case 5:	show_information();
		break;
	case 6: save_data();
        exit(0);
	}
}