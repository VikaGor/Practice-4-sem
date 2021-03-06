// praktika.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;

void print(double **A, double *B, int n) 
{
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			cout << A[i][j] << "*x[" << j + 1 << "]";
			if (j != n - 1)
				cout << "+";
		}
		cout << "=" << B[i] << endl;
	}
}

void methods(double **A, double *B, int n, double e, int fl)
{
	double zn, k, kv = 0;
	double a, b, ch_a, ch_b;
	double *Xk, *Zk, *Rk, *tmp;
	Xk = new double[n];
	Rk = new double[n];
	Zk = new double[n];
	tmp = new double[n];
	for (int i = 0; i < n; i++)
		kv += B[i] * B[i];
	//Задаем начальные приближения корней. В Xk находятся значения корней k-ой итерации
	for (int i = 0; i<n; i++)
		Xk[i] = 0.15;
	//Задаем начальные значения r0 и z0
	for (int i = 0; i < n; i++)
	{
		tmp[i] = 0;
		for (int j = 0; j < n; j++)
		{
			tmp[i] += A[i][j] * Xk[j];
		}
		Rk[i] = B[i] - tmp[i];
		Zk[i] = Rk[i];
	}
	do
	{
		zn = 0;
		ch_a = 0, ch_b = 0;
		// Вычисляем числитель и знаменатель для коэффициента αk = (rk-1,rk-1)/(AZk-1,Zk-1)
		for (int i = 0; i < n; i++)
		{
			tmp[i] = 0;
			for (int j = 0; j < n; j++)
				tmp[i] += A[i][j] * Zk[j];
			ch_a += Rk[i] * Rk[i];
			zn += tmp[i] * Zk[i];
		}
		a = ch_a / zn;           
		// Вычисляем вектор решения: xk = xk-1+ αkzk-1, вектор невязки: rk = rk-1- αkAzk-1 и числитель для βk равный (rk,rk)
		for (int i = 0; i < n; i++)
		{
			Xk[i] += a * Zk[i];
			Rk[i] -= a * tmp[i];
			if (fl == 1)
				ch_b += Rk[i] * Rk[i];
			else
			{
				if (i > 0)
					k = Rk[i] - Rk[i - 1];
				else
					k = 0;
				ch_b += Rk[i] * k;
			}
		}
		// Вычисляем b(бетта)
		b = ch_b / ch_a;
		if (b < 0)
			b = 0;
		// Вычисляем вектор спуска: zk = rk+ βkzk-1 
		for (int i = 0; i < n; i++)
			Zk[i] = Rk[i] + b * Zk[i];
	}
	// Проверяем условие выхода из итерационного цикла 
	while (ch_b / kv > e*e);
	if (n>7) {
		puts("Для проверки распечатаем первые 5 значений вектора х");
		n = 5;
	}
	for (int i = 0; i<n; i++) {
		printf("x[%d]=%f\n", i + 1, Xk[i]);
	}
}


void bigmatr()
{
	int fl;
	double e = 0.0001;
	double **A = new double *[10], B[10];
	for (int i = 0; i < 10; i++)
	{
		*(A + i) = new double[10];
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == j)
				A[i][j] = 4.0;
			else
				A[i][j] = 2.0;
		}
		B[i] = 10 + 1;
	}
	/////////Метод Флетчера-Ривса//////////
	cout << "Метод Флетчера-Ривса" << endl;
	methods(A, B, 10, e, 1);
	cout << "//////////////////////////////////////////////////" << endl;
	/////////Метод Полака-Райбера//////////
	cout << "Метод Полака-Райбера" << endl;
	methods(A, B, 10, e, 0);
	cout << "//////////////////////////////////////////////////" << endl;
	for (int i = 0; i<10; i++) {
		delete[] * (A + i);
	}
	delete[]A;

}

int main()
{
	setlocale(0, "rus");
	int   n, fl, kv = 0, flag = 0;
	double **A, *B, e;
	double t = 0.01;
	printf_s("Введите размер матрицы A[n][n]:\nn= ");
	scanf_s("%d", &n);
	A = new double*[n];
	B = new double[n];
	//Ввод матрицы А +проверка на симметричность
	while (flag == 0)
	{
		cout << "Введите матрицу A:" << endl;
		for (int i = 0; i < n; i++)
		{
			A[i] = new double[n];
			for (int j = 0; j < n; j++)
				cin >> A[i][j];
		}
		cout << "Bведенная матрица A:" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << A[i][j] << " ";
			}
			cout << endl;
		}
		//////////////////////////////////////
		//Проверка на симметричность матрицы//
		//////////////////////////////////////
		flag = 1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i != n && A[i][j] != A[j][i])
					flag = 0;
			}
		}
		if (flag == 1)
		{
			printf("Матрица симметричная!!!\n");
		}
		else
		{
			printf("!!!Матрица НЕ СИММЕТРИЧНАЯ-попробуйте снова\n\n");
		}
		puts("...нажмите Enter");
		_getch();
		system("cls");
	}
	//////////////////////////////////////
	cout << "Введите вектор b: " << endl;
	for (int i = 0; i < n; i++)
		cin >> B[i];
	cout << "Bведенный вектор b:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << B[i] << " ";
	}
	_getch();
	system("cls");
	cout << "CЛАУ:" << endl;
	print(A, B, n);
	cout <<"Введите точность e="; 
	cin >> e;
	system("cls");
	cout << "CЛАУ:" << endl;
	print(A, B, n);
	/////////Метод Флетчера-Ривса//////////
	cout << "Метод Флетчера-Ривса" << endl;
	methods(A, B, n, e, 1);
	cout << "//////////////////////////////////////////////////" << endl;
	/////////Метод Полака-Райбера//////////
	cout << "Метод Полака-Райбера" << endl;
	methods(A, B, n, e, 0);
	cout << "//////////////////////////////////////////////////" << endl;
	_getch();
	system("cls");
	printf("Добавим возмущение %f\n", t);
	for (int i = 0; i<n; i++) {
		B[i] = B[i] + t;
	}
	puts("Откуда получаем");
	print(A, B, n);
	/////////Метод Флетчера-Ривса//////////
	cout << "Метод Флетчера-Ривса" << endl;
	methods(A, B, n, e, 1);
	cout << "//////////////////////////////////////////////////" << endl;
	/////////Метод Полака-Райбера//////////
	cout << "Метод Полака-Райбера" << endl;
	methods(A, B, n, e, 0);
	cout << "//////////////////////////////////////////////////" << endl;
	_getch();
	system("cls");
	cout << "Для матрицы (10X10)" << endl;
	bigmatr();
	cout << "//////////////////////////////////////////////////" << endl;
	for (int i = 0; i<n; i++) 
	{
		delete[] * (A + i);
	}
	delete[]A;
	delete[]B;
	_getch();
	return 0;
}

