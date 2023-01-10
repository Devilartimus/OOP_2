#pragma once
#ifndef HEADER_H
#define HEADER_H
#include <iostream>

using namespace std;

namespace DevMatr
{
class Matrix
{
private:

    double* data;       // для первого значения матрицы
    int N,M;            // строки и столбцы
    static int counter; // индивидуальный номер матриц, который не меняется
    int id;             // id матриц

public:
    //конструкторы
    ~Matrix();              //деструктор
    Matrix();               //дефолт конструктор
    Matrix(int);            //конструктор квадратной матрицы
    Matrix(int, int);       //конструктор прямоугольной матрицы
    Matrix(int, int, double* (*Function) (int,int));    //конструктор прямоугольной матрицы с заполнением
    Matrix(const Matrix&);   //конструктор копирования
    Matrix(Matrix&&) noexcept;  //конструктор перемещения

    //геттеры
    int GetId() const;  //геттер id
    int GetN() const;   //геттер количества строк
    int GetM() const;   //геттер количества столбцов
    int Get(const int&, const int&) const; //геттер определнного элемента

    //методы работы с матрицами
    void Input();       //заполнение элементов вручную
    bool CheckMult(const Matrix&) const;
    bool CheckAdd(const Matrix&) const;
    int Max() const;
    int Min() const;

    class Line  //вложенный класс для двумерной индексации
    {
    private:
        double* arr;
    public:
        Line(double* arr);  //конструктор
        double& operator[](const int&);  //для неконстантных обращений, передаем ссылкой т.к имел смысл менять значение объекта
        double operator[](const int&) const; //для константых обращений, передаем копией т.к. изменения не допускаются
    };

    Line operator[](const int&);
    const Line operator[](const int&) const; // первая const то что вернет const строку(неизменяемую), второй const гарантируют неизменяемость полей(элементов)
    Matrix& operator=(const Matrix&); //оператор копирования, без создания новой матрицы
    Matrix& operator=(Matrix&&) noexcept;   //оператор присваивания с перемещением
    Matrix& operator+=(const Matrix&);  // оператор приблавения матрицы А к матрице B
    Matrix& operator-=(const Matrix&);  // оператор вычитания матрицы А из матрицы B
    Matrix& operator*=(const Matrix&);  // оператор умножения c присваиванием матрицы А на матрицу B
    Matrix& operator*=(const double&);  // оператор умножения матрицы на скаляр
    friend ostream& operator<<(ostream& , const Matrix&);   //оператор вывода
};
//ПЕРЕГРУЗКИ ОПЕРАТОРОВ С ПОЛУЧЕНИЕМ НОВЫХ МАТРИЦ
Matrix operator+(const Matrix&, const Matrix&); //оператор сложения матриц
Matrix operator-(const Matrix&, const Matrix&); //оператор вычитания матриц
Matrix operator*(const Matrix&, const Matrix&); //оператор умножения матриц
Matrix operator*(const double&, const Matrix&); //оператор умножения матрицы на скаляр
Matrix operator*(const Matrix&, const double&); //оператор умножения матрицы на скаляр
}

#endif // HEADER_H
