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

void calculations(double latFrom, double lonFrom, double latTo, double lonTo, double Un, int hd) {
	Parameters parameters;
	parameters.initiateUc(Un);
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
		UnV, Un1m, Un2m;//����������� �������� ���������
	string
		nameV,          //�������� �����
		name1m,			//�����1
		name2m;			//�����2
	int
		hdv, hm1, hm2;  //������ ���������
//������������ ��������
	if (fromKp) {
		latV = 39.43, lonV = 131.11; UnV = 4.6; nameV = "����� ������"; hdv = 18/2; cout << "��������� �������� �����\n";
		lat1m = 42.45; lon1m = 133.02; name1m = "���� � �.�����������"; hm1 = 25; Un1m = 3.2; cout << "��������� �������� ����1\n";
		lat2m = 54.45; lon2m = 20.35; name2m = "���� � �.�����������"; hm2 = 22; Un2m = 4; cout << "��������� �������� ����2\n";
	}
	else {
		br("���� �������� ������ ��� ����� (name, lat, lon, Unom, hda)");
		cout << "������� �������� �����                 : "; cin >> nameV; nl();
		cout << "������� ������ ����� (lat)             : "; cin >> latV; nl();
		cout << "������� ������� ����� (lon)            : "; cin >> lonV; nl();
		cout << "������� ������ ������������� �������   : "; cin >> hdv; nl();
		cout << "������� ����������� �������� ��������� : "; cin >> UnV; nl();

		nameV = "����� " + nameV;

		nl();
		br("���� �������� ������ ��� ����1 (name, lat, lon, Unom, hda)");

		cout << "������� ����� � ��������� ����         : "; cin >> name1m; nl();
		cout << "������� ������ ��������� ���� (lat)    : "; cin >> lat1m; nl();
		cout << "������� ������� ��������� ���� (lon)   : "; cin >> lon1m; nl();
		cout << "������� ������ ������������� �������   : "; cin >> hm1; nl();
		cout << "������� ����������� �������� ��������� : "; cin >> Un1m; nl();

		name1m = "����1 � �." + name1m;
		nl();
		br("���� �������� ������ ��� ����2 (name, lat, lon, Unom, hda)");
		cout << "������� ����� � ���������� ����        : "; cin >> name2m; nl();
		cout << "������� ������ ������� ���� (lat)      : "; cin >> lat2m; nl();
		cout << "������� ������� ������� ���� (lon)     : "; cin >> lon2m; nl();
		cout << "������� ������ ������������� �������   : "; cin >> hm2; nl();
		cout << "������� ����������� �������� ��������� : "; cin >> Un2m; nl();

		name2m = "����2 � �." + name2m;
		nl();
	}
cl();
	
	
//�������
	Coordinates vessel(latV, lonV, nameV, UnV, hdv);
nl();
	Coordinates mskc1(lat1m, lon1m, name1m, Un1m, hm1);
nl();
	Coordinates mskc2(lat2m, lon2m, name2m, Un2m, hm2);
nl();
	

cl();
//�����-�����
br("������� ����� - ����� \n\n�� ����� �� " + mskc1.locationsName);
nl();
calculations(vessel.latitude, vessel.longitude, mskc1.latitude, mskc1.longitude, mskc1.Unom, mskc1.hda);
cl();
br("�� ����� �� " + mskc2.locationsName);
nl();
calculations(vessel.latitude, vessel.longitude, mskc2.latitude, mskc2.longitude, mskc2.Unom, mskc2.hda);
//�����-�����
cl();
br("������� �����-����� \n\n�� " + mskc1.locationsName + " �� �����");
nl();
calculations(mskc1.latitude, mskc1.longitude, vessel.latitude, vessel.longitude, vessel.Unom, vessel.hda);
//calculations(42.40, 133.02, vessel.latitude, vessel.longitude, vessel.Unom, vessel.hda);
cl();
br("�� " + mskc2.locationsName + " �� �����");
nl();
calculations(mskc2.latitude, mskc2.longitude, vessel.latitude, vessel.longitude, vessel.Unom, vessel.hda);
//calculations(54.43, 20.44, vessel.latitude, vessel.longitude, vessel.Unom, vessel.hda);
cl();
}