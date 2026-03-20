#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
typedef int ItemType;

struct SNode {
	ItemType Info;
	SNode* Next;
};

SNode* createSNode(ItemType x) {
	SNode* p = new SNode;
	if (p == NULL) {
		printf("\nKhong du bo nho de cap phat");
		_getch();
		return NULL;
	}
	p->Info = x;
	p->Next = NULL;
	return p;
}

void showSNode(SNode* p) {
	printf("%d", p->Info);
}

void deleteSNode(SNode*& p) {
	if (p == NULL) return;
	p->Next = NULL;
	delete p;
}

struct SList {
	SNode* Head;
	SNode* Tail;
};

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
		printf("\nDanh sach rong!");
		return;
	}
	printf("\nDanh sach cua ban la: ");
	for (SNode* p = sl.Head; p != NULL; p = p->Next) {
		showSNode(p);
		printf(" -> ");
	}
	printf("NULL");
}

int addHead(SList& sl, SNode* p) {
	if (p == NULL) {
		return 0;
	}
	if (isEmpty(sl) == 1) {
		sl.Head = sl.Tail = p;
	}
	else {
		p->Next = sl.Head;
		sl.Head = p;
	}
	return 1;
}

void addTail(SList& sl, SNode* p) {
	if (p == NULL) {
		return;
	}
	if (isEmpty(sl) == 1) {
		sl.Head = sl.Tail = p;
	}
	else {
		sl.Tail->Next = p;
		sl.Tail = p;
	}
}

void addAfter(SList& sl, SNode* q, SNode* p) {
	if (q == NULL || p == NULL) {
		return;
	}
	p->Next = q->Next;
	q->Next = p;
	if (sl.Tail == q) {
		sl.Tail = p;
	}
}

void addBefore(SList& sl, SNode* q, SNode* p) {
	if (q == NULL || p == NULL) {
		return;
	}
	if (sl.Head == q) {
		addHead(sl, p);
		return;
	}
	SNode* prev = sl.Head;						// (head)->prev:1 2 (3) 4						
	while (prev != NULL && prev->Next != q) {	// 1. prev = 2 
		prev = prev->Next;						// 2. stop => prev = 2
	}
	if (prev != NULL) {			//1 -> 2 -> 3 -> 4 . add p=6 before q=3
		p->Next = q;			// 6 -> 3 -> 4
		prev->Next = p;			//1 -> 2 -> 6 -> 3 -> 4
	}
}

SNode* findSNode(SList sl, ItemType x) {
	if (sl.Head == NULL) {
		return NULL;
	}
	SNode* p = sl.Head;
	while (p != NULL) {
		if (p->Info == x) {
			return p;
		}
		p = p->Next;
	}
	return NULL;
}

void createSList_InputByHand(SList& sl) {
	int n;
	ItemType x;
	initSList(sl);
	do {
		printf("\nNhap vao so luong phan tu cua danh sach (n >= 0): ");
		scanf("%d", &n);
	} while (n <= 0);
	int i = 0;
	while (i < n) {
		printf("\nNhap vao phan tu thu %d: ", i+1);
		scanf("%d", &x);
		SNode* p = createSNode(x);
		int kq = addHead(sl, p);
		if (kq == 1) i++;
	}
}

void createSList_Random(SList& sl) {
	int n;
	ItemType x;
	initSList(sl);
	do {
		printf("\nNhap vao so luong phan tu cua danh sach (n >= 0): ");
		scanf("%d", &n);
	} while (n <= 0);
	srand((unsigned)time(NULL));
	int i = 1;
	while (i < n) {
		x = (rand() % 199) - 99;
		SNode* p = createSNode(x);
		int kq = addHead(sl, p);
		if (kq == 1) i++;
	}
}

