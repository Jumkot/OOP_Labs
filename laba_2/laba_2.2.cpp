#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

struct Matrix
{
    explicit Matrix(size_t size, int maxValue)
        : size_(size), size_elem(new int[size]), matrix(new int *[size])
    {
        int e_index = 0;
        for (int i = 0; i < size; ++i)
        {
            size_elem[e_index] = rand() % 10;
            matrix[i] = new int[size_elem[e_index++]];
            for (int j = 0; j < size_elem[i]; ++j)
            {
                matrix[i][j] = rand() % maxValue;
            }
        }
    }

    ~Matrix()
    {
        delete[] size_elem;
        for (int i = 0; i < size_; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    int get_size() const { return size_; }

    void print_matrix(Matrix *matrix)
    {
        for (int i = 0; i < matrix->size_; ++i)
        {
            cout << size_elem[i] << ": ";
            for (int j = 0; j < size_elem[i]; ++j)
            {
                cout << matrix->matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

private:
    int size_;
    int *size_elem;
    int **matrix;
};

int main()
{
    srand(time(NULL));
    int size = rand() % 9 + 1;
    int maxValue = 100;
    Matrix matrix(size, maxValue);
    matrix.print_matrix(&matrix);

    return 0;
}