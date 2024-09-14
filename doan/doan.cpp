#include "SanPham.cpp"
#include "Nhacungcap.cpp"
#include "HoaDon.cpp"
#include "indetail.cpp"
#include "outdetail.cpp"
#include<fstream>
#include<vector>
#include<conio.h>
#include<Windows.h>
#include<fcntl.h>
#include<io.h>

using namespace std;

//graphic
void setcolor(int code) {
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, code);
}
//product
bool showproduct(string s) {
	fstream Data, subData;
	SanPham sp;
	Data.open(s, ios::in | ios::binary);
	if (!Data.is_open()) {
		wcout << L"Ch\u01B0a s\u1EA3n ph\u1EA9m n\u00E0o \u0111\u01B0\u1EE3c nh\u1EADp v\u00E0o!" << endl;
		return false;
	}
	wcout << L"                                 DANH S\u00C1CH S\u1EA2N PH\u1EA8M                          \n";
	wcout << L"_____________________________________________________________________________________________\n";
	wcout << L"\tM\u00E3 SP\t\tT\u00EAn SP\t\t\tS\u1ED1 l\u01B0\u1EE3ng\t\u0110\u01A1n gi\u00E1\t\tM\u00E3 NCC\n";
	wcout << L"_____________________________________________________________________________________________\n";
	
	Data.read((char*)&sp, sizeof(SanPham));
	while (!Data.eof()) {
		sp.display();
		Data.read((char*)&sp, sizeof(SanPham));
	};
	Data.close(); wcout << endl;
	return true;
}

void importproduct(string s) {
	fstream Data, subData;
	bool b = true;
	char ma[10], subma[10];
	SanPham sp; NCC ncc;

	subData.open("producer.dat", ios::in | ios::binary);
	if (!subData.is_open()) {
		wcout << L"Ch\u01B0a c\u00F3 d\u1EEF li\u1EC7u v\u1EC1 nh\u00E0 cung c\u1EA5p, nh\u1EADp nh\u00E0 cung c\u1EA5p tr\u01B0\u1EDBc!" << endl;
		goto afterfence2;
	}
	wcout << L"Nh\u1EADp m\u00E3 s\u1EA3n ph\u1EA9m: "; cin.seekg(cin.end); cin.getline(ma, 10);
	while (strlen(ma) == 0)
	{
		wcout << L"M\u00E3 s\u1EA3n ph\u1EA9m kh\u00F4ng \u0111\u01B0\u1EE3c r\u1ED7ng, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
	}

	Data.open(s, ios::in | ios::binary);
	if (!Data.is_open()) goto afterfence1;

	while (true) {
		b = true; Data.seekg(ios::beg);
		Data.read((char*)&sp, sizeof(SanPham));
		while (!Data.eof()) {
			sp.getma(subma);
			if (strcmp(subma, ma) == 0) {
				wcout << L"Y\u00EAu c\u1EA7u nh\u1EADp l\u1EA1i m\u00E3: "; cin.getline(ma, 10);
				while (strlen(ma) == 0)
				{
					wcout << L"M\u00E3 s\u1EA3n ph\u1EA9m kh\u00F4ng \u0111\u01B0\u1EE3c r\u1ED7ng, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
				}
				b = false;
				break;
			}
			Data.read((char*)&sp, sizeof(SanPham));
		}
		if (b) break;
	}
afterfence1:
	Data.close();
	sp.setma(ma);

	sp.NhapThongTin();

	wcout << L"Nh\u1EADp v\u00E0o m\u00E3 nh\u00E0 cung c\u1EA5p: "; cin.seekg(cin.end); cin.getline(ma, 10);
	while (true)
	{
		b = false;

		subData.read((char*)&ncc, sizeof(NCC));
		while (!subData.eof())
		{
			ncc.getma(subma);
			if (strcmp(subma, ma) == 0) {
				b = true;
				sp.setmancc(ma);
				break;
			}
			subData.read((char*)&ncc, sizeof(NCC));
		}
		if (b) break;
		else {
			wcout << L"M\u00E3 nh\u00E0 cung c\u1EA5p kh\u00F4ng t\u1ED3n t\u1EA1i, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
			subData.clear(); subData.seekg(ios::beg);
		}
	}

	Data.open(s, ios::out | ios::app | ios::binary);
	Data.write((char*)&sp, sizeof(SanPham));
	Data.close();
afterfence2:;
}

void deleteproduct(string s) {
	fstream Data;
	SanPham sp;
	char ma[10], subma[10];
	vector<SanPham> list;

	cin.seekg(cin.end);
	wcout << L"Nh\u1EADp v\u00E0o m\u00E3 s\u1EA3n ph\u1EA9m c\u1EA7n x\u00F3a: "; cin.getline(subma, 10);

	Data.open(s, ios::in | ios::binary);

	Data.read((char*)&sp, sizeof(SanPham));
	while (Data.eof() == false) {
		sp.getma(ma);
		if (strcmp(ma, subma) != 0) list.push_back(sp);
		Data.read((char*)&sp, sizeof(SanPham));
	}
	Data.close();

	Data.open(s, ios::out | ios::trunc | ios::binary);
	for (int i = 0; i < list.size(); i++) Data.write((char*)&list[i], sizeof(SanPham));
	Data.close();
}

void deleteproduct(string s, char cond[]) {
	fstream Data;
	SanPham sp;
	char subma[10];
	vector<SanPham> list;
	Data.open(s, ios::in | ios::binary);

	Data.read((char*)&sp, sizeof(SanPham));
	while (!Data.eof())
	{
		sp.getma(subma);
		if (strcmp(cond, subma) != 0) list.push_back(sp);
		Data.read((char*)&sp, sizeof(SanPham));
	}
	Data.close();

	Data.open(s, ios::out | ios::trunc | ios::binary);
	for (int i = 0; i < list.size(); i++) Data.write((char*)&list[i], sizeof(SanPham));
	Data.close();
}

void editproduct(string s) {
	int n = -1; bool b = false;
	char subma[10], ma[10];
	fstream Data, subData;
	SanPham sp; NCC ncc;

	cin.seekg(cin.end);
	wcout << L"Nh\u1EADp v\u00E0o m\u00E3 s\u1EA3n ph\u1EA9m c\u1EA7n thay \u0111\u1ED5i: "; cin.getline(subma, 10);

	Data.open(s, ios::in | ios::out | ios::binary); if (!Data.is_open()) {
		wcout << L"Ch\u01B0a c\u00F3 m\u00E3 s\u1EA3n ph\u1EA9m n\u00E0o \u0111\u01B0\u1EE3c nh\u1EADp v\u00E0o!" << endl;
		goto exit;
	}

	Data.read((char*)&sp, sizeof(SanPham));
	while (!Data.eof())
	{
		sp.getma(ma); n++;
		if (strcmp(subma, ma) == 0) {
			b = true;

			sp.NhapThongTin();
			subData.open("producer.dat", ios::in | ios::binary);
			wcout << L"Nh\u1EADp v\u00E0o m\u00E3 nh\u00E0 cung c\u1EA5p: "; cin.seekg(cin.end); cin.getline(ma, 10);
			while (true)
			{
				b = false;

				subData.read((char*)&ncc, sizeof(NCC));
				while (!subData.eof())
				{
					ncc.getma(subma);
					if (strcmp(subma, ma) == 0) {
						b = true;
						sp.setmancc(ma);
						break;
					}
					subData.read((char*)&ncc, sizeof(NCC));
				}

				if (b) {
					subData.close();
					break;
				}
				else {
					wcout << L"M\u00E3 nh\u00E0 cung c\u1EA5p kh\u00F4ng t\u1ED3n t\u1EA1i, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
					subData.clear(); subData.seekg(ios::beg);
				}
			}

			Data.seekp(n * sizeof(SanPham));
			Data.write((char*)&sp, sizeof(SanPham));
			break;
		}
		Data.read((char*)&sp, sizeof(SanPham));
	}
	Data.close();

	if (!b) wcout << L"Kh\u00F4ng t\u00ECm th\u1EA5y s\u1EA3n ph\u1EA9m c\u00F3 m\u00E3 n\u00E0y!" << endl; else wcout << L"\u0110\u00E3 thay \u0111\u1ED5i!" << endl;
exit:;
}

