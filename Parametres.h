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
	double hda;					    	 //высота прямолинейной антенны 
	double Unomt;						 //уровень сигнала на входе 
	double Unomc;						 //уровень сигнала на входе
	double Unomu;						 //уровень сигнала на входе
	double Uct1;						 //номинальный уровень сигнала на входе, определяемый заданным отношением сигнал/помеха 
	double Uct2;						 //номинальный уровень сигнала на входе, определяемый заданным отношением сигнал/помеха 
	double Ucu1;						 //номинальный уровень сигнала на входе, определяемый заданным отношением сигнал/помеха 
	double Ucu2;						 //номинальный уровень сигнала на входе, определяемый заданным отношением сигнал/помеха 
	double Ucc1;						 //номинальный уровень сигнала на входе, определяемый заданным отношением сигнал/помеха 
	double Ucc2;						 //номинальный уровень сигнала на входе, определяемый заданным отношением сигнал/помеха 
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
	double P1t;							 //cредняя мощность РПдУ в кВт вариант 1
	double P2t;							 //cредняя мощность РПдУ в кВт вариант 2
	double P1u;							 //cредняя мощность РПдУ в кВт вариант 1
	double P2u;							 //cредняя мощность РПдУ в кВт вариант 2
	double P1c;							 //cредняя мощность РПдУ в кВт вариант 1
	double P2c;							 //cредняя мощность РПдУ в кВт вариант 2
	double Eat1;							 //напряженность поля в точке приема В/м вариант 1
	double Eat2;							 //напряженность поля в точке приема В/м вариант 2
	double Eau1;							 //напряженность поля в точке приема В/м вариант 1
	double Eau2;							 //напряженность поля в точке приема В/м вариант 2
	double Eac1;							 //напряженность поля в точке приема В/м вариант 1
	double Eac2;							 //напряженность поля в точке приема В/м вариант 2
	//переменные для расчетов
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
	
		bra( "Для однополосной телефонии");
		cout << "Unom = " << Unomt << " мкВ\n";
		cout << "1) Uc = Unom * (1 + |3|) = " << Unomt << " * " << Gvh1 << " = " << Uct1 / 10 << " В * 10^-5\n"; if (Unt > Uct1) {Uct1 = Unt; cout << "Uc < Un => Uc = " << Uct1 / 10 << " В * 10^-5\n";}
		cout << "2) Uc = Unom * (1 - |3|) = " << Unomt << " * " << Gvh2 << " = " << Uct2 / 10 << " В * 10^-5\n"; if (Unt > Uct2) {Uct2 = Unt; cout << "Uc < Un => Uc = " << Uct2 / 10 << " В * 10^-5\n";}
		bra("Для ЦИВ");
		cout << "Unom = " << Unomc << " мкВ\n";
		cout << "1) Uc = Unom * (1 + |3|) = " << Unomc << " * " << Gvh1 << " = " << Ucc1 / 10 << " В * 10^-5\n"; if (Unc > Ucc1) {Ucc1 = Unc; cout << "Uc < Un => Uc = " << Ucc1 / 10 << " В * 10^-5\n";}
		cout << "2) Uc = Unom * (1 - |3|) = " << Unomc << " * " << Gvh2 << " = " << Ucc2 / 10 << " В * 10^-5\n"; if (Unc > Ucc2) {Ucc2 = Unc; cout << "Uc < Un => Uc = " << Ucc2 / 10 << " В * 10^-5\n";}
		bra("Для УБПЧ");
		cout << "Unom = " << Unomu << " мкВ\n";
		cout << "1) Uc = Unom * (1 + |3|) = " << Unomu << " * " << Gvh1 << " = " << Ucu1 / 10 << " В * 10^-5\n"; if (Unu > Ucu1) {Ucu1 = Unu; cout << "Uc < Un => Uc = " << Ucu1 / 10 << " В * 10^-5\n";}
		cout << "2) Uc = Unom * (1 - |3|) = " << Unomu << " * " << Gvh2 << " = " << Ucu2 / 10 << " В * 10^-5\n"; if (Unu > Ucu2) {Ucu2 = Unu; cout << "Uc < Un => Uc = " << Ucu2 / 10 << " В * 10^-5\n";}
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
		Eat1 = 2 * Uct1 / hda * pow(10, -5);
