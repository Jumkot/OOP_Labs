#include "laba_4.h"
#include <time.h>

int main()
{
    cout << "Работаем с double!\n";
    Matrix<double> M(3, 4);
    cout << "Object M:\n---------------------\n";
    M.Print();

    // Заполнить матрицу значениями по формуле
    int i, j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            M.SetM(i, j, (i + j) * 0.5);
        }
    }
    cout << "Object M:\n---------------------\n";
    M.Print();

    Matrix<double> M1 = M; // вызов конструктора копирования
    cout << "Object M1:\n---------------------\n";
    M1.Print();

    Matrix<double> M2;
    M2 = M; // вызов оператора копирования - проверка
    cout << "Object M2:\n---------------------\n";
    M2.Print();

    Matrix<double> M3;
    M3 = M2 = M1 = M; // вызов оператора копирования в виде "цепочки"
    cout << "Object M3:\n---------------------" << endl;
    M3.Print();
}