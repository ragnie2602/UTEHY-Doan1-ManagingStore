#pragma once
#include<iostream>
#include<cstring>
#include<fcntl.h>
#include<io.h>
#include<Windows.h>
#include<conio.h>
using namespace std;
class ThongTin
{
protected:
	char Ma[10];
	char Ten[80];
public:
	ThongTin() {};
	ThongTin(char Ma[], char Ten[]) {
		strcpy(this->Ma, Ma);
		strcpy(this->Ten, Ten);
	};

	void setma(char Ma[]) {
		strcpy(this->Ma, Ma);
	};
	void setten(char Ten[]) {
		strcpy(this->Ten, Ten);
	};

	void getma(char Ma[]) {
		strcpy(Ma, this->Ma);
	};
	void getten(char Ten[]) {
		strcpy(Ten, this->Ten);
	};
};