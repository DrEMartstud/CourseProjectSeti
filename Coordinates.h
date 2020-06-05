#include <iostream>
using namespace std;
class Coordinates {
public:
	int
		hda;			 //������ ������������� �������
	double
		Unomt,			 //����������� ��������
		Unomu,			 //����������� ��������
		Unomc,			 //����������� ��������
		latitude,		 //������
		longitude;		 //�������
	string
		latitudeString,	 //�������� ��� �����
		longitudeString, //�������� ��� ���������
		locationsName;	 //�������� �������

	Coordinates(double  lat, double  lon, string name, double Unt, double Unu, double Unc, int hd) {
		latitude = lat; longitude = lon; locationsName = name; Unomt = Unt; Unomu = Unu; Unomc = Unc; hda = hd;
		if (lat < 0) latitudeString = "�����"; else latitudeString = "��������";
		if (lon < 0) longitudeString = "��������"; else longitudeString = "���������";
		cout << "���������� " << locationsName << ": \n" << latitude << " �������� " << latitudeString << " ������ " << longitude << " �������� " << longitudeString << " �������\n";
		cout << "����������� �������� ����������� ������������ ��� ��: \n" << Unomt << " ���\n";
		cout << "����������� �������� ����������� ������������ ��� ����: \n" << Unomu << " ���\n";
		cout << "����������� �������� ����������� ������������ ��� ���: \n" << Unomc << " ���\n";
		cout << "������ ������������� �������: \n" << hda << " �\n";
	}
	~Coordinates() {}
};