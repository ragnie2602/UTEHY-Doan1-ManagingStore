#include "ThongTin.cpp"

class SanPham : public ThongTin
{
private:
	int SLSP;
	int64_t DGSP;
	char MaNCC[10];
	
public:
	SanPham() { };
	SanPham(char Ma[], char Ten[], int SLSP, int64_t DGSP, char MaNCC[]) : ThongTin(Ma, Ten) {
		this->SLSP = SLSP;
		this->DGSP = DGSP;
		strcpy(this->MaNCC, MaNCC);
	};
	
	void setslsp(int slsp) {
		this->SLSP = slsp;
	};
	void setdgsp(int64_t dgsp) {
		this->DGSP = dgsp;
	};
	void setmancc(char MaNCC[]) {
		strcpy(this->MaNCC, MaNCC);
	};

	int getslsp() {
		return SLSP;
	};
	int64_t getdgsp() {
		return DGSP;
	};
	void getmancc(char MaNCC[]) {
		strcpy(MaNCC, this->MaNCC);
	};

	void NhapThongTin()
	{
		wcout << L"Nh\u1EADp t\u00EAn s\u1EA3n ph\u1EA9m: ";cin.getline(Ten, 60);
		while (strlen(Ten) == 0)
		{
			wcout << L"T\u00EAn s\u1EA3n ph\u1EA9m kh\u00F4ng \u0111\u01B0\u1EE3c \u0111\u1EC3 tr\u1ED1ng. Nh\u1EADp l\u1EA1i: "; cin.getline(this->Ten, 60);
		}
		wcout << L"S\u1ED1 l\u01B0\u1EE3ng s\u1EA3n ph\u1EA9m: ";cin >> SLSP;
		while (SLSP <= 0)
		{
			wcout << L"Nh\u1EADp l\u1EA1i s\u1ED1 l\u01B0\u1EE3ng s\u1EA3n ph\u1EA9m: "; cin >> SLSP;
		}
		wcout << L"\u0110\u01A1n gi\u00E1: ";cin >> DGSP;
		while (DGSP <= 0)
		{
			wcout << L"Nh\u1EADp l\u1EA1i \u0111\u01A1n gi\u00E1 s\u1EA3n ph\u1EA9m: "; cin >> DGSP;
		}
	};

	void display() {
		wcout <<'\t'<< Ma << "\t\t"  << Ten << "\t\t" << SLSP << "\t\t" << DGSP << "\t\t" << MaNCC << endl;
	}
};
