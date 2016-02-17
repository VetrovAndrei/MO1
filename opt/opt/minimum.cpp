#include "minimum.h"


minimum::minimum(void)
{
}


minimum::~minimum(void)
{
}

double minimum::Func(double x) 
{
	n++;
	return pow((x - 2.0), 2.0);
}

// метод дихотомии
void minimum::Dichotomy(std::ofstream &output)
{
	double a0 = -2, b0 = 20;
	double fun1, fun2;
	int num = 1;
	n = 0;
	a = a0;
	b = b0;
	double delta = eps / 2.;
	output.precision(15);
	output << "n\t" << "a\t" << "b\t" << "b-a\t" << "(bP-aP)/(b-a)\t" << std::endl;
	while (abs(b - a) > eps) 
	{
		bPrev = b;
		aPrev = a;
		//подбираем x
		x1 = (a + b - delta) / 2.;
		x2 = (a + b + delta) / 2.;
		fun1 = Func(x1);
		fun2 = Func(x2);
		//в зависимости от значения в x, отсекаем правую или левую часть отрезка
		if (fun1 >= fun2)
		{
			a = x1;
		}
		else
		{
			b = x2;
		}
		output << num << "\t" << a << "\t" << b << "\t" << b - a << "\t" << (bPrev - aPrev) / (b - a) << std::endl;
		num++;
	}
	output << n;
}

//метод золотого сечения
void minimum::GoldenSection(std::ofstream &output)
{
	double a0 = -2, b0 = 20;
	double sech = (3.0 - sqrt(5.0)) / 2.0;
	double fun1, fun2;
	double length = 0, lengthprev = b0 - a0;
	int num = 1;
	n = 0;
	char flag = 0;
	a = a0;
	b = b0;
	bPrev = b;
	aPrev = a;
	output.precision(15);
	output << "n\t" << "a\t" << "b\t" << "b-a\t" << "(bP-aP)/(b-a)\t" << std::endl;
	//подбираем иксы по формуле золотого сечения
	x1 = a + sech * lengthprev;
	x2 = b - sech * lengthprev;
	fun1 = Func(x1);
	fun2 = Func(x2);
	//в зависимости от значения в x, отсекаем правую или левую часть отрезка
	if (fun1 > fun2)
	{
		a = x1;
		flag = 2;
	}
	else
	{
		b = x2;
		flag = 1;
	}
	length = b - a;
	output << num << "\t" << a << "\t" << b << "\t" << b - a << "\t" << lengthprev / length << std::endl;
	lengthprev = length;
	while (lengthprev > eps) 
	{
		//по свойствам золотого сечения в зависимости от того, какой отрезок мы отсекли
		//присваем одному из иксов предыдущее значение другого икса, и значение функции
		//соответственно
		if (flag == 1) 
		{
			x2 = x1;
			x1 = a + sech * lengthprev;
			fun2 = fun1;
			fun1 = Func(x1);
		}
		else 
		{
			x1 = x2;
			x2 = b - sech * lengthprev;
			fun1 = fun2;
			fun2 = Func(x2);
		}
		//в зависимости от значения в x, отсекаем правую или левую часть отрезка
		if (fun1 > fun2)
		{
			a = x1;
			flag = 2;
		}
		else
		{
			b = x2;
			flag = 1;
		}
		num++;
		length = b - a;
		output << num << "\t" << a << "\t" << b << "\t" << b - a << "\t" << lengthprev / length << std::endl;
		lengthprev = length;
	}
	output << n;
}

//формула бине
double minimum::Fib(int j)
{
	double res = (pow(((1.0+sqrt(5.0))/2.0),j)-pow(((1.0-sqrt(5.0))/2.0),j))/sqrt(5.0); 
	return res;
}

//поиск наибольшего числа из последовательности фибоначчи необходимое для заданной погрешности
int minimum::FindN(double &fib3)
{
	double a0 = -2, b0 = 20;
	double buf = abs(b0-a0)/eps;
	int num = 0;
	fib3 = 0;
	double fib1 = 1, fib2 = 1;
	while (buf > fib3)
	{
		fib3 = fib1 + fib2;
		fib1 = fib2;
		fib2 = fib3;
		num++;
	}
	return num;
}

//метод фибоначчи
void minimum::Fibonachi(std::ofstream &output)
{
	double a0 = -2, b0 = 20;
	double fun1, fun2, fibMax = 0;
	double length = 0, lengthprev = b0 - a0, lengthconst = b0 - a0;
	int num = 0, k = 2;
	n = 0;
	char flag = 0;
	//вычисляем необходимое количество элементов последовательности 
	//фибоначчи и запоминаем максимальный
	num = FindN(fibMax);
	a = a0;
	b = b0;
	bPrev = b;
	aPrev = a;
	output.precision(15);
	output << "n\t" << "a\t" << "b\t" << "b-a\t" << "(bP-aP)/(b-a)\t" << std::endl;
	//считаем х по формулам фибоначчи
	x1 = a + Fib(num)/fibMax * lengthconst;
	x2 = a + Fib(num + 1)/fibMax * lengthconst;
	fun1 = Func(x1);
	fun2 = Func(x2);
	//в зависимости от значения в x, отсекаем правую или левую часть отрезка
	if (fun1 > fun2)
	{
		a = x1;
		flag = 2;
	}
	else
	{
		b = x2;
		flag = 1;
	}
	length = b - a;
	output << "1" << "\t" << a << "\t" << b << "\t" << b - a << "\t" << lengthprev / length << std::endl;
	lengthprev = length;
	while (k <= num) 
	{
		//по свойствам последовательности фибоначчи в зависимости от того, какой отрезок мы отсекли
		//присваем одному из иксов предыдущее значение другого икса, и значение функции
		//соответственно
		if (flag == 1) 
		{
			x2 = x1;
			x1 = a + Fib(num - k + 1)/fibMax * lengthconst;
			fun2 = fun1;
			fun1 = Func(x1);
		}
		else 
		{
			x1 = x2;
			x2 = a + Fib(num - k + 2)/fibMax * lengthconst;
			fun1 = fun2;
			fun2 = Func(x2);
		}

		if (fun1 > fun2)
		{
			a = x1;
			flag = 2;
		}
		else
		{
			b = x2;
			flag = 1;
		}
		length = b - a;
		output << k << "\t" << a << "\t" << b << "\t" << b - a << "\t" << lengthprev / length << std::endl;
		lengthprev = length;
		k++;
	}
	output << n;
}

void minimum::minInter(double x0, std::ofstream &output)
{
	double x1, x2;
	double h;
	double fun1, fun2;
	int k = 0;
	output.precision(17);
	for (eps = 0.1; eps > 1e-15; eps/=10)
	{
		output << eps << std::endl;
		for (x0 = -10.0; x0 < 11; x0++)
		{
			fun1 = Func(x0);
			fun2 = Func(x0 + eps);
			if (fun1 > fun2)
			{
				h = eps;
			}
			else 
			{
				h = -eps;
				std::swap(fun1,fun2);
			}
			x1 = x0 + h;
			h *= 2;
			while (fun1 > fun2)
			{
				x2 = x1 + h;
				fun1 = fun2;
				fun2 = Func(x2);
				h *= 2;
				k++;
				x1 = x2;
			}
			x1 -= h + h/2;
			if (x1 > x2)
			{
				std::swap(x1,x2);
			}
			output << x0 << "\t" << k << "\t" << x2 - x1 << std::endl;
			k = 0;
		}
		output << std::endl;
	}
}