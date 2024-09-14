#include "detailbill.cpp"

class outdetail : public dtb
{
public:
	outdetail () : dtb() { };
	outdetail(char MaHD[], char MaSP[], int sl, int64_t dg, char TenKH[]) : dtb(MaHD, MaSP, sl, dg) {
		strcpy(this->TenKH, TenKH);
	}

	void settenkh(char tenkh[]) {
		strcpy(TenKH, tenkh);
	}
	void settensp(char tensp[]) {
		strcpy(this->tensp, tensp);
	}

	void gettenkh(char tenkh[]) {
		strcpy(tenkh, TenKH);
	}
	void gettensp(char tensp[]) {
		strcpy(tensp, this->tensp);
	}
	void NhapTT() {
		wcout << L"S\u1ED1 l\u01B0\u1EE3ng: "; cin >> sl;
		while (sl <= 0)
		{
			wcout << L"Nh\u1EADp l\u1EA1i s\u1ED1 l\u01B0\u1EE3ng: "; cin >> sl;
		}
		wcout << L"\u0110\u01A1n gi\u00E1: "; cin >> dg;
		while (dg <= 0)
		{
			wcout << L"Nh\u1EADp l\u1EA1i \u0111\u01A1n gi\u00E1: "; cin >> dg;
		}
		tt = sl * dg;
	}

	void display() {
		wcout << '\t' << TenKH << "\t\t" << MaSP << "\t\t" << tensp << "\t\t" << sl << "\t\t" << dg << "\t\t" << tt << endl;
	}
private:
	char TenKH[40];
	char tensp[80];
};
