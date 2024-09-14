#include "detailbill.cpp"

class indetail : public dtb
{
public:
	indetail() : dtb() { };
	indetail(char MaHD[], char MaSP[], int sl, int64_t dg, char MaNCC[]) : dtb(MaHD, MaSP, sl, dg) {
		strcpy(this->MaNCC, MaNCC);
	}

	void setmancc(char mancc[]) {
		strcpy(MaNCC, mancc);
	}

	void getmancc(char mancc[]) {
		strcpy(mancc, MaNCC);
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
		wcout << '\t' << MaSP << "\t\t" << sl << "\t\t" << dg << "\t\t" << tt << "\t\t" << MaNCC << endl;
	}
private:
	char MaNCC[10];
};