cout << "Для ТФ\n";
		cout << " 1) Ea = " << Eat1 << " В/м\n";
		Eat2 = 2 * Uct2 / hda * pow(10, -5);
		cout << " 2) Ea = " << Eat2 << " В/м\n";
		
		Eac1 = 2 * Ucc1 / hda * pow(10, -5);
cout << "Для ЦИВ\n";
		cout << " 1) Ea = " << Eac1 << " В/м\n";
		Eac2 = 2 * Ucc2 / hda * pow (10, -5);
		cout << " 2) Ea = " << Eac2 << " В/м\n";

		Eau1 = 2 * Ucu1 / hda * pow(10, -5);
cout << "Для УБПЧ\n";
		cout << " 1) Ea = " << Eau1 << " В/м\n";
		Eau2 = 2 * Ucu2 / hda * pow(10, -5);
		cout << " 2) Ea = " << Eau2 << " В/м\n";
	}
	virtual void calculateP() {
		bra("Средняя мощность радиоустановки P");
		double tmp = (N * d) / (71.6 * pow(0.8, N - 2) * exp(-y * (N - 1)));
		//P1 = pow((Ea1 * N * d) / (71.6 * pow(0.8, N - 2) * exp(-y * (N - 1))), 2);
		P1t = pow(Eat1 * tmp, 2);
cout << "Для ТФ\n";
		cout << " 1) P = (" << Eat1 << " * " << tmp << ")^2 = " << P1t << " Вт\n";
		P2t = pow(Eat2 * tmp, 2);
		cout << " 2) P = (" << Eat2 << " * " << tmp << ")^2 = " << P2t << " Вт\n";
cout << "Для ЦИВ\n";
		P1c = pow(Eac1 * tmp, 2);
		cout << " 1) P = (" << Eac1 << " * " << tmp << ")^2 = " << P1c << " Вт\n";
		P2c = pow(Eac2 * tmp, 2);
		cout << " 2) P = (" << Eac2 << " * " << tmp << ")^2 = " << P2c << " Вт\n";
cout << "Для УБПЧ\n";
		P1u = pow(Eau1 * tmp, 2);
		cout << " 1) P = (" << Eau1 << " * " << tmp << ")^2 = " << P1u << " Вт\n";
		P2u = pow(Eau2 * tmp, 2);
		cout << " 2) P = (" << Eau2 << " * " << tmp << ")^2 = " << P2u << " Вт\n";

	}

	virtual void getInfo() {
		cout << "\n";
		bra("Дано:");
		cout << "h = " << h << " - высота отражающего слоя атмосферы \n";
		cout << "y = " << y << " - коэффициент поглощения радиоволн при отражении\n";
		cout << "hда = " << hda << " - действующая высота приемной антенны в м\n";
		cout << "R = " << R << " - радиус земли\n";
		cout << "Uс ном = " << Unomt << " мкВ - номинальный уровень сигнала на входе для ТФ\n";
		cout << "Uс ном = " << Unomu << " мкВ - номинальный уровень сигнала на входе для УБПЧ\n";
		cout << "Uс ном = " << Unomc << " мкВ - номинальный уровень сигнала на входе для ЦИВ\n";
		cout << "Uc1 = " << Uct1 << " - уровень сигнала на входе для ТФ\n";
		cout << "Uc2 = " << Uct2 << " - уровень сигнала на входе для ТФ\n";
		cout << "Uc1 = " << Ucu1 << " - уровень сигнала на входе для УБПЧ\n";
		cout << "Uc2 = " << Ucu2 << " - уровень сигнала на входе для УБПЧ\n";
		cout << "Uc1 = " << Ucc1 << " - уровень сигнала на входе для ЦИВ\n";
		cout << "Uc2 = " << Ucc2 << " - уровень сигнала на входе для ЦИВ\n";
	}
	~Parameters() {}

};
