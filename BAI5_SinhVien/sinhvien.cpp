#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct DiemMH {
	float DTL, DCK, DTB;
};
typedef char KeyType;
struct KetQua {
	KeyType MaMH[11];
	char TenMH[50];
	int soTC;
	DiemMH Diem;
};
struct SNodeKQ {
	KetQua Info;
	SNodeKQ* Next;
};
struct SlistKQ {
	SNodeKQ* Head;
	SNodeKQ* Tail;
};
struct SinhVien {
	KeyType MaSV[11];
	char HoDem[25];
	char ten[8];
	SlistKQ diemKQ;
};
typedef SinhVien ItemType;
struct SNode {
	ItemType Info;
	SNode* Next;
};
struct SList {
	SNode* Head;
	SNode* Tail;
};