void searchproduct(string s) {
	int n = -1; bool b = false;
	fstream Data, subData;
	char subma[10], ma[10];
	SanPham sp;

	cin.seekg(cin.end);
	wcout << L"Nh\u1EADp v\u00E0o m\u00E3 s\u1EA3n ph\u1EA9m: "; cin.getline(subma, 10);

	Data.open(s, ios::in | ios::out | ios::binary); if (!Data.is_open()) {
		wcout << L"Ch\u01B0a c\u00F3 s\u1EA3n ph\u1EA9m n\u00E0o \u0111\u01B0\u1EE3c nh\u1EADp v\u00E0o!" << endl;
		goto exit;
	}

	Data.read((char*)&sp, sizeof(SanPham));
	while (!Data.eof())
	{
		sp.getma(ma); n++;
		if (strcmp(subma, ma) == 0) {
			b = true;
			wcout << L"_______________________________________________________________________________________________";
			wcout << L"\n\tM\u00E3 SP\t\tT\u00EAn SP\t\t\tS\u1ED1 l\u01B0\u1EE3ng\t\u0110\u01A1n gi\u00E1\t\tM\u00E3 NCC\n";
			wcout << L"_______________________________________________________________________________________________\n";
			sp.display();
			break;
		}
		Data.read((char*)&sp, sizeof(SanPham));
	}
	Data.close();
	if (!b) wcout << L"Kh\u00F4ng t\u00ECm th\u1EA5y s\u1EA3n ph\u1EA9m c\u00F3 m\u00E3 n\u00E0y!" << endl;
exit:;
}
//producer
bool showproducer(string s) {
	fstream Data;
	NCC ncc;

	Data.open(s, ios::in | ios::binary); if (!Data.is_open()) {
		wcout << L"Ch\u01B0a c\u00F3 th\u00F4ng tin n\u00E0o v\u1EC1 nh\u00E0 cung c\u1EA5p!" << endl;
		return false;
	}
	wcout << L"                       DANH S\u00C1CH NH\u00C0 CUNG C\u1EA4P                          \n";
	wcout << L"_______________________________________________________________________\n";
	wcout << L"\tM\u00E3 nh\u00E0 CC\tT\u00EAn nh\u00E0 CC\tS\u1ED1 \u0111i\u1EC7n tho\u1EA1i\t\u0110\u1ECBa ch\u1EC9         \n";
	wcout << L"_______________________________________________________________________\n";
	

	Data.read((char*)&ncc, sizeof(NCC));
	while (!Data.eof())
	{
		
		ncc.display();
		
		Data.read((char*)&ncc, sizeof(NCC));
		
	};
	Data.close(); wcout << endl;
	
	return true;
}

void importproducer(string s) {
	char c, ma[10], subma[10]; bool b = true;
	fstream Data;
	NCC ncc;

	Data.open(s, ios::binary | ios::app | ios::in);
	Data.seekg(ios::beg);

	wcout << L"Nh\u1EADp m\u00E3 nh\u00E0 cung c\u1EA5p: "; cin.seekg(cin.end); cin.getline(ma, 10);
	while (strlen(ma) == 0)
	{
		wcout << L"M\u00E3 nh\u00E0 cung c\u1EA5p kh\u00F4ng \u0111\u01B0\u1EE3c tr\u1ED1ng, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
	}

	while (true) {
		b = true;
		Data.seekg(ios::beg);
		while (!Data.eof())
		{
			Data.read((char*)&ncc, sizeof(NCC));
			ncc.getma(subma);
			if (strcmp(subma, ma) == 0) {
				wcout << L"Y\u00EAu c\u1EA7u nh\u1EADp l\u1EA1i m\u00E3: "; cin.getline(ma, 10);
				while (strlen(ma) == 0)
				{
					wcout << L"M\u00E3 nh\u00E0 cung c\u1EA5p kh\u00F4ng \u0111\u01B0\u1EE3c tr\u1ED1ng, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
				}
				b = false;
				break;
			}
		}
		if (b) break;
	}
	Data.close();

	ncc.setma(ma); ncc.importdata();

	Data.open(s, ios::out | ios::app | ios::binary);
	Data.write((char*)&ncc, sizeof(NCC));
	Data.close();
};

void deleteproducer(string s) {
	char subma[10], ma[10];
	fstream Data;
	NCC ncc;
	vector<NCC> list;

	wcout << L"Nh\u1EADp v\u00E0o m\u00E3 nh\u00E0 cung c\u1EA5p c\u1EA7n x\u00F3a: "; cin.seekg(cin.end); cin.getline(subma, 10);

	Data.open(s, ios::in | ios::binary);
	Data.read((char*)&ncc, sizeof(NCC));
	while (Data.eof() == false) {
		ncc.getma(ma);
		cout << ma <<endl;
		if (strcmp(ma, subma) != 0) list.push_back(ncc);
		Data.read((char*)&ncc, sizeof(ncc));
	}
	Data.close();

	Data.open(s, ios::out | ios::trunc | ios::binary);
	for (int i = 0; i < list.size(); i++) Data.write((char*)&list[i], sizeof(NCC));
	Data.close();
}

void editproducer(string s) {
	int n = -1; bool b = false;
	char subma[10], ma[10];
	NCC ncc;
	fstream Data;

	wcout << L"Nh\u1EADp v\u00E0o m\u00E3 nh\u00E0 cung c\u1EA5p c\u1EA7n thay \u0111\u1ED5i: "; cin.seekg(cin.end); cin.getline(subma, 10);
	
	Data.open(s, ios::in | ios::out | ios::binary);

	Data.read((char*)&ncc, sizeof(NCC));
	while (!Data.eof())
	{
		ncc.getma(ma); n++;
		if (strcmp(subma, ma) == 0) {
			b = true;

			ncc.importdata();

			Data.seekp(n * sizeof(NCC));
			Data.write((char*)&ncc, sizeof(NCC));
			break;
		}
		Data.read((char*)&ncc, sizeof(NCC));
	}
	Data.close();

	if (!b) wcout << L"Kh\u00F4ng t\u00ECm th\u1EA5y nh\u00E0 cung c\u1EA5p c\u00F3 m\u00E3 n\u00E0y!" << endl; else wcout << L"\u0110\u00E3 thay \u0111\u1ED5i!" << endl;
}

void searchproducer(string s) {
	int n = -1; bool b = false;
	char subma[10], ma[10];
	NCC ncc;
	fstream Data;

	Data.open(s, ios::in | ios::out | ios::binary); if (!Data.is_open()) {
		wcout << L"Ch\u01B0a c\u00F3 th\u00F4ng tin nh\u00E0 cung c\u1EA5p n\u00E0o!" << endl;
		goto exit;
	}

	wcout << L"Nh\u1EADp v\u00E0o m\u00E3 nh\u00E0 cung c\u1EA5p: "; cin.seekg(cin.end); cin.getline(subma, 10);

	Data.read((char*)&ncc, sizeof(NCC));
	while (!Data.eof())
	{
		ncc.getma(ma); n++;
		if (strcmp(subma, ma) == 0) {
			b = true;
			wcout << L"_______________________________________________________________________";
			wcout << L"\n\tM\u00E3 nh\u00E0 CC\tT\u00EAn nh\u00E0 CC\tS\u1ED1 \u0111i\u1EC7n tho\u1EA1i\t\u0110\u1ECBa ch\u1EC9\n";
			wcout << L"_______________________________________________________________________\n";
			ncc.display();
			break;
		}
		Data.read((char*)&ncc, sizeof(NCC));
	}
	Data.close();
	if (!b) wcout << L"Kh\u00F4ng t\u00ECm th\u1EA5y nh\u00E0 cung c\u1EA5p c\u00F3 m\u00E3 n\u00E0y!" << endl;
exit:;
}

