#include <stdio.h>
#include <conio.h>
#include <string.h>
struct HocPhan {
	char maHP[21];
	char tenHP[41];
	int soTC;
	float DTL, DCK;
	float diemHP;
};
struct NodeHP {
	HocPhan Info;
	NodeHP* Next;
};
struct SinhVien {
	char hoDem[26];
	char tenSV[9];
	int namSinh;
	NodeHP* dsHP;
	float diemTB;
};
struct NodeSV {
	SinhVien Info;
	NodeSV* Next;
};