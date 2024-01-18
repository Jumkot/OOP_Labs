#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int **genRandMatrix(int size, int maxValue);
void printMatrix(int **matrix);

int main()
{
    srand(time(NULL));
    int size = rand() % 10;
    int maxValue = 100;
    int **matrix = genRandMatrix(size, maxValue);
    printMatrix(matrix);

    for (int i = 0; i < size + 1; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

int *genRandArray(int size, int maxValue)
{
    int *rand_array = new int[size + 1];
    rand_array[0] = size;
    for (int i = 1; i <= size; ++i)
    {
        rand_array[i] = rand() % maxValue;
    }

    return rand_array;
}

int **genRandMatrix(int size, int maxValue)
{
    int **matrix = new int *[size + 1];
    matrix[0] = new int[1];
    matrix[0][0] = size;
    for (int i = 1; i <= size; ++i)
    {
        matrix[i] = genRandArray(rand() % 10, maxValue);
    }
    return matrix;
}

void print(int *arr)
{
    cout << arr[0] << ": ";
    for (int i = 1; i <= arr[0]; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void printMatrix(int **matrix)
{
    cout << matrix[0][0] << endl;
    for (int i = 1; i <= matrix[0][0]; ++i)
    {
        print(matrix[i]);
    }
}