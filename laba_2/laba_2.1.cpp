#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

struct Matrix
{
    explicit Matrix(size_t size, int maxValue)
        : size_(size), matrix(new int *[size])
    {
        for (int i = 0; i < size; ++i)
        {
            matrix[i] = new int[size];
            for (int j = 0; j < size; ++j)
            {
                matrix[i][j] = rand() % maxValue;
            }
        }
    }

    ~Matrix()
    {
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
            for (int j = 0; j < matrix->size_; ++j)
            {
                cout << matrix->matrix[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    int *spiral_left(Matrix *matrix)
    {
        int *arr = new int[matrix->size_ * matrix->size_];
        int top = 0, bottom = matrix->size_ - 1;
        int left = 0, right = matrix->size_ - 1;
        int count = 0;

        while (top <= bottom && left <= right && count < matrix->size_ * matrix->size_)
        {
            // Вправо
            for (int i = left; i <= right; i++)
            {
                arr[count++] = matrix->matrix[top][i];
            }
            top++;

            // Вниз
            for (int i = top; i <= bottom; i++)
            {
                arr[count++] = matrix->matrix[i][right];
            }
            right--;

            // Влево
            if (top <= bottom)
            {
                for (int i = right; i >= left; i--)
                {
                    arr[count++] = matrix->matrix[bottom][i];
                }
                bottom--;
            }

            // Вверх
            if (left <= right)
            {
                for (int i = bottom; i >= top; i--)
                {
                    arr[count++] = matrix->matrix[i][left];
                }
                left++;
            }
        }

        return arr;
    }

    int *spiral_center(Matrix *matrix)
    {
        int *arr = new int[matrix->size_ * matrix->size_];

        int row = matrix->size_ / 2;
        int col = matrix->size_ / 2;
        int step = 1;

        arr[0] = matrix->matrix[row][col];
        int count = 1;

        while (count < matrix->size_ * matrix->size_)
        {
            // Вправо
            for (int i = 0; i < step; ++i)
            {
                ++col;
                if (row >= 0 && row < matrix->size_ && col >= 0 && col < matrix->size_)
                {
                    arr[count++] = matrix->matrix[row][col];
                }
            }

            // Вниз
            for (int i = 0; i < step; ++i)
            {
                ++row;
                if (row >= 0 && row < matrix->size_ && col >= 0 && col < matrix->size_)
                {
                    arr[count++] = matrix->matrix[row][col];
                }
            }

            // Влево
            for (int i = 0; i < step + 1; ++i)
            {
                --col;
                if (row >= 0 && row < matrix->size_ && col >= 0 && col < matrix->size_)
                {
                    arr[count++] = matrix->matrix[row][col];
                }
            }

            // Вверх
            for (int i = 0; i < step + 1; ++i)
            {
                --row;
                if (row >= 0 && row < matrix->size_ && col >= 0 && col < matrix->size_)
                {
                    arr[count++] = matrix->matrix[row][col];
                }
            }

            step += 2;
        }
        return arr;
    }

    int *diagonal_right(Matrix *matrix)
    {
        int *arr = new int[matrix->size_ * matrix->size_];
        int count = 0;
        for (int step = 0; step < 2 * matrix->size_ - 1; step++)
        {
            for (int i = 0; i < matrix->size_; i++)
            {
                int j = matrix->size_ - 1 - (step - i);
                if (j >= 0 && j < matrix->size_)
                {
                    arr[count++] = matrix->matrix[i][j];
                }
            }
        }
        return arr;
    }

    int *diagonal_left(Matrix *matrix)
    {
        int *arr = new int[matrix->size_ * matrix->size_];
        int count = 0;
        for (int step = 0; step < 2 * matrix->size_ - 1; step++)
        {
            for (int i = 0; i < matrix->size_; i++)
            {
                int j = step - i;
                if (j >= 0 && j < matrix->size_)
                {
                    arr[count++] = matrix->matrix[i][j];
                }
            }
        }
        return arr;
    }

private:
    int size_;
    int **matrix;
};

void print_arr(int *arr, int size);

int main()
{
    srand(time(NULL));
    int size = rand() % 4 + 3;
    int maxValue = 100;
    Matrix matrix(size, maxValue);
    matrix.print_matrix(&matrix);

    int *arr = matrix.diagonal_right(&matrix);
    cout << "a) По правым диагоналям, начиная с правого верхнего элемента:" << endl;
    print_arr(arr, size);

    arr = matrix.diagonal_left(&matrix);
    cout << "b) По левым диагоналям, начиная с левого верхнего элемента:" << endl;
    print_arr(arr, size);

    if (matrix.get_size() % 2 == 1)
    {
        arr = matrix.spiral_center(&matrix);
        cout << "c) По спирали, начиная с центрального элемента:" << endl;
        print_arr(arr, size);
    }
    else
    {
        cout << "c) В матрице чётное количество элементов, невозможгно вывести по спирали с центрального" << endl;
    }

    arr = matrix.spiral_left(&matrix);
    cout << "d) По спирали, начиная с левого верхнего элемента:" << endl;
    print_arr(arr, size);

    delete[] arr;

    return 0;
}

void print_arr(int *arr, int size)
{
    for (int i = 0; i < size * size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}