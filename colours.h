#include <iostream>
#include <Windows.h>
using namespace std;

void Color(int color)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
};