//input bill
void showindetail(string s, char cond[]) {
	fstream Data;
	indetail idt;
	char subma[10];

	Data.open(s, ios::in | ios::binary | ios::app);
	Data.clear(); Data.seekg(ios::beg);
	wcout << L"____________________________________________________________________________________\n";
	wcout << '\t' << L"M\u00E3 s\u1EA3n ph\u1EA9m" << '\t' << L"S\u1ED1 l\u01B0\u1EE3ng" << '\t' << L"\u0110\u01A1n gi\u00E1" << "\t\t" << L"Th\u00E0nh ti\u1EC1n" << '\t' << L"M\u00E3 NCC" << endl;
	wcout << L"____________________________________________________________________________________\n";
	Data.read((char*)&idt, sizeof(indetail));
	while (!Data.eof()) {
		idt.getmahd(subma);
		if (strcmp(subma, cond) == 0) idt.display();
		Data.read((char*)&idt, sizeof(indetail));
	}

	Data.close();
}

void importindetail(string s, char mahd[]) {
	indetail idt; idt.setmahd(mahd); SanPham sp;
	bool b = true; int n = 0; char c, ma[10], subma[10];
	fstream Data, subData;

	system("cls"); wcout << L"Nh\u1EADp th\u00EAm 1 chi ti\u1EBFt h\u00F3a \u0111\u01A1n: " << endl;
	wcout << L"Nh\u1EADp m\u00E3 s\u1EA3n ph\u1EA9m: "; cin.seekg(cin.end); cin.getline(ma, 10);
	while (strlen(ma) == 0)
	{
		wcout << L"M\u00E3 s\u1EA3n ph\u1EA9m kh\u00F4ng \u0111\u01B0\u1EE3c tr\u1ED1ng, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
	}
	Data.open("product.dat", ios::in | ios::binary); if (!Data.is_open()) goto afterfence1;
	while (true)
	{
		b = false; n = 0;
		Data.read((char*)&sp, sizeof(SanPham));
		while (!Data.eof())
		{
			sp.getma(subma);
			if (strcmp(subma, ma) == 0) {
				idt.setmasp(ma);
				b = true;
				break;
			}
			Data.read((char*)&sp, sizeof(SanPham)); n++;
		}
		if (b) {
			Data.close();
			sp.getmancc(subma);
			idt.setmancc(subma);
			idt.NhapTT();
			Data.open("product.dat", ios::in | ios::out | ios::binary);
			Data.seekg(n * sizeof(SanPham)); Data.read((char*)&sp, sizeof(SanPham));
			sp.setslsp(sp.getslsp() + idt.getsl());
			sp.setdgsp(idt.getdg());
			Data.seekp(n * sizeof(SanPham)); Data.write((char*)&sp, sizeof(SanPham));
			Data.close();
			break;
		}
		else
		{
		afterfence1:
			wcout << L"Kh\u00F4ng c\u00F3 m\u00E3 s\u1EA3n ph\u1EA9m n\u00E0y, nh\u1EADp l\u1EA1i (N) hay th\u00EAm s\u1EA3n ph\u1EA9m m\u1EDBi (Y)? \n"; c = _getch();
			if (c == 'y' || c == 'Y') {
				Data.close();
				importproduct("product.dat");

				Data.open("product.dat", ios::in | ios::binary); while (!Data.eof()) Data.read((char*)&sp, sizeof(SanPham)); Data.close();

				sp.getma(ma); idt.setmasp(ma);
				idt.setsl(sp.getslsp());
				idt.setdg(sp.getdgsp());
				sp.getmancc(ma); idt.setmancc(ma);
				break;
			}
			else
			{
				wcout << L"Nh\u1EADp l\u1EA1i m\u00E3:"; cin.getline(ma, 10);
				Data.clear(); Data.seekg(ios::beg);
			}
		}
	}
	subData.open(s, ios::out | ios::binary | ios::app);
	subData.write((char*)&idt, sizeof(indetail));
	subData.close();
}

void editindetail(string s, char cond[]) {
	bool b = false; int64_t pos1 = 0, pos2 = 0, change = 0;
	char subma[10], ma[10], subma1[10];
	fstream Data, subData;
	SanPham sp; indetail idt;

	wcout << L"Nh\u1EADp m\u00E3 s\u1EA3n ph\u1EA9m: "; cin.seekg(cin.end); cin.getline(ma, 10);
	subData.open("product.dat", ios::in | ios::out | ios::binary);
	while (true)
	{
		if (strlen(ma) == 0)
		{
			wcout << L"M\u00E3 s\u1EA3n ph\u1EA9m kh\u00F4ng \u0111\u01B0\u1EE3c tr\u1ED1ng, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
			continue;
		}
		b = false; pos1 = 0;
		subData.read((char*)&sp, sizeof(SanPham));
		while (!subData.eof())
		{
			sp.getma(subma);
			if (strcmp(subma, ma) == 0) {
				idt.setmasp(ma);
				b = true;
				break;
			}
			subData.read((char*)&sp, sizeof(SanPham)); pos1++;
		}
		if (b) break;
		else
		{
			wcout << L"Kh\u00F4ng c\u00F3 m\u00E3 s\u1EA3n ph\u1EA9m n\u00E0y, nh\u1EADp l\u1EA1i:"; cin.getline(ma, 10);
			subData.clear(); subData.seekg(ios::beg);
		}
	}

	b = false;
	Data.open(s, ios::in | ios::out | ios::binary);
	Data.seekg(ios::beg); Data.read((char*)&idt, sizeof(indetail));
	while (!Data.eof())
	{
		idt.getmahd(subma); idt.getmasp(subma1);
		if (strcmp(subma, cond) == 0 && strcmp(subma1, ma) == 0) {
			b = true; change = idt.getsl();
			idt.NhapTT();
			sp.setdgsp(idt.getdg());
			change = idt.getsl() - change; sp.setslsp(sp.getslsp() + change);
			Data.seekp(pos2 * sizeof(indetail));
			Data.write((char*)&idt, sizeof(indetail));
			break;
		}
		Data.read((char*)&idt, sizeof(indetail)); pos2++;
	}
	Data.close();
	if (b) wcout << L"\u0110\u00E3 thay \u0111\u1ED5i.\n"; else wcout << L"Kh\u00F4ng c\u00F3 m\u00E3 s\u1EA3n ph\u1EA9m n\u00E0y trong h\u00F3a \u0111\u01A1n " << cond << endl;

	subData.seekp(pos1 * sizeof(SanPham));
	subData.write((char*)&sp, sizeof(SanPham));
	subData.close();
}

void deleteindetail(string s, char cond[]) {
	bool b = true;
	char subma1[10], ma[10], subma[10];
	fstream Data;
	indetail idt;
	vector<indetail> list;

	wcout << L"Nh\u1EADp m\u00E3 s\u1EA3n ph\u1EA9m: "; cin.seekg(cin.end); cin.getline(ma, 10);
	Data.open(s, ios::in | ios::binary);
	Data.seekg(ios::beg); Data.read((char*)&idt, sizeof(indetail));
	while (!Data.eof())
	{
		idt.getmahd(subma); idt.getmasp(subma1);
		if (strcmp(subma, cond) != 0 || strcmp(subma1, ma) != 0) list.push_back(idt);
		Data.read((char*)&idt, sizeof(indetail));
	}
	Data.close();
	if (b) {
		Data.open(s, ios::out | ios::binary | ios::trunc);
		for (int i = 0; i < list.size(); i++) Data.write((char*)&list[i], sizeof(indetail));
		wcout << L"\u0110\u00E3 thay \u0111\u1ED5i!\n" << endl;
	}
	else wcout << L"Kh\u00F4ng c\u00F3 m\u00E3 s\u1EA3n ph\u1EA9m n\u00E0y trong h\u00F3a \u0111\u01A1n!" << cond << endl;
	Data.close();
}

