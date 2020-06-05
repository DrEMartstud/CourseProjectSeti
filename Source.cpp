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
	cout << "При вычислениях разница между полученными АВ составила " << abs(parameters.ABdegree - parameters.ABradian) << "км, что можно считать незначительной погрешностью.\n";
	}
	cout << "В целях повышения точности расчетов я буду использовать АВ, полученную через радианы.\n";
nl();
	parameters.calculateAlpha(latFrom, lonFrom, lonTo, parameters.cDegree);	 //азимут АВ
	parameters.calculateBeta(latTo, lonFrom, lonTo, parameters.cDegree);	//азимут ВА
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
	
	
	
	
	//bool fromKp = true; //если нужны дефолтные значения
	bool fromKp = false; //если нужно вручную вводить
	

//обьявления переменных
	double
		latV, lonV,	    //широта и долгота судна (v - vessel)
		lat1m, lon1m,   //широта и долгота первого мскц (1m - first mskc)
		lat2m, lon2m,   //широта и долгота второго мскц (2m - second mskc)
		UnVu, UnVc, UnVt, Un1mc, Un1mt, Un1mu, Un2mc, Un2mt, Un2mu;//номинальная мощность приемника
	string
		nameV,          //название судна
		name1m,			//город1
		name2m;			//город2
	int
		hdv, hm1, hm2;  //высота приемника
//присваивание значений
	if (fromKp) {
		latV = 39.43, lonV = 131.11; UnVt = 0.7; UnVc = 0.7; UnVu = 4; nameV = "Судна Победа"; hdv = 9; cout << "Дефолтное значение судна\n";
		lat1m = 42.45; lon1m = 133.02; name1m = "БРСТ в г.Владивосток"; hm1 = 12.5; Un1mu = UnVu; Un1mc = UnVc; Un1mt = UnVt; cout << "Дефолтное значение БРСТ1\n";
		lat2m = 54.45; lon2m = 20.35; name2m = "БРСТ в г.Калининград"; hm2 = 11; Un2mu = UnVu; Un2mc = UnVc; Un2mt = UnVt; cout << "Дефолтное значение БРСТ2\n";
	}
	else {
		br("Ввод исходных данных для судна (name, lat, lon, Unom, hda)");
		cout << "Введите название судна                           : "; cin >> nameV; nl(); 
		cout << "Введите широту судна (lat)           (формат d.m): "; cin >> latV; nl();
		cout << "Введите долготу судна (lon)          (формат d.m): "; cin >> lonV; nl();
		cout << "Введите высоту прямолинейной антенны        (в м): "; cin >> hdv; nl();
		cout << "Введите Unom для  ТФ                        (мкВ): "; cin >> UnVt; nl();
		cout << "Введите Unom для  УБПЧ                      (мкВ): "; cin >> UnVu; nl();
		cout << "Введите Unom для  ЦИВ                       (мкВ): "; cin >> UnVc; nl();
		nameV = "Судна " + nameV;

		nl();
		br("Ввод исходных данных для БРСТ1 (name, lat, lon, Unom, hda)");

		cout << "Введите город с ближайшей БРСТ                   : "; cin >> name1m; nl();
		cout << "Введите широту ближайшей БРСТ (lat)  (формат d.m): "; cin >> lat1m; nl();
		cout << "Введите долготу ближайшей БРСТ (lon) (формат d.m): "; cin >> lon1m; nl();
		cout << "Введите высоту прямолинейной антенны        (в м): "; cin >> hm1; nl();
		cout << "Введите Unom для  ТФ                        (мкВ): "; cin >> Un1mt; nl();
		cout << "Введите Unom для  УБПЧ                      (мкВ): "; cin >> Un1mu; nl();
		cout << "Введите Unom для  ЦИВ                       (мкВ): "; cin >> Un1mc; nl();

		name1m = "БРСТ1 в г." + name1m;
		nl();
		br("Ввод исходных данных для БРСТ2 (name, lat, lon, Unom, hda)");
		cout << "Введите город с дальнейшей БРСТ                  : "; cin >> name2m; nl();
		cout << "Введите широту дальней БРСТ (lat)    (формат d.m): "; cin >> lat2m; nl();
		cout << "Введите долготу дальней БРСТ (lon)   (формат d.m): "; cin >> lon2m; nl();
		cout << "Введите высоту прямолинейной антенны        (в м): "; cin >> hm2; nl();
		cout << "Введите Unom для  ТФ                        (мкВ): "; cin >> Un2mt; nl();
		cout << "Введите Unom для  УБПЧ                      (мкВ): "; cin >> Un2mu; nl();
		cout << "Введите Unom для  ЦИВ                       (мкВ): "; cin >> Un2mc; nl();

		name2m = "БРСТ2 в г." + name2m;
		nl();
	}
cl();
	
	
//расчеты Coordinates(lat, lon, name, Unt, Unu, Unc, hd)
	Coordinates vessel(latV, lonV, nameV, UnVt, UnVu, UnVc, hdv);
nl();
	Coordinates mskc1(lat1m, lon1m, name1m, Un1mt, Un1mu, Un1mc, hm1);
nl();
	Coordinates mskc2(lat2m, lon2m, name2m, Un2mt, Un2mu, Un2mc, hm2);
nl();
	

cl();
//судно-берег  calculations(latFrom, lonFrom, latTo, lonTo, Unt, Unu, Unc, hd)
br("Расчеты судно - берег \n\nОт судна до " + mskc1.locationsName);
nl();
calculations(vessel.latitude, vessel.longitude, mskc1.latitude, mskc1.longitude, mskc1.Unomt, mskc1.Unomu, mskc1.Unomc, mskc1.hda);
cl();
br("От судна до " + mskc2.locationsName);
nl();
calculations(vessel.latitude, vessel.longitude, mskc2.latitude, mskc2.longitude, mskc2.Unomt, mskc2.Unomu, mskc2.Unomc, mskc2.hda);
//берег-судно
cl();
br("Расчеты берег-судно \n\nОт " + mskc1.locationsName + " до судна");
nl();
calculations(mskc1.latitude, mskc1.longitude, vessel.latitude, vessel.longitude, vessel.Unomt, vessel.Unomu, vessel.Unomc, vessel.hda);
//calculations(42.40, 133.02, vessel.latitude, vessel.longitude, vessel.Unom, vessel.hda);
cl();
br("От " + mskc2.locationsName + " до судна");
nl();
calculations(mskc2.latitude, mskc2.longitude, vessel.latitude, vessel.longitude, vessel.Unomt, vessel.Unomu, vessel.Unomc, vessel.hda);
//calculations(54.43, 20.44, vessel.latitude, vessel.longitude, vessel.Unom, vessel.hda);
cl();
}