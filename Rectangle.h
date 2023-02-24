//Rectangle.h

#pragma once
#include "Geometric_figures.h"

class Rectangl : public virtual Shape
{
protected:
	int length1;
	int length2;
	string Rname;
public:
	Rectangl(int X = 3, int Y = 30,
		string Name = "PointR:",
		int len1 = 15,
		int len2 = 8,
		string RName = "Rectangle:") :Shape(X, Y, Name),
		length1(len1), length2(len2), Rname(RName) {};
	void Show();
	void Picture();
	void Save();
	void Load();
	Rectangl InFile();//извлечение данных из файла
};

inline void Rectangl::Show() //вывод на экран параметров фигуры и ее изображение
{
	GoToXY(y, x - 2);
	cout << Rname << " length1 = " << length1 << ", length2 = " << length2;
	GoToXY(y, x - 1);
	cout << name << " x = " << x << ", y = " << y;

	Picture();
}
void Rectangl::Picture() //рисование фигуры согласно заданным параметрам
{
	GoToXY(y, x);
	for (int i = 0; i < length1 * scale_y; i++)
	{
		cout << "*"; Sleep(100);
	}
	for (int i = 1; i < length2 - 1; i++)
	{
		GoToXY(y + length1 * scale_y - 1, x + i);
		cout << "*"; Sleep(100);
	}
	for (int i = length1 * scale_y - 1; i > 0; i--)
	{
		GoToXY(y + i, x + length2 - 1);
		cout << "*"; Sleep(100);
	}
	for (int i = length2 - 1; i > 0; i--)
	{
		GoToXY(y, x + i);
		cout << "*"; Sleep(100);
	}

	GoToXY(y, x + length2 + 1);	
}

inline void Rectangl::Save()
{
	//сперва провер€ем, чтобы не было дублировани€
	fstream infile;
	infile.open("Geometric_figures.txt", ios::in);
	if (!infile) { perror("infile_error"); exit(0); }
	string s;
	while (!infile.eof())
	{
		getline(infile, s);
		string s_poisk = "Rectangle";
		if (s.find(s_poisk) < s.size())//если в просматриваемой строке есть информаци€ о пр€моугольнике, Rectangle
		{
			string s1 = "Name: " + Rname + " X = " + IntToStr(x)
				+ "; Y = " + IntToStr(y) + "; length1 = " + IntToStr(length1)
				+ "; length2 = " + IntToStr(length2) + "; ";
			if (s1 == s)
			{
				infile.close(); return;
			}
		}
	}
	fstream outfile;
	outfile.open("Geometric_figures.txt", ios::out | ios::app);
	if (!outfile) { perror("outfile_error"); exit(0); }
	outfile << "Name: " << Rname << " X = " << x << "; Y = "
		<< y << "; length1 = " << length1 << "; length2 = " 
		<< length2 << "; \n";
	outfile.close();
}

inline void Rectangl::Load()
{
	Rectangl R1 = InFile();
	cout << "\n\t" << Rname << " length1 = " << length1 << ", length2 = " << length2;
	cout << "\n\t" << name << " x = " << x << ", y = " << y;
}
inline Rectangl Rectangl::InFile()//извлечение данных из файла
{
	fstream infile;
	infile.open("Geometric_figures.txt", ios::in);
	if (!infile) { perror("infile_error"); exit(0); }
	string s;
	int x_int = 0;
	int y_int = 0;
	int length1_int = 0;
	int length2_int = 0;
	while (!infile.eof())
	{
		getline(infile, s);
		string s_poisk = "Rectangle";
		if (s.find(s_poisk) < s.size())//если в просматриваемой строке есть информаци€ о пр€моугольнике, Rectangle

		{
			//вытаскиваем из общей информации параметр X, но в символьном виде
			string x_str = OutString(s, "X = ");
			//преобразовываем string x_str в int
			x_int = StringToInt(x_str, x_str.size());
			
			string y_str = OutString(s, "Y = ");
			y_int = StringToInt(y_str, y_str.size());
			
			string length1_str = OutString(s, "length1 = ");
			length1_int = StringToInt(length1_str, length1_str.size());
			
			string length2_str = OutString(s, "length2 = ");
			length2_int = StringToInt(length2_str, length2_str.size());
		}
	}
	return Rectangl(x_int, y_int, "PointS", length1_int, length2_int, "Rectangle:");
}