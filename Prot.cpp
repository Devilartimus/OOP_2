#pragma once
#include <iostream>
#include <time.h>
#include "Header.h"

using namespace std;

namespace DevMatr
{
int Matrix::counter=0;
//КОНСТРУКТОРЫ
Matrix::~Matrix()   //деструктор
{
    cout << endl << "Destructor matrix " << this -> id <<endl;
    delete[] this -> data;
}

Matrix::Matrix()    //дефолт конструктор
{
    this -> id = counter;
    counter ++;
    cout << endl << "Default constructor. Matrix " << id << endl << endl;
    this -> data = nullptr;
    this -> N = 0;
    this -> M = 0;
}

Matrix::Matrix(int N)   //конструктор квадратной
{
    this -> id = counter;
    counter++;
    if (N <= 0)
    {
        cout << "Square constructor error!";
        throw "Matrix (int N) : Matrix (" + to_string(id) + ") : Negative N passed";
    }
    cout << endl << "Square matrix constructor. Matrix " << id << endl << endl;
    this -> N = N;
    this -> M = N;
    this -> data = new double [N * M];
}

Matrix::Matrix(int N, int M)    //контруктор прямоугольной
{
    this -> id = counter;
    counter++;
    if (N <= 0 || M <= 0)
    {
        cout << "Rectangle constructor error!";
        throw "Matrix (int N) : Matrix (" + to_string(id) + ") : Negative N or M passed";
    }
    cout << endl << "Rectangle matrix constructor. Matrix " << id << endl << endl;
    this -> N = N;
    this -> M = M;
    this -> data = new double [N * M];
}

Matrix::Matrix(int N, int M, double* (*Function)(int, int)) //конструктор прямоугольной с заполнением
{
    this -> id = counter;
    counter++;
    if (N <= 0 || M <= 0)
    {
        cout << "Matrix constructor with filling in error!";
        throw "Matrix(int N, int M, double* (*Function)(int, int)) : Matrix (" + to_string(id) + ") : Negative N or M passed";
    }
    cout << endl << "Matrix constructor with filling in. Matrix " << id << endl << endl;
    this -> N = N;
    this -> M = M;
    this -> data = Function(N, M);
}

Matrix::Matrix(const Matrix& Matr) : Matrix(Matr.N, Matr.M) //конструктор копирования
{
    for (int i = 0; i < (this -> N * this -> M); i++)
        this -> data[i] = Matr.data[i];
}

Matrix::Matrix(Matrix&& Matr) noexcept    //конструктор перемещения
{
    this -> id = counter;
    counter++;
    cout << "Move Constructor" << endl;
    this -> N = Matr.N;
    this -> M = Matr.M;
    this -> data = Matr.data;
    Matr.N = Matr.M = 0;
    Matr.data = nullptr;
}

//ГЕТТЕРЫ
int Matrix::GetId() const { return this -> id; }    //геттер id
int Matrix::GetN() const  { return this -> N; }     //геттер кол-ва строк
int Matrix::GetM() const  { return this -> M; }     //геттер кол-ва столбцов
int Matrix::Get(const int& x , const int& y) const  //геттер элемента
{
    if ( x < 0 || x >= N || y < M || y >= M)
    {
        cout << "Get element error!";
        throw "Get(const int& x, const int& y) : Matrix(" + to_string(id) + ") : Negative x or y, or x>=N or y>=M passed";
    }
    return this -> data [x * this -> N + y];
}


void Matrix::Input()    //заполнение матрицы
{
    cout <<  "Enter the matrix matrix " << id << endl << endl;
    for (int i=0; i < this -> N; i++)
    {
        cout << "Fill in the row  " << i+1 << " of the matrix " << id << endl;
        for (int j = 0; j < this -> M; j++)
        {
            cout << j+1 << " >> ";
            cin >> this -> data[i * this -> M +j];
        }
    }
}

bool Matrix::CheckMult(const Matrix &matr) const { return (this -> N == matr.GetN()); }  //проверка на возможность умножения
bool Matrix::CheckAdd(const Matrix &matr) const { return ((this -> N == matr.GetN()) && (this -> M == matr.GetM())); }  //проверка на возможность сложения

int Matrix::Max() const //нахождение максимального элемента
{
    double max = this -> data[0];
    for (int i = 1; i < this -> N * this -> M; i++)
        if (max < this -> data[i])
            max = this -> data[i];
    return max;
}

int Matrix::Min() const //нахождение минимального элемента
{
    double min = this -> data[0];
    for (int i = 1; i < this -> N * this -> M; i++)
        if (min > data[i])
            min = data[i];
    return min;
}

Matrix::Line::Line(double* arr) : arr(arr) { }   //конструктор

double& Matrix::Line::operator[](const int& index) { return this -> arr[index]; }   //для не константных обращений
double Matrix::Line::operator[](const int & index) const { return this -> arr[index]; }   //для константных обращений

Matrix::Line Matrix::operator[](const int& index) { return Line(this -> data + this -> M * index); }
const Matrix::Line Matrix::operator[](const int& index) const { return Line(this -> data + this -> N * index); }

Matrix& Matrix::operator=(const Matrix& matr) //оператор присваивания с копированием, без получения новых матриц
{
    if ((this -> N != matr.N) || (this -> M != matr.M))
    {
        delete[] this -> data;  //очищаем память
        this -> N = matr.N;     //заносим новые значения
        this -> M = matr.M;
        this -> data = new double[this -> N * this -> M];   //выделяем новую память
    }
    for (int i = 0; i < this -> N * this -> M; i++)
        this -> data[i] = matr.data[i];
    return *this;
}

Matrix& Matrix::operator=(Matrix&& matr) noexcept    //оператор присваивания с перемещением
{
    if (&matr == this)
        return *this;
    this -> N = matr.N;
    this -> M = matr.M;
    delete [] this -> data;
    this -> data = matr.data;
    matr.data = nullptr;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& matr)  //оператор сложения матриц
{
    if (this -> CheckAdd(matr) == false)
    {
        cout << "operator+= error!";
        throw "operator+=(const Matrix& Matx) : Matrix(" + to_string(id) + ") : Matrices have different dimensions";
    }
    for (int i = 0; i < this -> N * this -> M; i++)
        this -> data[i] += matr.data[i];
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& matr)  //оператор вычитания матриц
{
    if (this -> CheckAdd(matr) == false)
    {
        cout << "operator-= error!";
        throw "operator-=(const Matrix& Matx) : Matrix(" + to_string(id) + ") : Matrices have different dimensions";
    }
    for (int i = 0; i < this -> N * this -> M; i++)
        this -> data[i] -= matr.data[i];
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& matr)  //возможность умножения пустых матриц
{
    if (this -> CheckMult(matr) == false)
    {
        cout << "operator*= error!";
        throw "operator*=(const Matrix& Matx) : Matrix(" + to_string(id) + ") : The multiplication condition is not met";
    }
    double *arr = new double[this -> N * matr.M]; //создаем указатель типа double и ставим его на новую ленту
                                                  //в памяти размерностью кол-во строк матрицы A * на кол-во столбцов матрицы B
    double S; //счетчик суммы
    for (int i = 0; i < this -> N; i++) //считаем произведение матрицы строка*столбец
        for (int j = 0; j < this -> M; j++)
        {
            S = 0;
            for (int k = 0; k < this -> M; k++)
                S += this -> data[i * this -> M + k] * matr.data[k * matr.M + j];
            arr [i * matr.M + j] = S;   //записываем получившиеся в результаты умножения элементы
        }
    delete [] this -> data; //очищаем старую ленту
    this -> M = matr.M; //устанавливаем количество стобцов как в матрице B
    this -> data = arr; //ставим указатель на новую ленту
    return *this;
}

Matrix& Matrix::operator*=(const double& x) //оператор умножения матрицы на скаляр
{
    for (int i = 0; i < this -> N * this -> M; i++)
        this -> data[i] *= x;
    return *this;
}

ostream& operator<<(ostream& str, const Matrix& matr)
{
    int width = str.width();
    for (int i = 0; i < matr.N; i++)
    {
        for (int j = 0; j < matr.M; j++)
        {
            if ( width == 0)
                str.width(7);
            else
                str.width(width);
            str << matr.data[i * matr.M + j];
        }
        str << endl;
    }
    return str;
}

Matrix operator+(const Matrix& matr1, const Matrix& matr2) { return move(Matrix(matr1) += matr2); }    //оператор сложения матриц
Matrix operator-(const Matrix& matr1, const Matrix& matr2) { return move(Matrix(matr1) += matr2); }    //оператор вычитания матриц
Matrix operator*(const Matrix& matr1, const Matrix& matr2) { return move(Matrix(matr1) *= matr2); }    //оператор умножения матриц
Matrix operator*(const double& x, const Matrix& matr) { return move(Matrix(matr) *= x); }  //опертор умножения матрицы на скаляр
Matrix operator*(const Matrix& matr, const double& x) { return move(Matrix(matr) *= x); }  //опертор умножения матрицы на скаляр


double* FunctInput(int N, int M)    //функция автоматического заполнения матрицы
{
    double* arr = new double[N * M];
    for (int i = 0; i < N * M; i++) {
        arr[i] = i * 0.25;
    }
    return arr;
}

}