//outputbill
void showoutdetail(string s, char cond[]) {
	fstream Data;
	outdetail odt;
	char subma[10];

	Data.open(s, ios::in | ios::binary | ios::app);
	Data.clear(); Data.seekg(ios::beg);
	wcout << L"__________________________________________________________________________________________________________________________\n";
	wcout << '\t' << L"T\u00EAn kh\u00E1ch h\u00E0ng" << "\t\t" << L"M\u00E3 s\u1EA3n ph\u1EA9m" << '\t' << L"T\u00EAn s\u1EA3n ph\u1EA9m" << "\t\t" << L"S\u1ED1 l\u01B0\u1EE3ng" << '\t' << L"\u0110\u01A1n gi\u00E1" << "\t\t" << L"Th\u00E0nh ti\u1EC1n" << endl;
	wcout << L"__________________________________________________________________________________________________________________________\n";
	
	Data.read((char*)&odt, sizeof(outdetail));
	while (!Data.eof()) {
		odt.getmahd(subma);
		if (strcmp(subma, cond) == 0) odt.display();
		Data.read((char*)&odt, sizeof(outdetail));
	}

	Data.close();
}

void importoutdetail(string s, char mahd[], char name[]) {
	fstream subData, Data;
	outdetail odt; odt.setmahd(mahd); SanPham sp;
	char c, nameprod[80], ma[10], subma[10];
	bool b = true; int n = 0; int64_t num;

	Data.open("product.dat", ios::in | ios::binary);
	if (!Data.is_open())
	{
		wcout << L"Ch\u01B0a c\u00F3 s\u1EA3n ph\u1EA9m n\u00E0o trong kho!" << endl;
		goto exiting;
	}
	subData.open(s, ios::out | ios::binary | ios::app);
	system("cls"); wcout << L"Nh\u1EADp th\u00EAm 1 chi ti\u1EBFt h\u00F3a \u0111\u01A1n: " << endl;
	wcout << L"Nh\u1EADp m\u00E3 s\u1EA3n ph\u1EA9m: "; cin.getline(ma, 10);
	while (strlen(ma) == 0)
	{
		wcout << L"M\u00E3 s\u1EA3n ph\u1EA9m kh\u00F4ng \u0111\u01B0\u1EE3c tr\u1ED1ng, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
	}
	while (true)
	{
		b = false; n = 0;
		Data.read((char*)&sp, sizeof(SanPham));
		while (!Data.eof())
		{
			sp.getma(subma);
			if (strcmp(subma, ma) == 0) {
				odt.setmasp(ma);
				sp.getten(nameprod);
				odt.settensp(nameprod);
				b = true;
				break;
			}
			Data.read((char*)&sp, sizeof(SanPham)); n++;
		}
		if (b) {
			Data.close();
			break;
		}
		else
		{
			wcout << L"Kh\u00F4ng c\u00F3 m\u00E3 s\u1EA3n ph\u1EA9m n\u00E0y, nh\u1EADp l\u1EA1i:"; cin.getline(ma, 10);
			Data.clear(); Data.seekg(ios::beg);
		}
	}

	odt.settenkh(name);
	do {
		wcout << L"S\u1ED1 l\u01B0\u1EE3ng: "; cin >> num;
		if (num <= 0) wcout << L"Nh\u1EADp l\u1EA1i ";
		else if (num > sp.getslsp()) wcout << L"Kh\u00F4ng \u0111\u1EE7 s\u1ED1 l\u01B0\u1EE3ng s\u1EA3n ph\u1EA9m \u0111\u1EC3 thanh to\u00E1n, nh\u1EADp l\u1EA1i ";
		else break;

	} while (true);
	odt.setsl(num);
	do {
		wcout << L"\u0110\u01A1n gi\u00E1: "; cin >> num;
		if (num < sp.getdgsp()) wcout << L"\u0110\u01A1n gi\u00E1 b\u00E1n ra n\u00EAn l\u1EDBn h\u01A1n \u0111\u01A1n gi\u00E1 m\u1EB7c \u0111\u1ECBnh c\u1EE7a s\u1EA3n ph\u1EA9m \u0111\u1EC3 tr\u00E1nh b\u1ECB l\u1ED7! Nh\u1EADp l\u1EA1i "; else break;
	} while (true);
	odt.setdg(num);

	Data.open("product.dat", ios::in | ios::out | ios::binary);
	Data.seekg(n * sizeof(SanPham)); Data.read((char*)&sp, sizeof(SanPham));
	sp.setslsp(sp.getslsp() - odt.getsl());
	if (sp.getslsp() > 0)
	{
		Data.seekp(n * sizeof(SanPham)); Data.write((char*)&sp, sizeof(SanPham));
		Data.close();
	}
	else
	{
		Data.close();
		sp.getma(ma);
		deleteproduct("product.dat", ma);
	}

	subData.write((char*)&odt, sizeof(outdetail));
	subData.close();
exiting:;
}

void editoutdetail(string s, char cond[]) {
	bool b = false, b1 = false; int64_t pos1 = 0, pos2 = 0, change = 0, n = 0;
	char subma1[10], subma[10], ma[10];
	fstream Data, subData;
	SanPham sp; outdetail odt;

	wcout << L"Nh\u1EADp m\u00E3 s\u1EA3n ph\u1EA9m: "; cin.seekg(cin.end); cin.getline(ma, 10);
	subData.open("product.dat", ios::in | ios::binary);
	while (strlen(ma) == 0)
	{
		wcout << L"M\u00E3 s\u1EA3n ph\u1EA9m kh\u00F4ng \u0111\u01B0\u1EE3c tr\u1ED1ng, nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
	}
	subData.read((char*)&sp, sizeof(SanPham));
	while (!subData.eof())
	{
		sp.getma(subma);
		if (strcmp(subma, ma) == 0) {
			odt.setmasp(ma);
			b1 = true;
			break;
		}
		subData.read((char*)&sp, sizeof(SanPham)); pos1++;
	}

	Data.open(s, ios::in | ios::out | ios::binary);
	Data.seekg(ios::beg); Data.read((char*)&odt, sizeof(outdetail));
	while (!Data.eof())
	{
		odt.getmahd(subma); odt.getmasp(subma1);
		if (strcmp(subma, cond) == 0 && strcmp(subma1, ma) == 0) {
			b = true; change = odt.getsl();
			do {
				wcout << L"S\u1ED1 l\u01B0\u1EE3ng: "; cin >> n; odt.setsl(n); if (!b1) break;
				if (odt.getsl() > sp.getslsp() + change) wcout << L"Kh\u00F4ng \u0111\u1EE7 s\u1ED1 l\u01B0\u1EE3ng \u0111\u1EC3 thanh to\u00E1n! Nh\u1EADp l\u1EA1i: ";
			} while (odt.getsl() > sp.getslsp());
			do {
				wcout << L"\u0110\u01A1n gi\u00E1: "; cin >> n; odt.setdg(n); if (!b1) break;
				if (odt.getdg() < sp.getdgsp()) wcout << L"\u0110\u01A1n gi\u00E1 b\u00E1n ra n\u00EAn l\u1EDBn h\u01A1n \u0111\u01A1n gi\u00E1 m\u1EB7c \u0111\u1ECBnh c\u1EE7a s\u1EA3n ph\u1EA9m! Nh\u1EADp l\u1EA1i: ";
			} while (odt.getdg() < sp.getdgsp());
			change = odt.getsl() - change; sp.setslsp(sp.getslsp() - change);
			Data.seekp(pos2 * sizeof(outdetail));
			Data.write((char*)&odt, sizeof(outdetail));
			break;
		}
		Data.read((char*)&odt, sizeof(outdetail)); pos2++;
	}
	Data.close();
	if (b) wcout << L"\u0110\u00E3 thay \u0111\u1ED5i.\n"; else wcout << L"Kh\u00F4ng c\u00F3 m\u00E3 s\u1EA3n ph\u1EA9m n\u00E0y trong h\u00F3a \u0111\u01A1n " << cond << endl;

	if (b1) {
		subData.clear();
		subData.seekp(pos1 * sizeof(SanPham));
		subData.write((char*)&sp, sizeof(SanPham));
	}
	subData.close();
}

