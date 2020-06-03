#define _USE_MATH_DEFINES

#include <cmath>
#include<iomanip>
#include<iostream>
#include <string>



using namespace std;
void bra(string header) {
	int i = header.length();
	for (int c = 0; c != i; c++) cout << "_";
	cout << endl;
	cout << header << endl;
	for (int c = 0; c != i; c++) cout << "_";
	cout << endl;
}
class Parameters {
public:
	//����
	int hda;					    	 //������ ������������� ������� 
	double Unom;					 //������� ������� �� ����� 
	double Uc1;							 //����������� ������� ������� �� �����, ������������ �������� ���������� ������/������ ������� 1
	double Uc2;							 //����������� ������� ������� �� �����, ������������ �������� ���������� ������/������ ������� 2
	const int h = 300;					 //������ ����������� ���� ��������� 
	const double y = 1.2;				 //����������� ���������� ��������� ��� ���������
	const int R = 6371;					 //������ �����
	const int G = 1;					 //����������� �������� ���������� �������
	//����������� �� ���� �������
	int ABdegree;						 //����� �����������
	int ABradian;						 //����� �����������, �� � ��������
	int N;					   			 //����� �������
	double cRadian;						 //����� ������������ ������������ ��� (���� ���� ��� �������)
	double cDegree;						 //���� �����, �� � ��������
	double alpha;						 //������ ����������� �� ����� �
	double beta;						 //������ ����������� �� ����� B
	double d;							 //����, ���������� ���������� ��� ������������� ��������������� �� ������ � ����������� ����� �� 
	double P1;							 //c������ �������� ���� � ��� ������� 1
	double P2;							 //c������ �������� ���� � ��� ������� 2
	double Ea1;							 //������������� ���� � ����� ������ �/� ������� 1
	double Ea2;							 //������������� ���� � ����� ������ �/� ������� 2
	//���������� ��� ��������
	double revLatA, revLatB, lonSub;
	Parameters() {}
	
	virtual void initiateHda(int hd) {
		hda = hd;
	}
	virtual void initiateUc(double Un) {
		Unom = Un;
		Uc1 = Un * 1.5;
		Uc2 = Un;
		cout << "Unom = " << Unom << " ���\n";
		//cout << "��� ������������ ���������\n";
		cout << "1) Uc = Unom * (1 + 0.5) = " << Unom << " * 1.5 = " << Uc1 << " ���\n";
		cout << "2) Uc = Unom * (1 - 0.5) = " << Unom << " * 0.5 = " << Unom * 0.5 << " ��� < " << Unom << " => Uc = " << Unom << " ���\n";
	}

	double fromRadianToDegrees(double rad) {
		return 180 / M_PI * rad;
	}
	double fromDegreesToRadian(double grad) {
		return M_PI / 180 * grad;
	}
	double coord(double number) {
		double integ;
		double fract = modf(number, &integ), ret = int(60 * fract) * 1.0 / 100 + integ;
		return ret;
	}
	virtual void calculateC(double latA, double  lonA, double  latB, double  lonB) {  // � � lat - ������. ��� � lon - �������
		revLatA = coord(90.0 - latA); revLatB = coord(90.0 - latB); lonSub = coord(abs(lonA - lonB));
		cout << "A = 90 - " << latA << " = " << revLatA << "\n";
		cout << "B = 90 - " << latB << " = " << revLatB << "\n";
		cout << "y = " << lonA << " - " << lonB << " = " << lonSub << "\n";
		cout << "c = arccos(cos(" << revLatA << ") * cos(" << revLatB << ") + sin(" << revLatA << ") * sin(" << revLatB << ") * cos(" << lonSub << ") )\n";
		cRadian = acos(cos(fromDegreesToRadian(revLatA)) * cos(fromDegreesToRadian(revLatB)) + sin(fromDegreesToRadian(revLatA)) * sin(fromDegreesToRadian(revLatB)) * cos(fromDegreesToRadian(abs(lonSub))));
		cDegree = fromRadianToDegrees(cRadian);
		cout << "c = " << cDegree << " �������� ��� c = " << cRadian << " ������\n";
	}

