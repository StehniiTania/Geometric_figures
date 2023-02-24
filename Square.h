//Square.h

#include "Geometric_figures.h"
#pragma once

class Square : public virtual Shape
{
protected:
	int length;
	string Sname;
public:
	Square(int X = 3, int Y = 5,
		string Name = "PointS:",
		int Len = 10,
		string SName = "Square:") :Shape(X, Y, Name),
		length(Len), Sname(SName) {};
	void Show();
	void Picture();
	void Save();
	void Load();
	Square InFile();//извлечение данных из файла
};

inline void Square::Show() //вывод на экран параметров фигуры и ее изображение
{
	GoToXY(y, x - 2);
	cout << Sname << " length = " << length;
	GoToXY(y, x - 1);
	cout << name << " x = " << x << ", y = " << y;
	Picture();
}
void Square::Picture() //рисование фигуры согласно заданным параметрам
{
	GoToXY(y, x);
	for (int i = 0; i < length * scale_y; i++)
	{
		cout << "*"; Sleep(100);
	}
	for (int i = 1; i < length - 1; i++)
	{
		GoToXY(y + length * scale_y - 1, x + i);
		cout << "*"; Sleep(100);
	}
	for (int i = length * scale_y - 1; i > 0; i--)
	{
		GoToXY(y + i, x + length - 1);
		cout << "*"; Sleep(100);
	}
	for (int i = length - 1; i > 0; i--)
	{
		GoToXY(y, x + i);
		cout << "*"; Sleep(100);
	}

	GoToXY(y, x + length + 1);
	
}

inline void Square::Save()
{	
	//сперва проверяем, чтобы не было дублирования
	fstream infile;
	infile.open("Geometric_figures.txt", ios::in);
	if (!infile) { perror("infile_error"); exit(0); }
	string s;
	while (!infile.eof())
	{
		getline(infile, s);
		string s_poisk = "Square";
		if (s.find(s_poisk) < s.size())//если в просматриваемой строке есть информация о квадрате, Square
		{
			string s1 = "Name: " + Sname + " X = " + IntToStr(x)
				+ "; Y = " + IntToStr(y) + "; length = " + IntToStr(length) + ";";
			if (s1 == s)
			{  infile.close(); return; }							
		}
	}
	fstream outfile;
	outfile.open("Geometric_figures.txt", ios::out | ios::app);
	if (!outfile) { perror("outfile_error"); exit(0); }
	outfile << "Name: " << Sname << " X = " << x << "; Y = " 
		<< y << "; length = " << length << ";\n";
	outfile.close();
}

inline void Square::Load()
{
	Square S1 = InFile();
	cout << "\n\t" << Sname << " length = " << length;
	cout << "\n\t" << name << " x = " << x << ", y = " << y;	
}

inline Square Square::InFile()//извлечение данных из файла
{
	fstream infile;
	infile.open("Geometric_figures.txt", ios::in);
	if (!infile) { perror("infile_error"); exit(0); }
	string s;
	int x_int;
	int y_int;
	int length_int;
	while (!infile.eof())
	{
		getline(infile, s);
		string s_poisk = "Square";
		if (s.find(s_poisk) < s.size())//если в просматриваемой строке есть информация об окружности, Square
		{
			//вытаскиваем из общей информации параметр X, но в символьном виде
			string x_str = OutString(s, "X = ");
			//преобразовываем string x_str в int
			x_int = StringToInt(x_str, x_str.size());
			
			string y_str = OutString(s, "Y = ");
			y_int = StringToInt(y_str, y_str.size());
			
			string length_str = OutString(s, "length = ");
			length_int = StringToInt(length_str, length_str.size());
		}
	}
	return Square(x_int,y_int,"PointS",length_int,"Square:");
}