void deleteoutdetail(string s, char cond[]) {
	bool b = true;
	outdetail odt;
	vector<outdetail> list;
	char subma1[10], ma[10], subma[10];
	fstream Data;

	wcout << L"Nh\u1EADp m\u00E3 s\u1EA3n ph\u1EA9m: "; cin.seekg(cin.end); cin.getline(ma, 10);
	Data.open(s, ios::in | ios::binary);
	Data.seekg(ios::beg); Data.read((char*)&odt, sizeof(outdetail));
	while (!Data.eof())
	{
		odt.getmahd(subma); odt.getmasp(subma1);
		if (strcmp(subma, cond) != 0 || strcmp(subma1, ma) != 0) list.push_back(odt);
		Data.read((char*)&odt, sizeof(outdetail));
	}
	Data.close();
	if (b) {
		Data.open(s, ios::out | ios::trunc | ios::binary);
		for (int i = 0; i < list.size(); i++) Data.write((char*)&list[i], sizeof(outdetail));
		wcout << L"\u0110\u00E3 thay \u0111\u1ED5i!\n";
	}
	else wcout << L"Kh\u00F4ng c\u00F3 m\u00E3 s\u1EA3n ph\u1EA9m n\u00E0y trong h\u00F3a \u0111\u01A1n" << cond << endl;
	Data.close();
}

//bill
bool showbill(string s) {
	fstream Data;
	HoaDon hd;

	Data.open(s, ios::in | ios::binary);
	if (!Data.is_open()) return false;

	
	wcout << L"        DANH S\u00C1CH H\u00D3A \u0110\u01A0N\n";
	wcout << L"__________________________________________\n";
	wcout << L"\tM\u00E3 HD\t\tNg\u00E0y                       \n";
	wcout << L"__________________________________________\n";
	Data.read((char*)&hd, sizeof(HoaDon));
	while (!Data.eof()) {
		hd.display();
		Data.read((char*)&hd, sizeof(HoaDon));
	};
	wcout << endl;
	Data.close(); return true;
}

void importbill(string s, int i) {
	char c, ma[10], subma[10], name[40];
	bool b = true;
	fstream Data, subData;
	HoaDon hd;

	subData.open("producer.dat", ios::in | ios::binary);
	if (!subData.is_open()) {
		wcout << L"Ch\u01B0a c\u00F3 d\u1EEF li\u1EC7u v\u1EC1 nh\u00E0 cung c\u1EA5p, nh\u1EADp nh\u00E0 cung c\u1EA5p tr\u01B0\u1EDBc!" << endl;
		goto afterfence2;
	}
	
	wcout << L"Nh\u1EADp m\u00E3 h\u00F3a \u0111\u01A1n: "; cin.seekg(cin.end); cin.getline(ma, 10);
	Data.open(s, ios::in | ios::binary); if (!Data.is_open()) goto afterfence;
	while (true) {
		if (strlen(ma) == 0)
		{
			wcout << L"M\u00E3 h\u00F3a \u0111\u01A1n kh\u00F4ng \u0111\u01B0\u1EE3c tr\u1ED1ng! Nh\u1EADp l\u1EA1i: "; cin.getline(ma, 10);
			continue;
		}
		b = true;
		Data.clear(); Data.seekg(ios::beg);
		while (!Data.eof()) {
			Data.read((char*)&hd, sizeof(HoaDon));
			hd.getmaHD(subma);
			if (strcmp(subma, ma) == 0) {
				wcout << L"Y\u00EAu c\u1EA7u nh\u1EADp l\u1EA1i m\u00E3: "; cin.getline(ma, 10);
				b = false;
				break;
			}
		}
		if (b) break;
	}
afterfence:
	hd.setmaHD(ma);	hd.NhapHD();

	if (i)
	{
		do {
			importindetail("indetail.dat", ma);
			wcout << L"B\u1EA1n c\u00F3 mu\u1ED1n ti\u1EBFp t\u1EE5c kh\u00F4ng? (Y/N): "; c = _getch();
		} while (c != 'N' && c != 'n');
	}
	else {
		wcout << L"Nh\u1EADp t\u00EAn kh\u00E1ch h\u00E0ng: "; cin.seekg(cin.end); cin.getline(name, 40);
		while (strlen(name) == 0)
		{
			wcout << L"T\u00EAn kh\u00E1ch h\u00E0ng kh\u00F4ng \u0111\u01B0\u1EE3c \u0111\u1EC3 tr\u1ED1ng! Nh\u1EADp l\u1EA1i: "; cin.getline(name, 40);
		}
		do {
			importoutdetail("outdetail.dat", ma, name); cin.seekg(cin.end);
			wcout << L"B\u1EA1n c\u00F3 mu\u1ED1n ti\u1EBFp t\u1EE5c kh\u00F4ng? (Y/N): "; c = _getch();
		} while (c != 'N' && c != 'n');
	}
	Data.close(); Data.open(s, ios::out | ios::app | ios::binary);
	Data.write((char*)&hd, sizeof(HoaDon));
	Data.close();
afterfence2:;
}

void deletebill(string s, string s1, int mode) {
	vector<HoaDon> list; vector<indetail> list1; vector<outdetail> list2;
	int i = 0; char ma[10], subma[10];
	fstream Data, subData;
	indetail idt; outdetail odt; HoaDon hd;

	Data.open(s, ios::in | ios::binary);
	if (Data.fail())
	{
		wcout << L"Ch\u01B0a h\u00F3a \u0111\u01A1n n\u00E0o \u0111\u01B0\u1EE3c nh\u1EADp v\u00E0o\n";
		goto exit;
	}

	wcout << L"Nh\u1EADp v\u00E0o m\u00E3 h\u00F3a \u0111\u01A1n c\u1EA7n x\u00F3a: "; cin.seekg(cin.end); cin.getline(subma, 10);
	Data.read((char*)&hd, sizeof(HoaDon));
	while (!Data.eof()) {
		hd.getmaHD(ma);
		if (strcmp(ma, subma) != 0) list.push_back(hd);
		Data.read((char*)&hd, sizeof(HoaDon));
	}
	Data.close();

	Data.open(s, ios::out | ios::trunc | ios::binary);
	for (i = 0; i < list.size(); i++) Data.write((char*)&list[i], sizeof(HoaDon));
	Data.close();

	subData.open(s1, ios::in | ios::binary);
	if (mode) {
		subData.read((char*)&idt, sizeof(indetail));
		while (!subData.eof())
		{
			idt.getmahd(ma);
			if (strcmp(ma, subma) != 0) list1.push_back(idt);
			subData.read((char*)&idt, sizeof(indetail));
		}
		subData.close();

		subData.open(s1, ios::out | ios::trunc | ios::binary);
		for (int i = 0; i < list1.size(); i++) subData.write((char*)&list1[i], sizeof(indetail));
	}
	else {
		subData.read((char*)&odt, sizeof(outdetail));
		while (!subData.eof())
		{
			odt.getmahd(ma);
			if (strcmp(ma, subma) != 0) list2.push_back(odt);
			subData.read((char*)&odt, sizeof(outdetail));
		}
		subData.close();

		subData.open(s1, ios::out | ios::trunc | ios::binary);
		for (int i = 0; i < list2.size(); i++) subData.write((char*)&list2[i], sizeof(outdetail));
	}
	subData.close();
exit:;
}

void editbill(string s) {
	int n = -1; bool b = false;
	fstream Data, subData;
	char ma[10], subma[10];
	HoaDon hd;

	cin.seekg(cin.end);
	wcout << L"Nh\u1EADp v\u00E0o m\u00E3 h\u00F3a \u0111\u01A1n c\u1EA7n thay \u0111\u1ED5i: "; cin.getline(ma, 10);

	Data.open(s, ios::in | ios::out | ios::binary);

	Data.read((char*)&hd, sizeof(HoaDon));
	while (!Data.eof())
	{
		hd.getmaHD(subma); n++;
		if (strcmp(subma, ma) == 0) {
			b = true;

			hd.NhapHD();

			Data.seekp(n * sizeof(HoaDon));
			Data.write((char*)&hd, sizeof(HoaDon));
			break;
		}
		Data.read((char*)&hd, sizeof(HoaDon));
	}
	Data.close();

	if (!b) wcout << L"Kh\u00F4ng t\u00ECm th\u1EA5y h\u00F3a \u0111\u01A1n c\u00F3 m\u00E3 n\u00E0y" << endl; else wcout << L"\u0110\u00E3 thay \u0111\u1ED5i!" << endl;
}

