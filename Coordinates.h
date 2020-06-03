#include <iostream>
using namespace std;
class Coordinates {
public:
	int
		hda;			 //������ ������������� �������
	double
		Unom,			 //����������� ��������
		latitude,		 //������
		longitude;		 //�������
	string
		latitudeString,	 //�������� ��� �����
		longitudeString, //�������� ��� ���������
		locationsName;	 //�������� �������

	Coordinates(double  lat, double  lon, string name, double Un, int hd) {
		latitude = lat; longitude = lon; locationsName = name; Unom = Un; hda = hd;
		if (lat < 0) latitudeString = "�����"; else latitudeString = "��������";
		if (lon < 0) longitudeString = "��������"; else longitudeString = "���������";
		cout << "���������� " << locationsName << ": \n" << latitude << " �������� " << latitudeString << " ������ " << longitude << " �������� " << longitudeString << " �������\n";
		cout << "����������� �������� ����������� ������������: \n" << Unom << " ���\n";
		cout << "������ ������������� �������: \n" << hda << " �\n";
	}
	~Coordinates() {}
};