//Ellipse.h

#pragma once
#include "Geometric_figures.h"

class Ellips : public virtual Shape
{
protected:
	int SemiAxis1; //полуось 1
	int SemiAxis2; //полуось 2
	string Ename; //имя
public:
	Ellips(int X = 22, int Y = 30,
		string Name = "PointE:",
		int SA1 = 5, 
		int SA2 = 8,
		string EName = "Ellipse:") :Shape(X, Y, Name),
		SemiAxis1(SA1), SemiAxis2(SA2), Ename(EName) {};
	void Show();
	
	double Ellips_formula(int i, int y);
	void Picture();
	void Save();
	void Load();
	Ellips InFile();//извлечение данных из файла
};

inline void Ellips::Show()
{
	{
		GoToXY((y - SemiAxis2) * scale_y, x - SemiAxis1 - 2);
		cout << Ename << " semi-axis1 = " << SemiAxis1 
			<< ", semi-axis2 = " << SemiAxis2 ;
		GoToXY((y - SemiAxis2) * scale_y, x - SemiAxis1 - 1);
		cout << name << " x = " << x << ", y = " << y;
	}
	Picture();
}

double Ellips::Ellips_formula(int i, int j) 
{
	double Form = pow(i, 2) / pow(SemiAxis1, 2) + pow(j, 2) / pow(SemiAxis2 * scale_y, 2);
		return Form;
}
void Ellips::Picture() //рисование фигуры согласно заданным параметрам
{
	
	GoToXY(y* scale_y - SemiAxis2* scale_y, x - SemiAxis1);
	int row = 0;
	for (int i = SemiAxis1; i >= -SemiAxis1; i--)
	{
		for (int j = - SemiAxis2* scale_y; j <=  SemiAxis2* scale_y; j++)
		{
			if (ABS(Ellips_formula(i, j) - 1) < 0.12)
			{
				cout << "*"; Sleep(100);
			}
			else cout << " ";
		}
		cout << "\n";
		row++;
		GoToXY(y * scale_y - SemiAxis2 * scale_y, x - SemiAxis1 + row);		
	}
}

inline void Ellips::Save()
{
	//сперва проверяем, чтобы не было дублирования
	fstream infile;
	infile.open("Geometric_figures.txt", ios::in);
	if (!infile) { perror("infile_error"); exit(0); }
	string s;
	while (!infile.eof())
	{
		getline(infile, s);
		string s_poisk = "Ellipse";
		if (s.find(s_poisk) < s.size())//если в просматриваемой строке есть информация об эллипсе, Ellipse
		{
			string s1 = "Name: " + Ename + " X = " + IntToStr(x)
				+ "; Y = " + IntToStr(y) + "; semi-axis1 = " + IntToStr(SemiAxis1)
				+ "; semi-axis2 = " + IntToStr(SemiAxis2) + ";";
			if (s1 == s)
			{
				infile.close(); return;
			}
		}
	}
	fstream outfile;
	outfile.open("Geometric_figures.txt", ios::out | ios::app);
	if (!outfile) { perror("outfile_error"); exit(0); }
	outfile << "Name: " << Ename << " X = " << x << "; Y = "
		<< y << "; semi-axis1 = " << SemiAxis1 << "; semi-axis2 = " << SemiAxis2 << ";\n";
	outfile.close();
}

inline void Ellips::Load()
{
	Ellips E1 = InFile();
	cout << "\n\t" << Ename << " semi-axis1 = " << SemiAxis1
		<< ", semi-axis2 = " << SemiAxis2;
	cout << "\n\t" << name << " x = " << x << ", y = " << y;
}

inline Ellips Ellips::InFile()//извлечение данных из файла
{
	fstream infile;
	infile.open("Geometric_figures.txt", ios::in);
	if (!infile) { perror("infile_error"); exit(0); }
	string s;
	int x_int = 0;
	int y_int = 0;
	int SemiAxis1_int = 0;
	int SemiAxis2_int = 0;
	while (!infile.eof())
	{
		getline(infile, s);
		string s_poisk = "Ellipse";
		if (s.find(s_poisk) < s.size())//если в просматриваемой строке есть информация об эллипсе, Ellipse
		{
			//вытаскиваем из общей информации параметр X, но в символьном виде
			string x_str = OutString(s, "X = ");
			//преобразовываем string x_str в int
			x_int = StringToInt(x_str, x_str.size());

			string y_str = OutString(s, "Y = ");
			y_int = StringToInt(y_str, y_str.size());

			string SemiAxis1_str = OutString(s, "semi-axis1 = ");
			SemiAxis1_int = StringToInt(SemiAxis1_str, SemiAxis1_str.size());
			
			string SemiAxis2_str = OutString(s, "semi-axis2 = ");
			SemiAxis2_int = StringToInt(SemiAxis2_str, SemiAxis2_str.size());
		}
	}
	return Ellips(x_int, y_int, "PointE", SemiAxis1_int, SemiAxis2_int, "Ellipse:");
}
