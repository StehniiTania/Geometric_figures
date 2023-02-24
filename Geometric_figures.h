//Geometric_figures.h

#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <cmath>
#include <sstream>

#define M_PI 3.14159265358979323846 //����� ��
#define ABS(X) (((X) < 0)? -(X) : X) //������ �����
#define scale_y 2 //����������� ��������������� �� ��� �

using namespace std;

class Shape  //����������� ����� �����
{
protected:
	int x, y;
	string name;
public:
	Shape(int X = 3, int Y = 3, string Name = "Point") :x(X), y(Y), name(Name) {};
	virtual void Show() = 0;	//������ ����������� �������
	virtual void Save() = 0;
	virtual void Load() = 0;
    virtual void Picture() = 0;
};

//�������, ����� ��� ���� �������
//===============================

//��������� ������� � ����� � ������������ column, line
void GoToXY(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetConsoleCursorPosition(hConsole, coord))
        cout << "Error";
}

//������������ �� ������ ����� ������� �� ������������ ������ �� ������
string OutString(string Str, string str)
{
    string S;    
        int n = Str.find(str);
        n += str.size();
        int count = 0;
        for (int i = n; i < Str.size(); i++)
        {           
            if (Str[i] == ';')
                break;
            count++;
        }
        S = Str.substr(n, count);   
    return S;
}

//�������������� string s � int, size - ������ s
int StringToInt(string s, int size)
{
    int Number = 0;
    for (int i = 0; i < size; i++)
    {
        int N = s[i] - '0';
        int st = pow(10, size - 1 - i);
        Number += N * st;
    }

    return Number;
}

//�������������� int n � string
string IntToStr(int n)
{
    string s = "";
    ostringstream ss;
    ss << n;
    s = ss.str();    
    
    return s;
}