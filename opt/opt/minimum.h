#include <fstream>
#include <math.h>
#include <iostream>

#pragma once
class minimum
{
private:
	int n;
	double Func(double x);
	double x1, x2, a, b, aPrev, bPrev;
public:
	double  eps;
	void GoldenSection(std::ofstream &output);
	void Dichotomy(std::ofstream &output);
	void Fibonachi(std::ofstream &output);
	int FindN(double &fib3);
	double Fib(int j);
	void minInter(double x0, std::ofstream &output);
	minimum(void);
	~minimum(void);
};