bool searchbill(string s, char res[]) {
	bool b = false;
	char subma[10];
	fstream Data;
	HoaDon hd;
	wcout << L"M\u00E3 h\u00F3a \u0111\u01A1n: "; cin.seekg(cin.end); cin.getline(res, 10);
	Data.open(s, ios::in | ios::binary); if (!Data.is_open())
	{
		wcout << L"Ch\u01B0a c\u00F3 d\u1EEF li\u1EC7u n\u00E0o v\u1EC1 h\u00F3a \u0111\u01A1n!" << endl;
		return false;
	}
	Data.read((char*)&hd, sizeof(HoaDon));
	while (!Data.eof())
	{
		hd.getmaHD(subma);
		if (strcmp(res, subma) == 0) {
			b = true;
			wcout << L"\tM\u00E3 HD\t\tNg\u00E0y\n";
			hd.display();
			break;
		}
		Data.read((char*)&hd, sizeof(HoaDon));
	}
	Data.close(); return b;
}

//Wage
int statictis(string in, string out) {
	int mon, year, n = 0; char ma[10], subma[10];
	fstream Data, subData;
	HoaDon hd; outdetail odt; indetail idt;
	wcout << L"Nh\u1EADp th\u00E1ng: "; cin >> mon; mon--;
	while (mon < 0 || mon > 11)
	{
		wcout << L"Th\u00E1ng kh\u00F4ng h\u1EE3p l\u1EC7, nh\u1EADp l\u1EA1i: "; cin >> mon; mon--;
	}
	time_t present = time(0);
	wcout << L"Nh\u1EADp n\u0103m: "; cin >> year; year -= 1900;
	while (year > gmtime(&present)->tm_year || year < 0)
	{
		wcout << L"N\u0103m kh\u00F4ng h\u1EE3p l\u1EC7! Nh\u1EADp l\u1EA1i: "; cin >> year; year -= 1900;
	}

	Data.open(out, ios::in | ios::binary);
	if (!Data.is_open()) {
		wcout << L"Ch\u01B0a m\u1EB7t h\u00E0ng n\u00E0o \u0111\u01B0\u1EE3c b\u00E1n ra!";
		return 0;
	}
	Data.read((char*)&hd, sizeof(HoaDon));
	while (!Data.eof())
	{
		present = hd.getday();
		if (mon == gmtime(&present)->tm_mon && year == gmtime(&present)->tm_year) {
			hd.getmaHD(ma);
			subData.open("outdetail.dat", ios::in | ios::binary);
			subData.read((char*)&odt, sizeof(outdetail));
			while (!subData.eof())
			{
				odt.getmahd(subma);
				if (strcmp(ma, subma) == 0) n += odt.gettt();
				subData.read((char*)&odt, sizeof(outdetail));
			}
			subData.close();
		}
		Data.read((char*)&hd, sizeof(HoaDon));
	}
	Data.close();

	Data.open(in, ios::in | ios::binary);
	Data.read((char*)&hd, sizeof(HoaDon));
	while (!Data.eof())
	{
		present = hd.getday();
		if (mon == gmtime(&present)->tm_mon && year == gmtime(&present)->tm_year) {
			hd.getmaHD(ma);
			subData.open("indetail.dat", ios::in | ios::binary);
			subData.read((char*)&idt, sizeof(indetail));
			while (!subData.eof())
			{
				idt.getmahd(subma);
				if (strcmp(ma, subma) == 0) n -= idt.gettt();
				subData.read((char*)&idt, sizeof(indetail));
			}
			subData.close();
		}
		Data.read((char*)&hd, sizeof(HoaDon));
	}
	Data.close();
	return n;
}

