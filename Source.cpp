#define _USE_MATH_DEFINES
#include "Parametres.h"
#include "Coordinates.h"
#include "logo.h"
#include <cmath>
#include<iomanip>
#include <iostream>
#include <string>
#include <locale>
#include <Windows.h>

//#include "stdafx.h"

using namespace std;


void cl() { system("pause"); system("cls"); }
void nl() { cout << "\n"; } 
void br(string header) { 
	cout << "________________________________________________________________\n";
	cout << header << endl;
	cout << "________________________________________________________________\n";
}

void calculations(double latFrom, double lonFrom, double latTo, double lonTo, double Unt, double Unu, double Unc, double hd) {
	Parameters parameters;
	parameters.initiateUc(Unt, Unu, Unc);
	parameters.initiateHda(hd);
	parameters.getInfo();
nl();

	parameters.calculateC(latFrom, lonFrom, latTo, lonTo);
nl();
	parameters.calculateAB(parameters.cDegree, parameters.cRadian);
nl();
	if(abs(parameters.ABdegree - parameters.ABradian) > 0){
	cout << "��� ����������� ������� ����� ����������� �� ��������� " << abs(parameters.ABdegree - parameters.ABradian) << "��, ��� ����� ������� �������������� ������������.\n";
	}
	cout << "� ����� ��������� �������� �������� � ���� ������������ ��, ���������� ����� �������.\n";
nl();
	parameters.calculateAlpha(latFrom, lonFrom, lonTo, parameters.cDegree);	 //������ ��
	parameters.calculateBeta(latTo, lonFrom, lonTo, parameters.cDegree);	//������ ��
nl();
	parameters.calculateN();
nl();
	parameters.calculateD();
nl();
	parameters.calculateEa();
nl();
	parameters.calculateP();
nl();
}


void main() {
	//setlocale(LC_CTYPE, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	initialScreen();  
	
	
	
	
	//bool fromKp = true; //���� ����� ��������� ��������
	bool fromKp = false; //���� ����� ������� �������
	

//���������� ����������
	double
		latV, lonV,	    //������ � ������� ����� (v - vessel)
		lat1m, lon1m,   //������ � ������� ������� ���� (1m - first mskc)
		lat2m, lon2m,   //������ � ������� ������� ���� (2m - second mskc)
		UnVu, UnVc, UnVt, Un1mc, Un1mt, Un1mu, Un2mc, Un2mt, Un2mu;//����������� �������� ���������
	string
		nameV,          //�������� �����
		name1m,			//�����1
		name2m;			//�����2
	int
		hdv, hm1, hm2;  //������ ���������
//������������ ��������
	if (fromKp) {
		latV = 39.43, lonV = 131.11; UnVt = 0.7; UnVc = 0.7; UnVu = 4; nameV = "����� ������"; hdv = 9; cout << "��������� �������� �����\n";
		lat1m = 42.45; lon1m = 133.02; name1m = "���� � �.�����������"; hm1 = 12.5; Un1mu = UnVu; Un1mc = UnVc; Un1mt = UnVt; cout << "��������� �������� ����1\n";
		lat2m = 54.45; lon2m = 20.35; name2m = "���� � �.�����������"; hm2 = 11; Un2mu = UnVu; Un2mc = UnVc; Un2mt = UnVt; cout << "��������� �������� ����2\n";
	}
	else {
		br("���� �������� ������ ��� ����� (name, lat, lon, Unom, hda)");
		cout << "������� �������� �����                           : "; cin >> nameV; nl(); 
		cout << "������� ������ ����� (lat)           (������ d.m): "; cin >> latV; nl();
		cout << "������� ������� ����� (lon)          (������ d.m): "; cin >> lonV; nl();
		cout << "������� ������ ������������� �������        (� �): "; cin >> hdv; nl();
		cout << "������� Unom ���  ��                        (���): "; cin >> UnVt; nl();
		cout << "������� Unom ���  ����                      (���): "; cin >> UnVu; nl();
		cout << "������� Unom ���  ���                       (���): "; cin >> UnVc; nl();
		nameV = "����� " + nameV;

		nl();
		br("���� �������� ������ ��� ����1 (name, lat, lon, Unom, hda)");

		cout << "������� ����� � ��������� ����                   : "; cin >> name1m; nl();
		cout << "������� ������ ��������� ���� (lat)  (������ d.m): "; cin >> lat1m; nl();
		cout << "������� ������� ��������� ���� (lon) (������ d.m): "; cin >> lon1m; nl();
		cout << "������� ������ ������������� �������        (� �): "; cin >> hm1; nl();
		cout << "������� Unom ���  ��                        (���): "; cin >> Un1mt; nl();
		cout << "������� Unom ���  ����                      (���): "; cin >> Un1mu; nl();
		cout << "������� Unom ���  ���                       (���): "; cin >> Un1mc; nl();

		name1m = "����1 � �." + name1m;
		nl();
		br("���� �������� ������ ��� ����2 (name, lat, lon, Unom, hda)");
		cout << "������� ����� � ���������� ����                  : "; cin >> name2m; nl();
		cout << "������� ������ ������� ���� (lat)    (������ d.m): "; cin >> lat2m; nl();
		cout << "������� ������� ������� ���� (lon)   (������ d.m): "; cin >> lon2m; nl();
		cout << "������� ������ ������������� �������        (� �): "; cin >> hm2; nl();
		cout << "������� Unom ���  ��                        (���): "; cin >> Un2mt; nl();
		cout << "������� Unom ���  ����                      (���): "; cin >> Un2mu; nl();
		cout << "������� Unom ���  ���                       (���): "; cin >> Un2mc; nl();

		name2m = "����2 � �." + name2m;
		nl();
	}
cl();
	
	
//������� Coordinates(lat, lon, name, Unt, Unu, Unc, hd)
	Coordinates vessel(latV, lonV, nameV, UnVt, UnVu, UnVc, hdv);
nl();
	Coordinates mskc1(lat1m, lon1m, name1m, Un1mt, Un1mu, Un1mc, hm1);
nl();
	Coordinates mskc2(lat2m, lon2m, name2m, Un2mt, Un2mu, Un2mc, hm2);
nl();
	

cl();
//�����-�����  calculations(latFrom, lonFrom, latTo, lonTo, Unt, Unu, Unc, hd)
br("������� ����� - ����� \n\n�� ����� �� " + mskc1.locationsName);
nl();
calculations(vessel.latitude, vessel.longitude, mskc1.latitude, mskc1.longitude, mskc1.Unomt, mskc1.Unomu, mskc1.Unomc, mskc1.hda);
cl();
br("�� ����� �� " + mskc2.locationsName);
nl();
calculations(vessel.latitude, vessel.longitude, mskc2.latitude, mskc2.longitude, mskc2.Unomt, mskc2.Unomu, mskc2.Unomc, mskc2.hda);
//�����-�����
cl();
br("������� �����-����� \n\n�� " + mskc1.locationsName + " �� �����");
nl();
calculations(mskc1.latitude, mskc1.longitude, vessel.latitude, vessel.longitude, vessel.Unomt, vessel.Unomu, vessel.Unomc, vessel.hda);
//calculations(42.40, 133.02, vessel.latitude, vessel.longitude, vessel.Unom, vessel.hda);
cl();
br("�� " + mskc2.locationsName + " �� �����");
nl();
calculations(mskc2.latitude, mskc2.longitude, vessel.latitude, vessel.longitude, vessel.Unomt, vessel.Unomu, vessel.Unomc, vessel.hda);
//calculations(54.43, 20.44, vessel.latitude, vessel.longitude, vessel.Unom, vessel.hda);
cl();
}