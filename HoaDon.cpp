#pragma once
#include<iostream>
#include<cstring>
#include<ctime>

using namespace std;

class HoaDon
{
protected:
	char MaHD[10];
	tm Time;
	char date[10];
public:
	HoaDon() {
		time_t setup = time(0);
		Time = *gmtime(&setup);
	};
	HoaDon(char MaHD[], tm Time) {
		strcpy(this->MaHD, MaHD);
		time_t setup = time(0);
		Time = *gmtime(&setup);
		this->Time.tm_mday = Time.tm_mday;
		this->Time.tm_mon = Time.tm_mon;
		this->Time.tm_year = Time.tm_year;
	};

	int converter(char x[], int f, int l) {
		int res = 0;
		for (int i = f; i <= l; i++) {
			res = static_cast<int>(x[i]) - 48 + res * 10;
		}
		return res;
	}
	bool checkstringdate(char x[]) {
		if (strlen(x) != 10) return false;
		if (x[2] != '/' || x[5] != '/') return false;
		for (int i = 0; i < strlen(x); i++) {
			if (i == 2 || i == 5) continue;
			if (x[i] < 48 || x[i] > 57) return false;
		}

		return true;
	}
	bool checkdate(tm Time) {
		time_t test; tm* res; tm clone = Time;

		test = mktime(&clone);
		res = localtime(&test);
		if (res->tm_mday == Time.tm_mday && res->tm_mon == Time.tm_mon && res->tm_year == Time.tm_year) return true;
		else return false;
	}

	void setmaHD(char MaHD[]) {
		strcpy(this->MaHD, MaHD);
	};
	void setday() {
		time_t now = time(0);
		Time = *gmtime(&now);
	}
	void setday(time_t Day) {
		Time = *gmtime(&Day);
	};
	void setday(tm Time) {
		this->Time = Time;
	}
	bool setday(char Date[10]) {
		if (checkstringdate(Date)) {
			Time.tm_mday = converter(Date, 0, 1);
			Time.tm_mon = converter(Date, 3, 4) - 1;
			Time.tm_year = converter(Date, 6, 9) - 1900;
			if (checkdate(Time)) return true;
			else return false;
		}
		else return false;
	}

	void getmaHD(char MaHD[]) {
		strcpy(MaHD, this->MaHD);
	};
	time_t getday() {
		return mktime(&Time);
	};
	void getday(tm Time) {
		Time = this->Time;
	}
	void getday(char Time[]) {
		Time = asctime(&(this->Time));
	}
	void NhapHD()
	{
		wcout << L"Nh\u1EADp th\u1EDDi gian (dd/mm/yyyy): ";
		cin >> date;
		while (!setday(date))
		{
			wcout << L"Nh\u1EADp l\u1EA1i th\u1EDDi gian (dd/mm/yyyy): ";
			cin >> date;
		}
	};

	void display() {
		wcout << '\t' << MaHD << "\t\t" << Time.tm_mday << '/' << Time.tm_mon + 1 << '/' << Time.tm_year + 1900 << endl;
	};
};
