#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
typedef int ItemType;
struct SNode {
	ItemType Info;
	SNode* Next;
};
struct SList {
	SNode* Head;
	SNode* Tail;
};
SNode* createSNode(ItemType x) {
	SNode* p = new SNode;
	if (p == 0) return NULL;
	p->Info = x;
	p->Next = NULL;
	return p;
}
void initSList(SList& sl) {
	sl.Head = sl.Tail = NULL;
}
void showSNode(SNode* p) {
	printf("%d", p->Info);
}
void showSList(SList sl) {
	if (sl.Head == 0) {
		printf("\nDanh sach rong");
		return;
	}
	else {
		printf("\nDanh sach cua ban la: ");
		for (SNode* p = sl.Head; p != NULL; p = p->Next) {
			showSNode(p);
			printf(" -> ");
		}
		printf("NULL");
	}
}
void swap(ItemType& x, ItemType& y) {
	ItemType temp = x;
	x = y;
	y = temp;
}
void sapSepTangDan(SList sl) {
	if (sl.Head == NULL) {
		return;
	}
	else {
		for (SNode* p = sl.Head; p != NULL; p = p->Next) {
			for (SNode* q = p->Next; q != NULL; q = q->Next) {
				if (p->Info > q->Info) {
					swap(p->Info, q->Info);
				}
			}
		}
	}
}
int addHead(SList& sl, SNode* p) {
	if (p == NULL) return 0;
	if (sl.Head == NULL) {
		sl.Head = sl.Tail = p;
	}
	else {
		p->Next = sl.Head;
		sl.Head = p;
	}
	return 1;
}
int addTail(SList& sl, SNode* p) {
	if (p == NULL) return 0;
	if (sl.Head == NULL) {
		sl.Head = sl.Tail = p;
	}
	else {
		sl.Tail->Next = p;
		sl.Tail = p;
	}
	return 1;

}
void createSList(SList& sl) {
	int n;
	ItemType x;
	initSList(sl);
	do {
		printf("\nNhap vao so luong phan tu: ");
		scanf("%d", &n);
	} while (n <= 0);
	int i = 0;
	while (i < n) {
		printf("\nNhap vao phan tu thu %d: ", i + 1);
		scanf("%d", &x);
		SNode* p = createSNode(x);
		int kq = addHead(sl, p);
		if (kq == 1) i++;
	}
}
void noisl2sausl1(SList& sl1, SList& sl2, ItemType x) {
	if (sl1.Head == NULL) {
		return;
	}
	SNode* p = sl1.Head;
	while (p != NULL && p->Info != x) {
		p = p->Next;
	}
	if (p == NULL) {
		printf("\nKhong co phan tu x");
		return;
	}
	if (sl2.Head == NULL) {
		printf("\nDanh sach 2 rong!");
		return;
	}
	sl2.Tail->Next = p->Next;
	p->Next = sl2.Head;
	if (p == sl1.Tail) {
		sl2.Tail = sl1.Tail;
	}
	printf("\nNoi thanh cong");
}
void menu() {
	printf("\n");
	printf("\n========================================");
	printf("\n	*MENU*					  ");
	printf("\n0. Exit");
	printf("\n1. Nhap danh sach");
	printf("\n2. Sap xep danh sach tang dan");
	printf("\n3. Them phan tu sao cho danh sach tang");
	printf("\n4. Noi danh sach sl2 vao sau phan tu co gia tri x trong danh sach sl1");
}
void process() {
	ItemType x;
	SList sl, sl2;
	int chon;
	initSList(sl);
	do {
		menu();
		do {
			printf("\nNhap vao lua chon cua ban: ");
			scanf("%d", &chon);
		} while (chon < 0);
		switch (chon)
		{
			case 1:
			{
				createSList(sl);
				showSList(sl);
				break;
			}
			case 2:
			{
				printf("\nDanh sach sau khi sap xep tang");
				sapSepTangDan(sl);
				showSList(sl);
			}
			case 3:
			{
				printf("\nNhap vao phan tu can them: ");
				scanf("%d", &x);
				SNode* p = createSNode(x);
				addTail(sl, p);
				sapSepTangDan(sl);
				showSList(sl);
				break;
			}
			case 4:
			{
				showSList(sl);
				printf("\nNhap vao danh sach sl2: ");
				createSList(sl2);
				printf("\nNhap vao phan tu x de them sl2: ");
				scanf("%d", &x);
				noisl2sausl1(sl, sl2, x);
				showSList(sl);
				break;
			}
		}
	} while (chon != 0);
}
int main() {
	process();
	return 1;
}

