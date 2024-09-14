#pragma once
#include <iostream>
#include <cstring>

using namespace std;

class dtb
{
protected:
	char MaHD[10];
	char MaSP[10];
	int sl;
	int64_t dg;
	int64_t tt;
public:
	dtb() {	};
	dtb(char mahd[], char masp[], int sl, int64_t dg) {
		strcpy(MaHD, mahd);
		strcpy(MaSP, masp);
		this->sl = sl;
		this->dg = dg;
		tt = sl * dg;
	}

	void setmahd(char mahd[]) {
		strcpy(MaHD, mahd);
	}
	void setmasp(char masp[]) {
		strcpy(MaSP, masp);
	}
	void setsl(int sl) {
		this->sl = sl;
		tt = sl * dg;
	}
	void setdg(int64_t dg) {
		this->dg = dg;
		tt = sl * dg;
	}

	void getmahd(char mahd[]) {
		strcpy(mahd, MaHD);
	}
	void getmasp(char masp[]) {
		strcpy(masp, MaSP);
	}
	int getsl() {
		return sl;
	}
	int64_t getdg() {
		return dg;
	}
	int64_t gettt() {
		return tt;
	}

	void display() {
		wcout << '\t' << MaSP << '\t' << sl << '\t' << dg;
	}
};