	virtual void calculateAB(double cd, double cr) {
		ABradian = cr * R; ABdegree = cd * 111;
		bra("���������� AB ����� ������� � �������.");
		cout << "AB ����� ������� ��� �������� = 111 * " << cDegree << " = " << ABdegree << "��\n";
		cout << "AB ����� ������� ��� ������ = R * " << cRadian << " = " << ABradian << "��\n";
	}

	virtual void calculateN() {
		N = floor(ABradian / 4000 + 1);
		cout << "����� ������� n = " << ABradian << " / 4000 = " << N << "\n";
	}

	virtual void calculateAlpha(double latA, double lonA, double lonB, double c) {
		//alpha = fromRadianToDegrees(asin((sin(revLatA) * sin(lonSub)) / sin(c)));

		alpha = abs(fromRadianToDegrees((sin(fromDegreesToRadian(revLatA)) * sin(fromDegreesToRadian(lonSub))) / sin(c)));
		cout << "������ ����������� �� ����� A �lpha = arcsin(sin(90 - " << latA << ") * sin(" << lonSub << ")/sin(" << c << ")) = " << alpha << "\n";
	}

	virtual void calculateBeta(double latB, double lonA, double lonB, double c) {
		beta = 360 - abs(fromRadianToDegrees((sin(fromDegreesToRadian(revLatB)) * sin(fromDegreesToRadian(lonSub))) / sin(c)));
		cout << "������ ����������� �� ����� � Beta = 360 - arcsin(sin(90 - " << latB << ") * sin(" << lonSub << ")/sin(" << c << ")) = " << beta << "\n";
	}

	virtual void calculateD() {
		bra("���� d, ���������� ���������� ��� ������������� ��������������� �� ������ � ����������� ����� ��");
		d = 2 * pow((4.0 * R * pow(sin(fromDegreesToRadian(ABradian / 222.4)), 2) * (R + h) + pow(h, 2)), 0.5);
		cout << "d = sqrt( (4 * " << R << " *  sin(" << ABradian / 222.4 << ")^2 * (" << R << " + " << h << ") + " << h << "^2 ) = " << d << " ��\n";

	}

	virtual void calculateEa() {
		//cout << "Ea = 71.6 * (" << P << " * " << G << ")^0.5 * 0.8^" << N - 2 << " * e^(" << -y << " * " << N - 1 << ") / (" << N << " * " << d << ")\n";
		//Ea = (71, 6 * pow((P * G), 0.5) * pow(0.8, (N - 2)) * exp((-y) * (N - 1))) / (N * d);
		bra("������������� ���� � ����� ������ Ea = 2 *  Uc * 10^-6 / hda");

		Ea1 = 2 * Uc1 / hda;
		cout << " 1) Ea = " << Ea1 << " �/�\n";
		Ea2 = 2 * Uc2 / hda;
		cout << " 2) Ea = " << Ea2 << " �/�\n";
	}
	virtual void calculateP() {
		bra("������� �������� �������������� P");
		double tmp = (N * d) / (71.6 * pow(0.8, N - 2) * exp(-y * (N - 1)));
		//P1 = pow((Ea1 * N * d) / (71.6 * pow(0.8, N - 2) * exp(-y * (N - 1))), 2);
		P1 = pow(Ea1 * tmp, 2);
		cout << " 1) P = (" << Ea1 << " * " << tmp << ")^2 = " << P1 << " ���\n";
		P2 = pow(Ea2 * tmp, 2);
		cout << " 2) P = (" << Ea2 << " * " << tmp << ")^2 = " << P2 << " ���\n";
	}

	virtual void getInfo() {
		cout << "\n";
		bra("����:");
		cout << "h = " << h << " - ������ ����������� ���� ��������� \n";
		cout << "y = " << y << " - ����������� ���������� ��������� ��� ���������\n";
		cout << "h�� = " << hda << " - ����������� ������ �������� ������� � �\n";
		cout << "R = " << R << " - ������ �����\n";
		cout << "U� ��� = " << Unom << " ��� - ����������� ������� ������� �� ����� \n";
		cout << "Uc1 = " << Uc1 << " - ������� ������� �� �����\n";
		cout << "Uc2 = " << Uc2 << " - ������� ������� �� �����\n";
	}
	~Parameters() {}

};
