#include <iostream>
#include <stdlib.h>
struct Node{
    double coef;//系数
    int expn;//指数
    struct Node *next;
};
using LinkList = Node;
LinkList *head1,*head2,*p;
void Insert(LinkList *head,double coef,int expn);//插入（尾插）
void display(LinkList *head);//输出
void add(LinkList *head1,LinkList *head2);//相加
int main(){
    printf("先输入第一个表达式的项数:\n");
    int n1,n2;
    double coef;
    int expn;
    scanf("%d",&n1);
    head1 = new LinkList;
    head1->next = nullptr;//head1初始化
    head2 = new LinkList;
    head2->next = nullptr;//head2初始化
    printf("逐项输入系数与指数并用空格隔开:\n");
    for(int i = 0; i < n1; i++) {
        scanf("%lf %d",&coef,&expn);
        Insert(head1,coef,expn);
    }
    printf("然后输入第二个表达式的项数:\n");
    scanf("%d",&n2);
    printf("逐项输入系数与指数并用空格隔开:\n");
    for(int i = 0; i < n2 ; i++) {
        scanf("%lf %d",&coef,&expn);
        Insert(head2,coef,expn);
    }
    add(head1,head2);
    display(head1);
    return 0;
}

void Insert(LinkList *head,double coef,int expn){
    LinkList *S;
    S = new LinkList;
    S->next = nullptr;
    S->coef = coef;
    S->expn = expn;
    p = head;
    while(p->next != nullptr){
        p = p->next;
    }
    p->next = S;
}
void display(LinkList *head){
    p = head->next;
    while(p->next != nullptr){
        printf("%.2f*x^%d+",p->coef,p->expn);
        p = p->next;
    }
    printf("%.2f*x^%d\n",p->coef,p->expn);
}
void add(LinkList* head1,LinkList* head2) {
	LinkList *pa, *pb,*pre,*temp;
	double sum;
	pa = head1->next;
	pb = head2->next;
	pre = head1;
	while (pa != nullptr && pb != nullptr) {
		if(pa->expn < pb->expn) {
			pre->next = pa;
			pre = pre->next;
			pa = pa->next;
		}else if(pa->expn == pb->expn) {
			sum = pa->coef + pb->coef;
			if(sum != 0) {
				pa->coef = sum;
				pre->next = pa;
				pre = pre->next;
				pa = pa->next;

				temp = pb;
				pb = pb->next;
				delete temp;
			}else{
				temp = pa->next;
				delete pa;
				pa = temp;

				temp = pb->next;
				delete pb;
				pb = temp;
			}
		}else{
			pre->next = pb;
			pre = pre->next;
			pb = pb->next;
		}
	}
	if(pa != nullptr){
		pre->next = pa;
	}else{
		pre->next = pb;
	}
	delete pb;
}
