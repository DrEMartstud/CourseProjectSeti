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
	double hda;					    	 //������ ������������� ������� 
	double Unomt;						 //������� ������� �� ����� 
	double Unomc;						 //������� ������� �� �����
	double Unomu;						 //������� ������� �� �����
	double Uct1;						 //����������� ������� ������� �� �����, ������������ �������� ���������� ������/������ 
	double Uct2;						 //����������� ������� ������� �� �����, ������������ �������� ���������� ������/������ 
	double Ucu1;						 //����������� ������� ������� �� �����, ������������ �������� ���������� ������/������ 
	double Ucu2;						 //����������� ������� ������� �� �����, ������������ �������� ���������� ������/������ 
	double Ucc1;						 //����������� ������� ������� �� �����, ������������ �������� ���������� ������/������ 
	double Ucc2;						 //����������� ������� ������� �� �����, ������������ �������� ���������� ������/������ 
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
	double P1t;							 //c������ �������� ���� � ��� ������� 1
	double P2t;							 //c������ �������� ���� � ��� ������� 2
	double P1u;							 //c������ �������� ���� � ��� ������� 1
	double P2u;							 //c������ �������� ���� � ��� ������� 2
	double P1c;							 //c������ �������� ���� � ��� ������� 1
	double P2c;							 //c������ �������� ���� � ��� ������� 2
	double Eat1;							 //������������� ���� � ����� ������ �/� ������� 1
	double Eat2;							 //������������� ���� � ����� ������ �/� ������� 2
	double Eau1;							 //������������� ���� � ����� ������ �/� ������� 1
	double Eau2;							 //������������� ���� � ����� ������ �/� ������� 2
	double Eac1;							 //������������� ���� � ����� ������ �/� ������� 1
	double Eac2;							 //������������� ���� � ����� ������ �/� ������� 2
	//���������� ��� ��������
	double revLatA, revLatB, lonSub;
	Parameters() {}
	
	virtual void initiateHda(double hd) {
		hda = hd / 2000;
	}
	virtual void initiateUc(double Unt, double Unu, double Unc) {
		int Gvh1 = 4, Gvh2 = 2;
		Unomt = Unt;
		Uct1 = Unt * Gvh1;
		Uct2 = Unt * Gvh2;
		Unomu = Unu;
		Ucu1 = Unu * Gvh1;
		Ucu2 = Unu * Gvh2;
		Unomc = Unc;
		Ucc1 = Unc * Gvh1;
		Ucc2 = Unc * Gvh2;
	
		bra( "��� ������������ ���������");
		cout << "Unom = " << Unomt << " ���\n";
		cout << "1) Uc = Unom * (1 + |3|) = " << Unomt << " * " << Gvh1 << " = " << Uct1 / 10 << " � * 10^-5\n"; if (Unt > Uct1) {Uct1 = Unt; cout << "Uc < Un => Uc = " << Uct1 / 10 << " � * 10^-5\n";}
		cout << "2) Uc = Unom * (1 - |3|) = " << Unomt << " * " << Gvh2 << " = " << Uct2 / 10 << " � * 10^-5\n"; if (Unt > Uct2) {Uct2 = Unt; cout << "Uc < Un => Uc = " << Uct2 / 10 << " � * 10^-5\n";}
		bra("��� ���");
		cout << "Unom = " << Unomc << " ���\n";
		cout << "1) Uc = Unom * (1 + |3|) = " << Unomc << " * " << Gvh1 << " = " << Ucc1 / 10 << " � * 10^-5\n"; if (Unc > Ucc1) {Ucc1 = Unc; cout << "Uc < Un => Uc = " << Ucc1 / 10 << " � * 10^-5\n";}
		cout << "2) Uc = Unom * (1 - |3|) = " << Unomc << " * " << Gvh2 << " = " << Ucc2 / 10 << " � * 10^-5\n"; if (Unc > Ucc2) {Ucc2 = Unc; cout << "Uc < Un => Uc = " << Ucc2 / 10 << " � * 10^-5\n";}
		bra("��� ����");
		cout << "Unom = " << Unomu << " ���\n";
		cout << "1) Uc = Unom * (1 + |3|) = " << Unomu << " * " << Gvh1 << " = " << Ucu1 / 10 << " � * 10^-5\n"; if (Unu > Ucu1) {Ucu1 = Unu; cout << "Uc < Un => Uc = " << Ucu1 / 10 << " � * 10^-5\n";}
		cout << "2) Uc = Unom * (1 - |3|) = " << Unomu << " * " << Gvh2 << " = " << Ucu2 / 10 << " � * 10^-5\n"; if (Unu > Ucu2) {Ucu2 = Unu; cout << "Uc < Un => Uc = " << Ucu2 / 10 << " � * 10^-5\n";}
	Uct1 /= 10;Uct2 /= 10;Ucu1 /= 10;Ucu2 /= 10;Ucc1 /= 10;Ucc2 /= 10;
	
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
		Eat1 = 2 * Uct1 / hda * pow(10, -5);
cout << "��� ��\n";
		cout << " 1) Ea = " << Eat1 << " �/�\n";
		Eat2 = 2 * Uct2 / hda * pow(10, -5);
		cout << " 2) Ea = " << Eat2 << " �/�\n";
		
		Eac1 = 2 * Ucc1 / hda * pow(10, -5);
cout << "��� ���\n";
		cout << " 1) Ea = " << Eac1 << " �/�\n";
		Eac2 = 2 * Ucc2 / hda * pow (10, -5);
		cout << " 2) Ea = " << Eac2 << " �/�\n";

		Eau1 = 2 * Ucu1 / hda * pow(10, -5);
cout << "��� ����\n";
		cout << " 1) Ea = " << Eau1 << " �/�\n";
		Eau2 = 2 * Ucu2 / hda * pow(10, -5);
		cout << " 2) Ea = " << Eau2 << " �/�\n";
	}
	virtual void calculateP() {
		bra("������� �������� �������������� P");
		double tmp = (N * d) / (71.6 * pow(0.8, N - 2) * exp(-y * (N - 1)));
		//P1 = pow((Ea1 * N * d) / (71.6 * pow(0.8, N - 2) * exp(-y * (N - 1))), 2);
		P1t = pow(Eat1 * tmp, 2);
cout << "��� ��\n";
		cout << " 1) P = (" << Eat1 << " * " << tmp << ")^2 = " << P1t << " ��\n";
		P2t = pow(Eat2 * tmp, 2);
		cout << " 2) P = (" << Eat2 << " * " << tmp << ")^2 = " << P2t << " ��\n";
cout << "��� ���\n";
		P1c = pow(Eac1 * tmp, 2);
		cout << " 1) P = (" << Eac1 << " * " << tmp << ")^2 = " << P1c << " ��\n";
		P2c = pow(Eac2 * tmp, 2);
		cout << " 2) P = (" << Eac2 << " * " << tmp << ")^2 = " << P2c << " ��\n";
cout << "��� ����\n";
		P1u = pow(Eau1 * tmp, 2);
		cout << " 1) P = (" << Eau1 << " * " << tmp << ")^2 = " << P1u << " ��\n";
		P2u = pow(Eau2 * tmp, 2);
		cout << " 2) P = (" << Eau2 << " * " << tmp << ")^2 = " << P2u << " ��\n";

	}

	virtual void getInfo() {
		cout << "\n";
		bra("����:");
		cout << "h = " << h << " - ������ ����������� ���� ��������� \n";
		cout << "y = " << y << " - ����������� ���������� ��������� ��� ���������\n";
		cout << "h�� = " << hda << " - ����������� ������ �������� ������� � �\n";
		cout << "R = " << R << " - ������ �����\n";
		cout << "U� ��� = " << Unomt << " ��� - ����������� ������� ������� �� ����� ��� ��\n";
		cout << "U� ��� = " << Unomu << " ��� - ����������� ������� ������� �� ����� ��� ����\n";
		cout << "U� ��� = " << Unomc << " ��� - ����������� ������� ������� �� ����� ��� ���\n";
		cout << "Uc1 = " << Uct1 << " - ������� ������� �� ����� ��� ��\n";
		cout << "Uc2 = " << Uct2 << " - ������� ������� �� ����� ��� ��\n";
		cout << "Uc1 = " << Ucu1 << " - ������� ������� �� ����� ��� ����\n";
		cout << "Uc2 = " << Ucu2 << " - ������� ������� �� ����� ��� ����\n";
		cout << "Uc1 = " << Ucc1 << " - ������� ������� �� ����� ��� ���\n";
		cout << "Uc2 = " << Ucc2 << " - ������� ������� �� ����� ��� ���\n";
	}
	~Parameters() {}

};
