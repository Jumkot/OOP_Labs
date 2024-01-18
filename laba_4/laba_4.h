#include <iostream>

using namespace std;

// Создать шаблонный класс Матрица. Размер матрицы m*n. Тип элементов задается через параметр шаблона.
// Память для матрицы выделяется динамически.
// Элементы класса:
// 1. Переменная M типа «указатель на указатель». Эта переменная определяет матрицу. Память для матрицы
// будет выделяться динамически;
// 2. Переменные m, n – это размерность матрицы M;
// 3. Конструктор по умолчанию (без параметров);
// 4. Конструктор с двумя параметрами – создает матрицу размером m*n. В конструкторе выделяется память
// для столбцов и строк матрицы. Значение каждого элемента матрицы устанавливается в 0;
// 5. Конструктор копирования M (M &). Этот конструктор необходим для создания копии объекта-матрицы
// из другого объекта-матрицы;
// 6. Методы чтения/записи элементов матрицы GetM(), SetM();
// 7. Метод Print() – вывод матрицы;
// 8. Оператор копирования operator=( M &). Этот оператор перегружает оператор присваивания = и предназначен
// для корректного копирования объектов, например, obj2=obj1;
// 9. Деструктор.

template <typename T>
class Matrix
{
private:
    // 2. Размерность матрицы m*n
    int m;
    int n;
    // 1. Матрица
    T **M;

public:
    // 3. Конструктор по умолчанию для инициализации матрицы размерности 0
    Matrix() : m(0), n(0), M(nullptr) {}

    // 4. Конструктор, принимающий размерность матрицы, для инициализации матрицы указанной размерности
    Matrix(int m, int n) : m(m), n(n), M(new T *[m])
    {
        for (int i = 0; i < m; ++i)
        {
            M[i] = new T[n];
            for (int j = 0; j < n; ++j)
            {
                M[i][j] = T();
            }
        }
    }

    // 9. Деструктор
    ~Matrix()
    {
        for (int i = 0; i < m; ++i)
        {
            delete[] M[i];
        }
        delete[] M;
    }

    // 5. Конструктор копирования M (M &)
    Matrix(const Matrix &other) : m(other.m), n(other.n), M(new T *[other.m])
    {
        for (int i = 0; i < m; ++i)
        {
            M[i] = new T[n];
            for (int j = 0; j < n; ++j)
            {
                M[i][j] = other.M[i][j];
            }
        }
        cout << "Конструктор копирования!" << endl;
    }

    // 8. Оператор присваивания operator=( M &)
    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < m; ++i)
            {
                delete[] M[i];
            }
            delete[] M;

            m = other.m;
            n = other.n;
            M = new T *[m];
            for (int i = 0; i < m; ++i)
            {
                M[i] = new T[n];
                for (int j = 0; j < n; ++j)
                {
                    M[i][j] = other.M[i][j];
                }
            }
        }
        cout << "Оператор присваивания!" << endl;
        return *this;
    }

    // Геттеры
    int get_m() const { return m; }
    int get_n() const { return n; }

    // 6. Методы чтения/записи элементов матрицы
    T GetM(int row, int col) const
    {
        return this->M[row][col];
    }
    void SetM(int row, int col, T num)
    {
        this->M[row][col] = num;
    }

    // 7. Метод Print() – вывод матрицы
    void Print()
    {
        for (int i = 0; i < this->m; ++i)
        {
            for (int j = 0; j < this->n; ++j)
            {
                cout << this->M[i][j] << "\t";
            }
            cout << endl;
        }
    }
};