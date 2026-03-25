#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
struct BaiHat {
	char tenBH[51];
	char tacGia[41];
	char caSi[41];
	int thoiLuong;
};
typedef BaiHat ItemType;
struct SNode {
	ItemType Info;
	SNode* Next;
};
struct SList {
	SNode* Head;
	SNode* Tail;
};
void initSList(SList& sl) {
	sl.Head = sl.Tail = NULL;
}
int isEmpty(SList sl) {
	if (sl.Head == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
SNode* createSNode(ItemType x) {
	SNode* p = new SNode;
	if (p == NULL) return NULL;
	p->Info = x;
	p->Next = NULL;
	return p;
}

//1.Nhap va xuat 1 bai hat
void nhapThongTinBaiHat(ItemType& bh) {
	getchar();
	printf("\nNhap vao ten bai hat: ");
	fgets(bh.tenBH, 51, stdin);
	bh.tenBH[strcspn(bh.tenBH, "\n")] = 0;

	printf("\nNhap vao ten tac gia: ");
	fgets(bh.tacGia, 41, stdin);
	bh.tacGia[strcspn(bh.tacGia, "\n")] = 0;

	printf("\nNhap vao ten ca si:  ");
	fgets(bh.caSi, 41, stdin);
	bh.caSi[strcspn(bh.caSi, "\n")] = 0;


	printf("\nNhap vao thoi luong bai hat: ");
	scanf("%d", &bh.thoiLuong);
}
void xuatThongTinBaiHat(ItemType bh) {
	printf("\nTen bai hat: %s", bh.tenBH);
	printf("\nTac gia: %s", bh.tacGia);
	printf("\nCa si: %s", bh.caSi);
	printf("\nThoi Luong: %d", bh.thoiLuong);
}
//2. Nhap mot danh sach bai hat
void addTail(SList& sl, SNode* p) {
	if (p == NULL) return;
	if (isEmpty(sl) == 1) {
		sl.Head = sl.Tail = p;
	}
	else {
		sl.Tail->Next = p;
		sl.Tail = p;
	}
}
void nhapDanhSachBaiHat(SList& sl) {
	int n;
	do {
		printf("\nNhap vao so luong bai hat: ");
		scanf("%d", &n);
	} while (n <= 0);
	ItemType x;
	for (int i = 0; i < n; i++) {
		printf("\n============================================");
		printf("\nNhap vao thong tin cua bai hat thu %d", i + 1);
		nhapThongTinBaiHat(x);
		addTail(sl, createSNode(x));
	}
}
//3. Load mot danh sach bai hat tu file
void loadFileBaiHat(SList& sl) {
	initSList(sl);
	FILE* p = fopen("baihat.txt", "r");
	if (p == NULL) {
		printf("\nDoc file khong thanh cong!");
		return;
	}
	BaiHat bh;
	int n;
	fscanf(p, "%d\n", &n);
	for (int i = 0; i < n; i++) {
		fscanf(p, " %[^,],%[^,],%[^,],%d"
			, bh.tenBH
			, bh.tacGia
			, bh.caSi
			, &bh.thoiLuong);
		addTail(sl, createSNode(bh));
	}
	fclose(p);
	printf("\nDoc file thanh cong!");
}
//4. In danh sach cac bai hat ra man hinh
void showDanhSachBaiHat(SList sl) {
	SNode* p = sl.Head;
	printf("\n*Danh sach bai hat cua ban la*");
	while (p != NULL) {
		printf("\n======================================");
		xuatThongTinBaiHat(p->Info);
		p = p->Next;
	}
}
//5. Tong thoi gian nghe het playlist
int tongThoiGianNghe(SList sl) {
	int tong = 0;
	SNode* p = sl.Head;
	while (p != NULL) {
		tong += p->Info.thoiLuong;
		p = p->Next;
	}
	return tong;
}
//6. Them mot bai hat vao dau danh sach
void addHead(SList& sl, SNode* p) {
	if (p == NULL) return;
	if (isEmpty(sl) == 1) {
		sl.Head = sl.Tail = p;
	}
	else {
		p->Next = sl.Head;
		sl.Head = p;
	}
}
//7. Xoa mot bai hat ra khoi danh sach
void delHead(SList& sl) {
	if (isEmpty(sl) == 1) {
		return;
	}
	else {
		SNode* p = sl.Head;
		sl.Head = sl.Head->Next;
		delete p;
	}
}
void delAfter(SList& sl, SNode* q) {
	if (q == NULL || q->Next == NULL) {
		return;
	}
	SNode* p = q->Next;
	q->Next = p->Next;
	if (sl.Tail == p) {
		sl.Tail = q;
	}
	delete p;
}
void deleteBaiHatX(SList& sl, char tenXoa[]) {
	if (isEmpty(sl) == 1) {
		printf("\nDanh sach rong khong con gi de xoa");
		return;
	}
	SNode* p = sl.Head;
	SNode* q = sl.Tail;
	while ((p != NULL) && (_strcmpi(p->Info.tenBH, tenXoa) != 0)) {
		q = p;
		p = p->Next;
	}
	if (p == NULL) {
		return;
	}
	if (p == sl.Head) {
		delHead(sl);
	}
	else {
		delAfter(sl, q);
	}
}
//8. Kiem Tra Xem Bai Hat Co Trong Playlist Hay Khong
int searchBaiHat(SList sl, char tenTim[]) {
	if (isEmpty(sl) == 1) {
		return 0;
	}
	else {
		for (SNode* p = sl.Head; p != NULL; p = p->Next) {
			if (_strcmpi(p->Info.tenBH, tenTim) == 0) {
				return 1;
			}
		}
	}
	return 0;
}
//9. Sap xep thep tu dien
void sapXepTheoTuDien(SList sl) {
	for (SNode* p = sl.Head; p != NULL; p = p->Next) {
		for (SNode* q = p->Next; q != NULL; q = q->Next) {
			if (strcmp(p->Info.tenBH, q->Info.tenBH) > 0) {
				ItemType tmp = p->Info;
				p->Info = q->Info;
				q->Info = tmp;
			}
		}
	}
}
//10. Sap xep giam dan theo ten ca si
void sapXepTheoCaSi(SList sl) {
	for (SNode* p = sl.Head; p != NULL; p = p->Next) {
		for (SNode* q = p->Next; q != NULL; q = q->Next) {
			if (strcmp(p->Info.caSi, q->Info.caSi) < 0) {
				ItemType tmp = p->Info;
				p->Info = q->Info;
				q->Info = tmp;
			}
		}
	}
}
void menu() {
	printf("\n");
	printf("\n======================================");
	printf("\n	*MENU*					  ");
	printf("\n0. Exit");
	printf("\n1. Nhap vao mot bai hat va xuat thong tin bai hat ra man hinh");
	printf("\n2. Nhap mot danh sach bai hat tu ban phim");
	printf("\n3. Load file bai hat");
	printf("\n4. In danh sach bai hat");
	printf("\n5. Tong thoi gian nghe playlist");
	printf("\n6. Them mot bai hat vao dau danh sach");
	printf("\n7. Them mot bai hat vao cuoi danh sach");
	printf("\n8. Xoa mot bai hat co ten X");
	printf("\n9. Kiem tra xem mot bai hat co trong danh sach hay khong");
	printf("\n10. Sap xep theo thu tu tu dien cua ten bai hat");
	printf("\n11. Sap xep theo thu tu giam dan ten ca si");
	printf("\n12. Dua mot bai hat len dau");
}
void process() {
	int chon;
	SList sl;
	initSList(sl);
	ItemType bh;
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
				nhapThongTinBaiHat(bh);
				printf("\n*BAI HAT CUA BAN LA*");
				xuatThongTinBaiHat(bh);
				break;
			}
			case 2:
			{
				nhapDanhSachBaiHat(sl);
				break;
			}
			case 3:
			{
				loadFileBaiHat(sl);
				break;
			}
			case 4: 
			{
				showDanhSachBaiHat(sl);
				break;
			}
			case 5:
			{
				int tong = tongThoiGianNghe(sl);
				printf("\nTong thoi gian de nghe het playlist: %d phut %d giay", tong / 60, tong % 60);
				break;
			}
			case 6:
			{
				printf("\nNhap vao bai hat muon them dau: ");
				nhapThongTinBaiHat(bh);
				SNode* p = createSNode(bh);
				addHead(sl, p);
				printf("\nDanh sach sao khi them: ");
				showDanhSachBaiHat(sl);
				break;
			}
			case 7:
			{
				printf("\nNhap vao bai hat muon them cuoi: ");
				nhapThongTinBaiHat(bh);
				SNode* q = createSNode(bh);
				addTail(sl, q);
				showDanhSachBaiHat(sl);
				break;
			}
			case 8:
			{
				char tenXoa[51];
				getchar();
				printf("\nNhap vao ten bai hat can xoa: ");
				fgets(tenXoa, 51, stdin);
				tenXoa[strcspn(tenXoa, "\n")] = 0;
				deleteBaiHatX(sl, tenXoa);
				printf("\nDanh sach sau khi xoa");
				showDanhSachBaiHat(sl);
				break;
			}
			case 9:
			{
				char tenTim[51];
				printf("\nNhap ten bai hat can tim kiem: ");
				fgets(tenTim, 51, stdin);
				tenTim[strcspn(tenTim, "\n")] = 0;
				int kq = searchBaiHat(sl, tenTim);
				if (kq != 0) {
					printf("\nTim thay bai hat!");
				}
				else {
					printf("\nKhong tim thay bai hat");
				}
				break;
			}
			case 10:
			{
				sapXepTheoTuDien(sl);
				printf("\nDanh sach sau khi sap xep");
				showDanhSachBaiHat(sl);
				break;
			}
			case 11:
			{
				sapXepTheoCaSi(sl);
				printf("\nDanh sach sau khi sap xep");
				showDanhSachBaiHat(sl);
				break;
			}
		}
	} while (chon !=0);
}
int main() {
	process();
	_getch();
	return 1;
}