void createSList_FromTextFile(SList& sl, char inputFilename[]) {
	int n, x;
	initSList(sl);
	FILE* fi = fopen(inputFilename, "rt");
	if (fi == NULL) {
		printf("\nLoi mo file: %s", inputFilename);
		return;
	}
	fscanf(fi, "%d", &n);

	for (int i = 0; i < n; i++) {
		if (fscanf(fi, "%d", &x) != 1) break;
		SNode* p = createSNode(x);
		addHead(sl, p);
	}
	fclose(fi);
}
void swap(ItemType& x, ItemType& y) {
	ItemType tmp = x;
	x = y;
	y = tmp;
}
void sortSList_ChonTrucTiep(SList& sl) {
	if (isEmpty(sl) == 1) {
		return;
	}
	for (SNode* p = sl.Head; p != NULL; p = p->Next) {
		SNode* min = p;
		for (SNode* q = p->Next; q != NULL; q = q->Next) {
			if (q->Info < min->Info) {
				min = q;
			}
		}
		if (min != p) {
			swap(min->Info, p->Info);
		}
	}
}
void sortSList_DoiChoTrucTiep(SList& sl) {
	if (isEmpty(sl) == 1) {
		return;
	}
	for (SNode* p = sl.Head; p != NULL; p = p->Next) {
		for (SNode* q = p->Next; q != NULL; q = q->Next) {
			if (q->Info < p->Info) {
				swap(q->Info, p->Info);
			}
		}
	}
}

int ktraSNT(ItemType x) {
	if (x < 2) {
		return 0;
	}
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			return 0;
		}
	}
	return 1;
}

int demSNT(SList sl) {
	int dem = 0;
	for (SNode* p = sl.Head; p != NULL; p = p->Next) {
		if (ktraSNT(p->Info)) {
			dem++;
		}
	}
	return dem;
}

int ktraSCP(ItemType n) {
	if (n< 0) {
		return 0;
	}
	long long x = (long long)sqrt(n);
	return x * x == n;
}

int sumSCP(SList sl) {
	int sum = 0;
	for (SNode* p = sl.Head; p != NULL; p = p->Next) {
		if (ktraSCP(p->Info)) {
			sum += p->Info;
		}
	}
	return sum;
}

int timMin(SList sl) {
	if (isEmpty(sl) == 1) {
		printf("\nDanh sach rong");
		return -1;
	}
	int min = sl.Head->Info;
	for (SNode* p = sl.Head; p = NULL; p = p->Next) {
		if (p->Info < min) {
			min = p->Info;
		}
	}
	return min;
}

int timMax(SList sl) {
	if (isEmpty(sl) == 1) {
		printf("\nDanh sach rong");
		return -1;
	}
	int max = sl.Head->Info;
	for (SNode* p = sl.Head; p = NULL; p = p->Next) {
		if (p->Info < max) {
			max = p->Info;
		}
	}
	return max;
}

int demGapDoi(SList sl) {
	int dem = 0;
	for (SNode* p = sl.Head; p != NULL; p = p->Next) {
		if (p->Info > 2 * p->Next->Info) {
			dem++;
		}
	}
	return dem;
}

