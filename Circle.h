//Circle.h

#pragma once
#include "Geometric_figures.h"

class Circle : public virtual Shape
{
protected:
	int Radius;
	string Cname;
public:
	Circle(int X = 22, int Y = 10,
		string Name = "PointC:",
		int rad = 6,
		string CName = "Circle:") :Shape(X, Y, Name),
		Radius(rad), Cname(CName) {};
	void Show()
	{		
		GoToXY((y - Radius)* scale_y, x - Radius - 2);
		cout << Cname << " Radius = " << Radius ;
		GoToXY((y - Radius) * scale_y, x - Radius - 1);
		cout << name << " x = " << x << ", y = " << y;
		Picture();
	}
	void Picture();
	void Save();
	void Load();
	double Circle_formula(int i, int j);
	Circle InFile();//извлечение данных из файла


};

double Circle::Circle_formula(int i, int j)
{
	double Form = pow(i, 2) / pow(Radius, 2) + pow(j, 2) / pow(Radius * scale_y, 2);
	return Form;
}

void Circle::Picture() //рисование фигуры согласно заданным параметрам
{
	GoToXY(y * scale_y - Radius * scale_y, x - Radius);
	int row = 0;
	for (int i = Radius; i >= -Radius; i--)
	{
		for (int j = -Radius * scale_y; j <= Radius * scale_y; j++)
		{
			if (ABS(Circle_formula(i, j) - 1) < 0.12)
			{
				cout << "*"; Sleep(100);
			}
			else cout << " ";
		}
		cout << "\n";
		row++;
		GoToXY(y * scale_y - Radius * scale_y, x - Radius + row);		
	}	
}

inline void Circle::Save()
{
	//сперва проверяем, чтобы не было дублирования
	fstream infile;
	infile.open("Geometric_figures.txt", ios::in);
	if (!infile) { perror("infile_error"); exit(0); }
	string s;
	while (!infile.eof())
	{
		getline(infile, s);
		string s_poisk = "Circle";
		if (s.find(s_poisk) < s.size())//если в просматриваемой строке есть информация об окружности, Circle
		{
			string s1 = "Name: " + Cname + " X = " + IntToStr(x) + "; Y = "
				+ IntToStr(y) + "; radius = " + IntToStr(Radius) + ";";
			if (s1 == s)
			{
				infile.close(); return;
			}
		}
	}
	
	fstream outfile;
	outfile.open("Geometric_figures.txt", ios::out | ios::app);
	if (!outfile) { perror("outfile_error"); exit(0); }
	outfile << "Name: " << Cname << " X = " << x << "; Y = "
		<< y << "; radius = " << Radius << ";\n";
	outfile.close();
}

inline void Circle::Load()
{
	Circle S1 = InFile();
	cout << "\n\t" << Cname << " radius = " << Radius;
	cout << "\n\t" << name << " x = " << x << ", y = " << y;
}

inline Circle Circle::InFile()//извлечение данных из файла
{
	fstream infile;
	infile.open("Geometric_figures.txt", ios::in);
	if (!infile) { perror("infile_error"); exit(0); }
	string s;
	int x_int;
	int y_int;
	int radius_int;
	while (!infile.eof())
	{
		getline(infile, s);
		string s_poisk = "Circle";
		if (s.find(s_poisk) < s.size())//если в просматриваемой строке есть информация об окружности, Circle

		{
			//вытаскиваем из общей информации параметр X, но в символьном виде
			string x_str = OutString(s, "X = ");
			//преобразовываем string x_str в int
			x_int = StringToInt(x_str, x_str.size());
			
			string y_str = OutString(s, "Y = ");
			y_int = StringToInt(y_str, y_str.size());
			
			string radius_str = OutString(s, "radius = ");
			radius_int = StringToInt(radius_str, radius_str.size());			
		}
	}
	return Circle(x_int, y_int, "PointC", radius_int, "Circle:");
}