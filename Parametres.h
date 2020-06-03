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
	//дано
	int hda;					    	 //высота прямолинейной антенны 
	double Unom;					 //уровень сигнала на входе 
	double Uc1;							 //номинальный уровень сигнала на входе, определяемый заданным отношением сигнал/помеха вариант 1
	double Uc2;							 //номинальный уровень сигнала на входе, определяемый заданным отношением сигнал/помеха вариант 2
	const int h = 300;					 //высота отражающего слоя атмосферы 
	const double y = 1.2;				 //коэффициент поглощения радиоволн при отражении
	const int R = 6371;					 //радиус земли
	const int G = 1;					 //коэффициент усиления передающей антенны
	//вычисляется по ходу решения
	int ABdegree;						 //длина радиотрассы
	int ABradian;						 //длина радиотрассы, но в радианах
	int N;					   			 //число скачков
	double cRadian;						 //точка сферического треугольника АВС (стык всех дуг наверху)
	double cDegree;						 //тоже самое, но в градусах
	double alpha;						 //Азимут радиотрассы из точки А
	double beta;						 //Азимут радиотрассы из точки B
	double d;							 //путь, проходимый радиолучом при односкачковом распространении по трассе с центральным углом фи 
	double P1;							 //cредняя мощность РПдУ в кВт вариант 1
	double P2;							 //cредняя мощность РПдУ в кВт вариант 2
	double Ea1;							 //напряженность поля в точке приема В/м вариант 1
	double Ea2;							 //напряженность поля в точке приема В/м вариант 2
	//переменные для расчетов
	double revLatA, revLatB, lonSub;
	Parameters() {}
	
	virtual void initiateHda(int hd) {
		hda = hd;
	}
	virtual void initiateUc(double Un) {
		Unom = Un;
		Uc1 = Un * 1.5;
		Uc2 = Un;
		cout << "Unom = " << Unom << " мкВ\n";
		//cout << "Для однополосной телефонии\n";
		cout << "1) Uc = Unom * (1 + 0.5) = " << Unom << " * 1.5 = " << Uc1 << " мкВ\n";
		cout << "2) Uc = Unom * (1 - 0.5) = " << Unom << " * 0.5 = " << Unom * 0.5 << " мкВ < " << Unom << " => Uc = " << Unom << " мкВ\n";
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
	virtual void calculateC(double latA, double  lonA, double  latB, double  lonB) {  // ф и lat - широта. пси и lon - долгота
		revLatA = coord(90.0 - latA); revLatB = coord(90.0 - latB); lonSub = coord(abs(lonA - lonB));
		cout << "A = 90 - " << latA << " = " << revLatA << "\n";
		cout << "B = 90 - " << latB << " = " << revLatB << "\n";
		cout << "y = " << lonA << " - " << lonB << " = " << lonSub << "\n";
		cout << "c = arccos(cos(" << revLatA << ") * cos(" << revLatB << ") + sin(" << revLatA << ") * sin(" << revLatB << ") * cos(" << lonSub << ") )\n";
		cRadian = acos(cos(fromDegreesToRadian(revLatA)) * cos(fromDegreesToRadian(revLatB)) + sin(fromDegreesToRadian(revLatA)) * sin(fromDegreesToRadian(revLatB)) * cos(fromDegreesToRadian(abs(lonSub))));
		cDegree = fromRadianToDegrees(cRadian);
		cout << "c = " << cDegree << " градусов или c = " << cRadian << " радиан\n";
	}

	virtual void calculateAB(double cd, double cr) {
		ABradian = cr * R; ABdegree = cd * 111;
		bra("Рассчитаем AB через градусы и радианы.");
		cout << "AB через формулу для градусов = 111 * " << cDegree << " = " << ABdegree << "км\n";
		cout << "AB через формулу для радиан = R * " << cRadian << " = " << ABradian << "км\n";
	}

	virtual void calculateN() {
		N = floor(ABradian / 4000 + 1);
		cout << "Число скачков n = " << ABradian << " / 4000 = " << N << "\n";
	}

	virtual void calculateAlpha(double latA, double lonA, double lonB, double c) {
		//alpha = fromRadianToDegrees(asin((sin(revLatA) * sin(lonSub)) / sin(c)));

		alpha = abs(fromRadianToDegrees((sin(fromDegreesToRadian(revLatA)) * sin(fromDegreesToRadian(lonSub))) / sin(c)));
		cout << "Азимут радиотрассы из точки A Аlpha = arcsin(sin(90 - " << latA << ") * sin(" << lonSub << ")/sin(" << c << ")) = " << alpha << "\n";
	}

	virtual void calculateBeta(double latB, double lonA, double lonB, double c) {
		beta = 360 - abs(fromRadianToDegrees((sin(fromDegreesToRadian(revLatB)) * sin(fromDegreesToRadian(lonSub))) / sin(c)));
		cout << "Азимут радиотрассы из точки В Beta = 360 - arcsin(sin(90 - " << latB << ") * sin(" << lonSub << ")/sin(" << c << ")) = " << beta << "\n";
	}

	virtual void calculateD() {
		bra("Путь d, проходимый радиолучом при односкачковом распространении по трассе с центральным углом фи");
		d = 2 * pow((4.0 * R * pow(sin(fromDegreesToRadian(ABradian / 222.4)), 2) * (R + h) + pow(h, 2)), 0.5);
		cout << "d = sqrt( (4 * " << R << " *  sin(" << ABradian / 222.4 << ")^2 * (" << R << " + " << h << ") + " << h << "^2 ) = " << d << " км\n";

	}

	virtual void calculateEa() {
		//cout << "Ea = 71.6 * (" << P << " * " << G << ")^0.5 * 0.8^" << N - 2 << " * e^(" << -y << " * " << N - 1 << ") / (" << N << " * " << d << ")\n";
		//Ea = (71, 6 * pow((P * G), 0.5) * pow(0.8, (N - 2)) * exp((-y) * (N - 1))) / (N * d);
		bra("Напряженность поля в точке приема Ea = 2 *  Uc * 10^-6 / hda");

		Ea1 = 2 * Uc1 / hda;
		cout << " 1) Ea = " << Ea1 << " В/м\n";
		Ea2 = 2 * Uc2 / hda;
		cout << " 2) Ea = " << Ea2 << " В/м\n";
	}
	virtual void calculateP() {
		bra("Средняя мощность радиоустановки P");
		double tmp = (N * d) / (71.6 * pow(0.8, N - 2) * exp(-y * (N - 1)));
		//P1 = pow((Ea1 * N * d) / (71.6 * pow(0.8, N - 2) * exp(-y * (N - 1))), 2);
		P1 = pow(Ea1 * tmp, 2);
		cout << " 1) P = (" << Ea1 << " * " << tmp << ")^2 = " << P1 << " кВт\n";
		P2 = pow(Ea2 * tmp, 2);
		cout << " 2) P = (" << Ea2 << " * " << tmp << ")^2 = " << P2 << " кВт\n";
	}

	virtual void getInfo() {
		cout << "\n";
		bra("Дано:");
		cout << "h = " << h << " - высота отражающего слоя атмосферы \n";
		cout << "y = " << y << " - коэффициент поглощения радиоволн при отражении\n";
		cout << "hда = " << hda << " - действующая высота приемной антенны в м\n";
		cout << "R = " << R << " - радиус земли\n";
		cout << "Uс ном = " << Unom << " мкВ - номинальный уровень сигнала на входе \n";
		cout << "Uc1 = " << Uc1 << " - уровень сигнала на входе\n";
		cout << "Uc2 = " << Uc2 << " - уровень сигнала на входе\n";
	}
	~Parameters() {}

};
