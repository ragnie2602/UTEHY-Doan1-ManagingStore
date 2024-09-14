#include "Thongtin.cpp"

class NCC : public ThongTin
{
private:
	char sdt[11];
	char diachi[100];

public:
	NCC() {};
	NCC(char ma[], char ten[], char sdt[], char diachi[]) : ThongTin(ma, ten) {
		while (!checksdt(sdt)) {
			cin >> sdt;
		}
		strcpy(this->sdt, sdt);
		strcpy(this->diachi, diachi);
	};

	bool checksdt(char s[]) {
		if (s[0] != '0') return false;
		if (strlen(s) != 10) return false;
		for (int i = 1; i < strlen(s); i++) if (s[i] < 48 || s[i] > 57) return false;
		return true;
	}

	void setsdt(char sdt[]) {
		while (!checksdt(sdt)) {
			cin >> sdt;
		}
		strcpy(this->sdt, sdt);
	}
	void setdiachi(char diachi[]) {
		strcpy(this->diachi, diachi);
	}
	
	void getsdt(char sdt[]) {
		strcpy(sdt, this->sdt);
	}
	void getdiachi(char diachi[]) {
		strcpy(diachi, this->diachi);
	}
	
	void importdata() {
		_setmode(_fileno(stdout), _O_U16TEXT);
		wcout << L"Nh\u1EADp v\u00E0o t\u00EAn nh\u00E0 cung c\u1EA5p: "; cin.getline(this->Ten, 80);
		while (strlen(Ten) == 0)
		{
			wcout << L"T\u00EAn nh\u00E0 cung c\u1EA5p kh\u00F4ng \u0111\u01B0\u1EE3c \u0111\u1EC3 tr\u1ED1ng. Nh\u1EADp l\u1EA1i: "; cin.getline(this->Ten, 80);
		}
		wcout << L"Nh\u1EADp v\u00E0o s\u1ED1 \u0111i\u1EC7n tho\u1EA1i nh\u00E0 cung c\u1EA5p: "; cin >> this->sdt;
		while (!checksdt(this->sdt))
		{
			wcout << L"Nh\u1EADp l\u1EA1i s\u1ED1 \u0111i\u1EC7n tho\u1EA1i: "; cin >> this->sdt;
		}
		while (getchar() != '\n');
		wcout << L"Nh\u1EADp v\u00E0o \u0111\u1ECBa ch\u1EC9: "; cin.getline(this->diachi, 100);
		while (strlen(diachi) == 0)
		{
			wcout << L"\u0110\u1ECBa ch\u1EC9 kh\u00F4ng \u0111\u01B0\u1EE3c \u0111\u1EC3 tr\u1ED1ng. Nh\u1EADp l\u1EA1i: "; cin.getline(this->diachi, 100);
		}
	}
	
	void display() {
		wcout << '\t' << Ma << "\t\t" << Ten << '\t' << sdt << '\t' << diachi <<  "\t"  <<endl;
	
	}
};