void addChanLe(SList& sl, SList& sl1, SList& sl2) {
	initSList(sl1);
	initSList(sl2);
	if (isEmpty(sl) == 1) {
		printf("\nDanh sach rong!");
		return;
	}
	SNode* p = sl.Head;
	for (; p != NULL; p = p->Next) {
		if (p->Info % 2 == 0) {
			addTail(sl1, p);
		}
		else {
			addTail(sl2, p);
		}
	}
}
void nhapFile(SList& sl) {
	char filename[100];
	getchar();
	printf("\nNhap vao ten file: ");
	fgets(filename, sizeof(filename), stdin);
	filename[strcspn(filename, "\n")] = '\0';
	printf("\nFile vua nhap: %s", filename);
	createSList_FromTextFile(sl, filename);
}
void menu() {
	printf("\n=================================");
	printf("\n**************MENU***************");
	printf("\n0. Thoat");
	printf("\n1. Nhap danh sach tu ban phim");
	printf("\n2. Tao danh sach tu dong");
	printf("\n3. Doc file");
	printf("\n4. Them dau");
	printf("\n5. Them cuoi");
	printf("\n6. Them p sau q");
	printf("\n7. Them p truoc q");
	printf("\n8. Tim kiem trong danh sach");
	printf("\n9. Sap xep danh sach: Chon Truc Tiep");
	printf("\n10. Sap xep danh sach: Doi cho truc tiep");
	printf("\n11. Dem so nguyen to");
	printf("\n12. Tong cac so chinh phuong");
	printf("\n13. Tim Min, Max");
	printf("\n14. Dem phan tu ma no lon gap hai lan phan tu phia sau no");
	printf("\n15. Danh sach chua so chan va danh sach chua so le");
	printf("\n=================================");
}
void process() {
	int chon;
	ItemType x;
	SNode* p, * q;
	SList sl, sl1, sl2;
	initSList(sl);
	do {
		menu();
		do {
			printf("\nChon chuc nang: ");
			scanf("%d", &chon);
		} while (chon < 0 || chon>15);
		switch (chon) {
		case 1:{
			createSList_InputByHand(sl);
			showSList(sl);
			break;
		}
		case 2: {
			createSList_Random(sl);
			showSList(sl);
			break;
		}
		case 3: {
			nhapFile(sl);
			showSList(sl);
			break;
		}
		case 4: {
			printf("\nNhap phan tu muon them dau");
			scanf("%d", &x);
			p = createSNode(x);
			addHead(sl, p);
			showSList(sl);
			break;
		}
		case 5: {
			printf("\nNhap phan tu muon them cuoi");
			scanf("%d", &x);
			p = createSNode(x);
			addTail(sl, p);
			showSList(sl);
			break;
		}
		case 6: {
			printf("\nNhap phan tu q de them sau: ");
			scanf("%d", &x);
			printf("\nNhap phan tu p de them sau q: ");
			scanf("%d", &x);
			p = createSNode(x);
			q = createSNode(x);
			addAfter(sl, q, p);
			showSList(sl);
			break;
		}
		case 7: {
			printf("\nNhap phan tu q de them truoc: ");
			scanf("%d", &x);
			printf("\nNhap phan tu p de them truoc q: ");
			scanf("%d", &x);
			p = createSNode(x);
			q = createSNode(x);
			addAfter(sl, q, p);
			showSList(sl);
			break;
		}
		case 8: {
			printf("\nNhap vao phan tu can tim kiem: ");
			scanf("%d", &x);
			p = createSNode(x);
			if (p != NULL) {
				printf("\Tim thay phan tu %d trong danh sach", x);
			}
			else {
				printf("\nKhong tim thay phan tu trong danh sach");
			}
			break;
		}
		case 9: {
			printf("\nMang truoc khi sap xep: ");
			showSList(sl);
			printf("\nMang sau khi sap xep: ");
			sortSList_ChonTrucTiep(sl);
			showSList(sl);
			break;
		}
		case 10: {
			printf("\nMang truoc khi sap xep: ");
			showSList(sl);
			printf("\nMang sau khi sap xep: ");
			sortSList_ChonTrucTiep(sl);
			showSList(sl);
			break;
		}
		case 11: {
			int kq1 = demSNT(sl);
			if (kq1 != 0) {
				printf("\nCo %d so nguyen to trong danh sach", kq1);
			}
			else {
				printf("\nTrong danh sach khong co so nguyen to");
			}
			break;
		}
		case 12: {
			int kq2 = sumSCP(sl);
			if (kq2 > 0) {
				printf("\nTong cac so chinh phuong = %d", kq2);
			}
			else {
				printf("\nDanh sach khong so chinh phuong");
			}
			break;
		}
		case 13: {
			printf("\nMin = %d", timMin(sl));
			printf("\nMax = %d", timMax(sl));
			break;
		case 14:
			int k = demGapDoi(sl);
			if (k != 0) {
				printf("\nCo %d phan tu thoat man dieu kien", k);
			}
			else {
				printf("\nKhong co phan tu thoat dieu kien");
			}
			break;
		}
		case 15: {
			addChanLe(sl, sl1, sl2);
			showSList(sl1);
			showSList(sl2);
			break;
		}
		}
	}while (chon != 0);
}
void main() {
	process();
}