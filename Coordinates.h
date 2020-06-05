#include <iostream>
using namespace std;
class Coordinates {
public:
	int
		hda;			 //высота прямолинейной антенны
	double
		Unomt,			 //номинальная мощность
		Unomu,			 //номинальная мощность
		Unomc,			 //номинальная мощность
		latitude,		 //широта
		longitude;		 //долгота
	string
		latitudeString,	 //северная или южная
		longitudeString, //западная или восточная
		locationsName;	 //название локации

	Coordinates(double  lat, double  lon, string name, double Unt, double Unu, double Unc, int hd) {
		latitude = lat; longitude = lon; locationsName = name; Unomt = Unt; Unomu = Unu; Unomc = Unc; hda = hd;
		if (lat < 0) latitudeString = "южной"; else latitudeString = "северной";
		if (lon < 0) longitudeString = "западной"; else longitudeString = "восточной";
		cout << "Координаты " << locationsName << ": \n" << latitude << " градусов " << latitudeString << " широты " << longitude << " градусов " << longitudeString << " долготы\n";
		cout << "Номинальная мощность принимающей радиостанции для ТФ: \n" << Unomt << " мкВ\n";
		cout << "Номинальная мощность принимающей радиостанции для УБПЧ: \n" << Unomu << " мкВ\n";
		cout << "Номинальная мощность принимающей радиостанции для ЦИВ: \n" << Unomc << " мкВ\n";
		cout << "Высота прямолинейной антенны: \n" << hda << " м\n";
	}
	~Coordinates() {}
};