#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int *genRandArray(int size, int maxValue);
void print(int *arr);

int main()
{
    srand(time(NULL));
    int size = rand() % 10;
    int maxValue = 100;
    int *arr = genRandArray(size, maxValue);
    print(arr);
    delete[] arr;

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

void print(int *arr)
{
    cout << arr[0] << ": ";
    for (int i = 1; i <= arr[0]; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}