bool analyze(string source, string infor, int mode) {
	int max = 0; int n = 0, mon = 0, year; char resname[80], prodma[10], odtprodma[10], ma[10], subma[10];
	fstream Data, subData, prodData;
	HoaDon hd; outdetail odt; SanPham sp;
	time_t present = time(0); mode--;
	prodData.open("product.dat", ios::in | ios::binary);
	if (!prodData.is_open()) {
		wcout << L"Ch\u01B0a s\u1EA3n ph\u1EA9m n\u00E0o \u0111\u01B0\u1EE3c nh\u1EADp v\u00E0o!\n";
		system("pause");
		return false;
	}
	Data.open(source, ios::in | ios::binary);
	if (!Data.is_open()) {
		wcout << L"Ch\u01B0a m\u1EB7t h\u00E0ng n\u00E0o \u0111o\u1EF1c giao d\u1ECBch!";
		system("pause");
		return false;
	}

	if (mode) {
		wcout << L"Nh\u1EADp th\u00E1ng: "; cin >> mon;
		while (mon < 1 || mon > 12)
		{
			wcout << L"Th\u00E1ng kh\u00F4ng h\u1EE3p l\u1EC7, nh\u1EADp l\u1EA1i: "; cin >> mon;
		}
	}
	wcout << L"Nh\u1EADp n\u0103m: "; cin >> year;
	while (year < 0 || year > gmtime(&present)->tm_year + 1900)
	{
		wcout << L"N\u0103m kh\u00F4ng h\u1EE3p l\u1EC7, nh\u1EADp l\u1EA1i: "; cin >> year;
	}

	mon--; year -= 1900;
	prodData.read((char*)&sp, sizeof(SanPham));
	while (!prodData.eof())
	{
		sp.getma(prodma); n = 0;
		Data.read((char*)&hd, sizeof(HoaDon));
		while (!Data.eof())
		{
			present = hd.getday();
			if (mon * mode == mode * (gmtime(&present)->tm_mon) && year == gmtime(&present)->tm_year) {
				hd.getmaHD(ma);
				subData.open("outdetail.dat", ios::in | ios::binary);
				subData.read((char*)&odt, sizeof(outdetail));
				while (!subData.eof())
				{
					odt.getmahd(subma); odt.getmasp(odtprodma);
					if (strcmp(ma, subma) == 0 && strcmp(prodma, odtprodma) == 0) n += odt.getsl();
					subData.read((char*)&odt, sizeof(outdetail));
				}
				subData.close();
			}
			Data.read((char*)&hd, sizeof(HoaDon));
		}
		if (n > max) {
			max = n;
			sp.getten(resname);
		}
		Data.clear(); Data.seekg(ios::beg);
		prodData.read((char*)&sp, sizeof(SanPham));
	}

	if (max > 0)
	{
		wcout << L"M\u1EB7t h\u00E0ng b\u00E1n ch\u1EA1y nh\u1EA5t l\u00E0: " << resname << endl;
		wcout << L"S\u1ED1 l\u01B0\u1EE3ng b\u00E1n ra: " << max << endl;
	}
	else wcout << L"Kh\u00F4ng c\u00F3 m\u1EB7t h\u00E0ng n\u00E0o \u0111\u01B0\u1EE3c b\u00E1n ra." << endl;
	system("pause");

	return true;
}
//main program
int main() {
	system("color F0");
	_setmode(_fileno(stdout), _O_U16TEXT);
	SetConsoleTitleW(L"T\u1EA1p h\u00F3a Nam Tr\u00E0");

	int choice = -1, option = -1, option1 = -1, n = 0;
	char res[10], ma[10], subma[10];

	while (choice != 0) {
		system("cls");
		wcout << L"\t ______________________________________________________________\n";
		wcout << L"\t|    CH\u01AF\u01A0NG TR\u00CCNH QU\u1EA2N L\u00DD C\u1EECA H\u00C0NG B\u00C1N H\u00C0NG T\u1EA0P H\u00D3A NAM TR\u00C0    |\n";
		wcout << L"\t|______________________________________________________________|\n";
		wcout << L"\t|                  1. Qu\u1EA3n l\u00FD nh\u00E0 cung c\u1EA5p                     |\n";
		wcout << L"\t|                  2. Qu\u1EA3n l\u00FD s\u1EA3n ph\u1EA9m                         |\n";
		wcout << L"\t|                  3. Qu\u1EA3n l\u00FD h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng                |\n";
		wcout << L"\t|                  4. Qu\u1EA3n l\u00FD h\u00F3a \u0111\u01A1n thanh to\u00E1n               |\n";
		wcout << L"\t|                  5. Th\u1ED1ng k\u00EA doanh thu                       |\n";
		wcout << L"\t|                  6. S\u1EA3n ph\u1EA9m b\u00E1n ch\u1EA1y                        |\n";
		wcout << L"\t|                  0. Tho\u00E1t                                    |\n";
		wcout << L"\t|______________________________________________________________|\n";
		wcout << L"\t                     Nh\u1EADp l\u1EF1a ch\u1ECDn c\u1EE7a b\u1EA1n: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			wcout << L"\t ______________________________________________________________\n";
			wcout << L"\t|                      QU\u1EA2N L\u00DD NH\u00C0 CUNG C\u1EA4P                    |\n";
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t|               1. Nh\u1EADp th\u00EAm 1 nh\u00E0 cung c\u1EA5p                    |\n";
			wcout << L"\t|               2. X\u00F3a 1 nh\u00E0 cung c\u1EA5p                          |\n";
			wcout << L"\t|               3. Hi\u1EC3n th\u1ECB danh s\u00E1ch nh\u00E0 cung c\u1EA5p             |\n";
			wcout << L"\t|               4. S\u1EEDa th\u00F4ng tin 1 nh\u00E0 cung c\u1EA5p                |\n";
			wcout << L"\t|               5. T\u00ECm ki\u1EBFm th\u00F4ng tin 1 nh\u00E0 cung c\u1EA5p           |\n";
			wcout << L"\t|               0. Tho\u00E1t                                       |\n";
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t                     Nh\u1EADp l\u1EF1a ch\u1ECDn c\u1EE7a b\u1EA1n: ";
			cin >> option;
			switch (option)
			{
			case 1:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: Nh\u1EADp th\u00EAm 1 nh\u00E0 cung c\u1EA5p!" << endl << endl;
				importproducer("producer.dat");
				system("pause");
				break;
			case 2:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: X\u00F3a 1 nh\u00E0 cung c\u1EA5p!" << endl << endl;
				wcout << L"Danh s\u00E1ch nh\u00E0 cung c\u1EA5p:" << endl << endl;
				if (showproducer("producer.dat")) deleteproducer("producer.dat");
				system("pause");
				break;
			case 3:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: Hi\u1EC3n th\u1ECB danh s\u00E1ch nh\u00E0 cung c\u1EA5p!" << endl << endl;
				showproducer("producer.dat");
				system("pause");
				break;
			case 4:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: S\u1EEDa th\u00F4ng tin 1 nh\u00E0 cung c\u1EA5p!" << endl << endl;
				wcout << L"Danh s\u00E1ch nh\u00E0 cung c\u1EA5p:" << endl << endl;
				if (showproducer("producer.dat")) editproducer("producer.dat");
				system("pause");
				break;
			case 5:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: T\u00ECm ki\u1EBFm th\u00F4ng tin 1 nh\u00E0 cung c\u1EA5p!" << endl << endl;
				searchproducer("producer.dat");
				system("pause");
				break;
			case 0:
				break;
			}
			break;
		case 2:
			system("cls");
			wcout << L"\t ______________________________________________________________\n";
			wcout << L"\t|                         QU\u1EA2N L\u00DD S\u1EA2N PH\u1EA8M                     |\n";
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t|                  1. Nh\u1EADp th\u00EAm 1 s\u1EA3n ph\u1EA9m m\u1EDBi                 |\n";
			wcout << L"\t|                  2. X\u00F3a 1 s\u1EA3n ph\u1EA9m                           |\n";
			wcout << L"\t|                  3. Hi\u1EC3n th\u1ECB danh s\u00E1ch s\u1EA3n ph\u1EA9m              |\n";
			wcout << L"\t|                  4. S\u1EEDa th\u00F4ng tin 1 s\u1EA3n ph\u1EA9m                 |\n";
			wcout << L"\t|                  5. T\u00ECm ki\u1EBFm th\u00F4ng tin 1 s\u1EA3n ph\u1EA9m            |\n";
			wcout << L"\t|                  0. Tho\u00E1t                                    |\n";
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t                     Nh\u1EADp l\u1EF1a ch\u1ECDn c\u1EE7a b\u1EA1n: ";
			cin >> option;
			switch (option)
			{
			case 1:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: Nh\u1EADp th\u00EAm 1 s\u1EA3n ph\u1EA9m m\u1EDBi!" << endl << endl;
				importproduct("product.dat");
				system("pause");
				break;
			case 2:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: X\u00F3a 1 s\u1EA3n ph\u1EA9m!" << endl << endl;
				wcout << L"Danh s\u00E1ch s\u1EA3n ph\u1EA9m:" << endl << endl;
				if (showproduct("product.dat")) deleteproduct("product.dat");
				system("pause");
				break;
			case 3:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: Hi\u1EC3n th\u1ECB danh s\u00E1ch s\u1EA3n ph\u1EA9m!" << endl << endl;
				showproduct("product.dat");
				system("pause");
				break;
			case 4:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: S\u1EEDa th\u00F4ng tin 1 s\u1EA3n ph\u1EA9m!" << endl << endl;
				wcout << L"Danh s\u00E1ch s\u1EA3n ph\u1EA9m:" << endl << endl;
				if (showproduct("product.dat")) editproduct("product.dat");
				system("pause");
				break;
			case 5:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: T\u00ECm ki\u1EBFm th\u00F4ng tin 1 s\u1EA3n ph\u1EA9m!" << endl << endl;
				searchproduct("product.dat");
				system("pause");
				break;
			case 0:
				break;
			}
			break;
		case 3:
			system("cls");
			wcout << L"\t ______________________________________________________________\n";
			wcout << L"\t|                    QU\u1EA2N L\u00DD H\u00D3A \u0110\u01A0N NH\u1EACP H\u00C0NG                 |\n";
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t|            1. Nh\u1EADp th\u00EAm 1 h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng m\u1EDBi              |\n";
			wcout << L"\t|            2. X\u00F3a 1 h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng                        |\n";
			wcout << L"\t|            3. Hi\u1EC3n th\u1ECB danh s\u00E1ch h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng           |\n";
			wcout << L"\t|            4. S\u1EEDa th\u00F4ng tin 1 h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng              |\n";
			wcout << L"\t|            5. T\u00ECm ki\u1EBFm th\u00F4ng tin 1 h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng         |\n";
			wcout << L"\t|            0. Tho\u00E1t                                          |\n";
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t                     Nh\u1EADp l\u1EF1a ch\u1ECDn c\u1EE7a b\u1EA1n: ";
			cin >> option;
			switch (option)
			{
			case 1:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: Nh\u1EADp th\u00EAm 1 h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng m\u1EDBi!" << endl << endl;
				importbill("inputbill.dat", 1);
				system("pause");
				break;
			case 2:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn x\u00F3a m\u1ED9t h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng!" << endl << endl;
				wcout << L"Danh s\u00E1ch h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng:" << endl << endl;
				if (showbill("inputbill.dat")) deletebill("inputbill.dat", "indetail.dat", 1);
				system("pause");
				break;
			case 3:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn : Hi\u1EC3n th\u1ECB danh s\u00E1ch h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng!" << endl << endl;
				showbill("inputbill.dat");
				system("pause");
				break;
			case 4:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: S\u1EEDa th\u00F4ng tin 1 h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng!" << endl << endl;
				wcout << L"Danh s\u00E1ch h\u00F3a \u0111\u01A1n nhâp h\u00E0ng:" << endl << endl;
				if (showbill("inputbill.dat")) editbill("inputbill.dat");
				system("pause");
				break;
			case 5:
				system("cls"); option1 = -1;
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: T\u00ECm ki\u1EBFm th\u00F4ng tin 1 h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng!" << endl << endl;
				if (searchbill("inputbill.dat", res)) showindetail("indetail.dat", res);
				else {
					wcout << L"Kh\u00F4ng c\u00F3 h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng n\u00E0y!" << endl;
					system("pause");
					break;
				}
				do
				{
					wcout << L"\t ______________________________________________________________\n";
					wcout << L"\t|                   T\u00CCM KI\u1EBEM H\u00D3A \u0110\u01A0N NH\u1EACP H\u00C0NG                 |\n";
					wcout << L"\t|______________________________________________________________|\n";
					wcout << L"\t|              1. S\u1EEDa chi ti\u1EBFt h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng               |\n";
					wcout << L"\t|              2. X\u00F3a chi ti\u1EBFt h\u00F3a \u0111\u01A1n nhâp h\u00E0ng               |\n";
					wcout << L"\t|              0. Tho\u00E1t                                        |\n";
					wcout << L"\t|______________________________________________________________|\n";
					wcout << L"\t                     Nh\u1EADp l\u1EF1a ch\u1ECDn c\u1EE7a b\u1EA1n: ";
					cin >> option1;
					switch (option1)
					{
					case 1:
						wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: S\u1EEDa chi ti\u1EBFt h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng!" << endl << endl;
						showindetail("indetail.dat", res);
						editindetail("indetail.dat", res);
						break;
					case 2:
						wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: X\u00F3a chi ti\u1EBFt h\u00F3a \u0111\u01A1n nh\u1EADp h\u00E0ng!" << endl << endl;
						showindetail("indetail.dat", res);
						deleteindetail("indetail.dat", res);
						break;
					case 0:
						break;
					default:
						break;
					}
				} while (option1 != 0);
				system("pause");
				break;
			case 0:
				break;
			}
			break;
		case 4:
			system("cls");
			wcout << L"\t ______________________________________________________________\n";
			wcout << L"\t|                   QU\u1EA2N L\u00DD H\u00D3A \u0110\u01A0N THANH TO\u00C1N                 |\n";
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t|           1. Nh\u1EADp th\u00EAm 1 h\u00F3a \u0111\u01A1n thanh to\u00E1n m\u1EDBi              |\n";
			wcout << L"\t|           2. X\u00F3a 1 h\u00F3a \u0111\u01A1n thanh to\u00E1n                        |\n";
			wcout << L"\t|           3. Hi\u1EC3n th\u1ECB danh s\u00E1ch h\u00F3a \u0111\u01A1n thanh to\u00E1n           |\n";
			wcout << L"\t|           4. S\u1EEDa th\u00F4ng tin 1 h\u00F3a \u0111\u01A1n thanh to\u00E1n              |\n";
			wcout << L"\t|           5. T\u00ECm ki\u1EBFm th\u00F4ng tin 1 h\u00F3a \u0111\u01A1n thanh to\u00E1n         |\n";
			wcout << L"\t|           0. Tho\u00E1t                                           |\n";
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t                     Nh\u1EADp l\u1EF1a ch\u1ECDn c\u1EE7a b\u1EA1n: ";
			cin >> option;
			switch (option)
			{
			case 1:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn nh\u1EADp th\u00EAm 1 h\u00F3a \u0111\u01A1n thanh to\u00E1n m\u1EDBi!" << endl << endl;
				importbill("outputbill.dat", 0);
				system("pause");
				break;
			case 2:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: X\u00F3a 1 h\u00F3a \u0111\u01A1n thanh to\u00E1n!" << endl << endl;
				wcout << L"Danh s\u00E1ch h\u00F3a \u0111\u01A1n thanh to\u00E1n:" << endl << endl;
				if (showbill("outputbill.dat")) deletebill("outputbill.dat", "outdetail.dat", 0);
				system("pause");
				break;
			case 3:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn hi\u1EC3n th\u1ECB danh s\u00E1ch h\u00F3a \u0111\u01A1n thanh to\u00E1n!" << endl << endl;
				showbill("outputbill.dat");
				system("pause");
				break;
			case 4:
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: S\u1EEDa th\u00F4ng tin 1 h\u00F3a \u0111\u01A1n thanh to\u00E1n!" << endl << endl;
				wcout << L"Danh s\u00E1ch h\u00F3a \u0111\u01A1n thanh to\u00E1n:" << endl << endl;
				if (showbill("outputbill.dat")) editbill("outputbill.dat");
				system("pause");
				break;
			case 5:
				system("cls");
				wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: T\u00ECm ki\u1EBFm th\u00F4ng tin 1 h\u00F3a \u0111\u01A1n thanh to\u00E1n!" << endl << endl;
				if (searchbill("outputbill.dat", res)) showoutdetail("outdetail.dat", res);
				else {
					wcout << L"Kh\u00F4ng c\u00F3 h\u00F3a \u0111\u01A1n thanh to\u00E1n n\u00E0y!" << endl;
					system("pause");
					break;
				}
				do
				{
					wcout << L"\t ______________________________________________________________\n";
					wcout << L"\t|                  T\u00CCM KI\u1EBEM H\u00D3A \u0110\u01A0N THANH TO\u00C1N                 |\n";
					wcout << L"\t|______________________________________________________________|\n";
					wcout << L"\t|              1. S\u1EEDa chi ti\u1EBFt h\u00F3a \u0111\u01A1n thanh to\u00E1n              |\n";
					wcout << L"\t|              2. X\u00F3a chi ti\u1EBFt h\u00F3a \u0111\u01A1n thanh to\u00E1n              |\n";
					wcout << L"\t|              0. Tho\u00E1t                                        |\n";
					wcout << L"\t|______________________________________________________________|\n";
					wcout << L"\t                     Nh\u1EADp l\u1EF1a ch\u1ECDn c\u1EE7a b\u1EA1n: ";
					cin >> option1;
					switch (option1)
					{
					case 1:
						wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: S\u1EEDa chi ti\u1EBFt h\u00F3a \u0111\u01A1n thanh to\u00E1n!" << endl << endl;
						showoutdetail("outdetail.dat", res);
						editoutdetail("outdetail.dat", res);
						break;
					case 2:
						wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: X\u00F3a chi ti\u1EBFt h\u00F3a \u0111\u01A1n thanh to\u00E1n!" << endl << endl;
						showoutdetail("outdetail.dat", res);
						deleteoutdetail("outdetail.dat", res);
						break;
					case 0:
						break;
					default:
						break;
					}
				} while (option1 != 0);
				system("pause");
				break;
			case 0:
				break;
			}
			break;
		case 5:
			wcout << L"B\u1EA1n \u0111\u00E3 ch\u1ECDn: Th\u1ED1ng k\u00EA doanh thu!" << endl << endl;
			n = statictis("inputbill.dat", "outputbill.dat");
			wcout << L"\nT\u00ECnh tr\u1EA1ng kinh doanh c\u1EE7a c\u1EEDa h\u00E0ng: ";
			if (n < 0) wcout << endl << L"L\u1ED7 " << -n << " VND" << endl; else if (n > 0) wcout << endl << L"L\u00E3i " << n << " VND" << endl; else wcout << L"\nH\u00F2a v\u1ED1n\n";
			system("pause");
			break;
		case 6:
			system("cls");
			wcout << L"\t ______________________________________________________________\n";
			wcout << L"\t|                  TH\u1ED0NG K\u00CA S\u1EA2N PH\u1EA8M B\u00C1N CH\u1EA0Y                  |\n";
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t|                    1. T\u00ECm ki\u1EBFm theo n\u0103m                      |" << endl;
			wcout << L"\t|                    2. T\u00ECm ki\u1EBFm theo th\u00E1ng                    |" << endl;
			wcout << L"\t|______________________________________________________________|\n";
			wcout << L"\t                Nh\u1EA5n ph\u00EDm b\u1EA5t k\u1EF3 kh\u00E1c \u0111\u1EC3 tho\u00E1t!" << endl;
			wcout << L"\t                Nh\u1EADp l\u1EF1a ch\u1ECDn c\u1EE7a b\u1EA1n: "; 
			cin >> option;
			if (option != 1 && option != 2) break;
			analyze("outputbill.dat", "outdetail.dat", option);
			break;
		default:
			break;
		}
	};
	return 0;
}
