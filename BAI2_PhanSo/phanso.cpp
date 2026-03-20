#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

void menu() {
	printf("\n");
	printf("\n========================================");
	printf("\n0. Exit");
	printf("\n1. Nhap phan so thu cong");
	printf("\n2. Tao phan so tu dong");
	printf("\n3. Nhap phan so va rut gon");
	printf("\n4. So sanh 2 phan so");
}
struct PhanSo {
	int Tuso;
	int Mauso;
};

typedef PhanSo ItemType;

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
	if (p == NULL) return NULL;
	p->Info = x;
	p->Next = NULL;
	return p;
}
void xuatPhanSo(PhanSo x) {
	printf("%d/%d", x.Tuso, x.Mauso);
}

void showSNode(SNode* p) {
	xuatPhanSo(p->Info);
}

void deleteSNode(SNode*& p) {
	if (p == NULL) return;
	p->Next = NULL;
	delete p;
}

void initSList(SList& sl) {
	sl.Head = NULL;
	sl.Tail = NULL;
}

int isEmpty(SList sl) {
	if (sl.Head == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

void showSList(SList sl) {
	if (isEmpty(sl) == 1) {
		printf("\nDanh sach rong");
		return;
	}
	else {
		printf("\nCac phan so cua ban la: ");
		for (SNode* p = sl.Head; p != NULL; p = p->Next) {
			showSNode(p);
			printf(" -> ");
		}
		printf("NULL");
	}
}

void kiemTraDoiDau(PhanSo& x) {
	if (x.Mauso < 0) {
		x.Tuso *= -1;
		x.Mauso *= -1;
	}
}

int timUCLN(int a, int b) {
	if (a == 0 || b == 0) {
		return 1;
	}
	a = abs(a);
	b = abs(b);
	while (a != b) {
		if (a > b) {
			a -= b;
		}
		else{
			b -= a;
		}
	}
	return a;
}

void rutGonPhanSo(PhanSo& x) {
	kiemTraDoiDau(x);
	int usc = timUCLN(x.Tuso, x.Mauso);
	x.Tuso /= usc;
	x.Mauso /= usc;
}

void nhapPhanSo(PhanSo& x) {
	do {
		printf("\nVui long nhap vao tu so: ");
		scanf("%d", &x.Tuso);
	} while (x.Tuso == 0);
	do {
		printf("\nVui long nhap vao mau so: ");
		scanf("%d", &x.Mauso);
	} while (x.Mauso == 0);
	rutGonPhanSo(x);
}

int insertTail(SList& sl, SNode* p) {
	if (p == NULL) return 0;
	if (isEmpty(sl) == 1) {
		sl.Head = sl.Tail = p;
	}
	else {
		sl.Tail->Next = p;
		sl.Tail = p;
	}
	return 1;
}
void createSList_InputByHand(SList& sl) {
	ItemType ps;
	int n;
	initSList(sl);
	do {
		printf("\nNhap vao so luong phan so (n>0) : ");
		scanf("%d", &n);
	} while (n <= 0);
	int i = 0;
	while (i < n) {
		nhapPhanSo(ps);
		SNode* p = createSNode(ps);
		int kq = insertTail(sl, p);
		if (kq == 1) i++;
	}
}
void createSList_Random(SList& sl) {
	ItemType ps;
	initSList(sl);
	int n;
	do {
		printf("\nNhap vao so luong phan tu cua danh sach: ");
		scanf("%d", &n);
	} while (n <= 0);
	int i = 0;
	srand((unsigned)time(NULL));
	while (i < n) {
		int x;
		do {
			ps.Tuso = (rand() % 199) - 99;
		} while (ps.Tuso == 0);
		x = ps.Tuso;
		do {
			ps.Mauso = (rand() % 199) - 99;
		} while (ps.Mauso == 0);
		x = ps.Mauso;
		rutGonPhanSo(ps);
		SNode* p = createSNode(ps);
		int kq = insertTail(sl, p);
		if (kq == 1) {
			i++;
		}
		else {
			printf("\nKhong the chen phan so");
		}
	}
}
int soSanhPhanSo(PhanSo ps1, PhanSo ps2) {
	int kq = (ps1.Tuso * ps2.Mauso) - (ps2.Mauso * ps1.Mauso);
	if (kq > 1) {
		return 1;
	}
	else if (kq == 0) {
		return 0;
	}
	else {
		return -1;
	}
}
void process() {
	int chon;
	PhanSo ps;
	SList sl;
	ItemType x;
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
				createSList_InputByHand(sl);
				showSList(sl);
				break;
			}
			case 2: 
			{
				createSList_Random(sl);
				showSList(sl);
				break;
			}
			case 3:
			{
				nhapPhanSo(ps);
				printf("\nPhan so cua ban la: ");
				rutGonPhanSo(ps);
				xuatPhanSo(ps);
				break;
			}
			case 4:
			{
				PhanSo ps1, ps2;
				printf("\n*Nhap phan so thu nhat*");
				nhapPhanSo(ps1);
				printf("\nPhan so thu nhat: ");
				printf("\n*Nhap phan so thu hai*");
				nhapPhanSo(ps2);
				printf("\nPhan so thu nhat: ");
				xuatPhanSo(ps1);
				printf("\nPhan so thu hai: ");
				xuatPhanSo(ps2);
				int kq = soSanhPhanSo(ps1, ps2);
				if (kq == 1) {
					printf("\nKet qua: Phan so thu nhat lon hon phan so thu hai");
				}
				else if (kq == 0) {
					printf("\nKet qua: Phan so thu nhat bang phan so thu hai");
				}
				else {
					printf("\nKet qua: Phan so thu nhat be hon phan so thu hai");
				}
			}

		}
	} while (chon != 0);
}
void main() {
	process();
}
