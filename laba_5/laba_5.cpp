#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// I. Построить иерархию классов графических фигур : При

//                                                      Фигура
//                                             Линия               Круг
//                                 Квадрат                                 Эллипс
//                     Прямоугольник

// При этом в классах необходимо реализовать следующую функциональность:

// 1. Инициализация фигур(задание координат при создании объекта) с помощью :
//     a.Конструктора по умолчанию для инициализации полей случайными значениями принимающего значения полей указанной размерности.
//     b. Конструктора, принимающего значения полей указанной размерности.
//     Для инициализации наследуемых координат использовать соответствующие конструкторы родительских классов.
// 2. Ввод значений полей класса
// 3. Вывод значений полей класса
// 4. В классе Линия : вычисление длины линии и вывод на экран(это разные методы, длина линии хранится в поле класса)
// 5. В классах Квадрат и Прямоугольник :
//     - 2 вида методов ввода значений координат случайно и с клавиатуры;
//     - методы вычисления периметра, площади.
// 6. В деструкторе - корректное очищение динамической памяти

class Figure
{
protected:
    int x;
    int y;

public:
    Figure()
    {
        x = get_rand();
        y = get_rand();
    }

    Figure(int x, int y) : x(x), y(y) {}

    virtual ~Figure() {}

    int get_rand() const
    {
        return rand() % 100;
    }

    virtual void input()
    {
        cout << "Введите координаты (x, y): ";
        cin >> x >> y;
    }

    virtual void print()
    {
        cout << "Координаты (x, y): (" << x << ", " << y << ")\n";
    }

    int get_x() const { return x; }
    int get_y() const { return y; }
};

class Line : public Figure
{
protected:
    int x2;
    int y2;
    double length;

public:
    Line() : Figure()
    {
        x2 = get_rand();
        y2 = get_rand();
        count_length();
    }

    Line(int x1, int y1, int x2, int y2) : Figure(x1, y1), x2(x2), y2(y2)
    {
        count_length();
    }

    ~Line(){};

    void input()
    {
        Figure::input();
        cout << "Введите координаты точки (x2, y2): ";
        cin >> x2 >> y2;
        count_length();
    }

    void print()
    {
        cout << "\n\tЛиния:\n";
        Figure::print();
        cout << "Координаты точки (x2, y2): (" << x2 << ", " << y2 << ")\n";
        cout << "Длина линии: " << length << endl;
    }

    double get_length() const { return length; }

    void count_length()
    {
        length = sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
    }
};

class Square : public Line
{
protected:
    int x3;
    int y3;
    double perimeter;
    double area;

public:
    Square() : Line()
    {
        y2 = y;
        count_length();
        x3 = x2;
        y3 = y2 - length;
        count_perimeter();
        count_area();
    }

    Square(int x, int y, int x2, int y2, int x3, int y3) : Line(x, y, x2, y2), x3(x3), y3(y3)
    {
        count_perimeter();
        count_area();
    }

    ~Square(){};

    void input()
    {
        Line::input();
        cout << "Введите координаты точки (x3, y3): ";
        cin >> x3 >> y3;
        count_perimeter();
        count_area();
    }

    void print()
    {
        cout << "\n\tКвадрат:\n";
        Line::print();
        cout << "\nКоординаты точки (x3, y3): (" << x3 << ", " << y3 << ")\n";
        cout << "Координаты точки (x4, y4): (" << x << ", " << y3 << ")\n";
        cout << "Длина стороны: " << length << "\n";
        cout << "Периметр: " << perimeter << "\n";
        cout << "Площадь: " << area << endl;
    }

    double get_perimeter() const { return perimeter; }
    double get_area() const { return area; }

    virtual void count_perimeter()
    {
        perimeter = 4 * length;
    }

    virtual void count_area()
    {
        area = length * length;
    }
};

class Rectangle : public Square
{
protected:
    double height;

public:
    Rectangle() : Square()
    {
        y3 = y2 - get_rand();
        count_height();
        count_perimeter();
        count_area();
    }

    Rectangle(int x, int y, int x2, int y2, int x3, int y3) : Square(x, y, x2, y2, x3, y3)
    {
        y3 = y2 - get_rand();
        count_height();
        count_perimeter();
        count_area();
    }

    ~Rectangle(){};

    void input()
    {
        Square::input();
        count_height();
    }

    void print()
    {
        cout << "\n\tПрямоугольник:\n";
        Line::print();
        cout << "\nКоординаты точки (x3, y3): (" << x3 << ", " << y3 << ")\n";
        cout << "Координаты точки (x4, y4): (" << x << ", " << y3 << ")\n";
        cout << "Ширина: " << length << "\nВысота: " << height << "\n";
        cout << "Периметр: " << perimeter << "\n";
        cout << "Площадь: " << area << endl;
    }

    double get_height() const { return height; }

    void count_height()
    {
        height = fabs(y2 - y3);
    }

    void count_perimeter()
    {
        perimeter = 2 * length + 2 * height;
    }

    void count_area()
    {
        area = length * height;
    }
};

class Circle : public Figure
{
protected:
    int radius;
    double perimeter;
    double area;

public:
    Circle() : Figure()
    {
        radius = get_rand();
        count_perimeter();
        count_area();
    }

    Circle(int x1, int y1, int radius) : Figure(x1, y1), radius(radius)
    {
        count_perimeter();
        count_area();
    }

    ~Circle(){};

    void input()
    {
        Figure::input();
        cout << "Введите радиус: ";
        cin >> radius;
        count_perimeter();
        count_area();
    }

    void print()
    {
        cout << "\n\tОкружность:\n";
        Figure::print();
        cout << "Радиус: " << radius << "\n";
        cout << "Периметр: " << perimeter << "\n";
        cout << "Площадь: " << area << endl;
    }

    int get_radius() const { return radius; }

    void count_perimeter()
    {
        perimeter = 2 * M_PI * radius;
    }

    void count_area()
    {
        area = M_PI * radius * radius;
    }
};

class Ellipse : public Circle
{
protected:
    int y_radius;

public:
    Ellipse() : Circle()
    {
        y_radius = get_rand();
        count_perimeter();
        count_area();
    }

    Ellipse(int x1, int y1, int radius, int y_radius) : Circle(x1, y1, radius), y_radius(y_radius)
    {
        count_perimeter();
        count_area();
    }

    ~Ellipse(){};

    void input()
    {
        Figure::input();
        cout << "Введите радиус: ";
        cin >> radius;
        count_perimeter();
        count_area();
    }

    void print()
    {
        cout << "\n\tЭллипс:\n";
        Figure::print();
        cout << "Большая полуось: " << radius << "\nМалая полуось: " << y_radius << "\n";
        cout << "Периметр: " << perimeter << "\n";
        cout << "Площадь: " << area << endl;
    }

    int get_y_radius() const { return y_radius; }

    void count_perimeter()
    {
        perimeter = 2 * M_PI * sqrt((radius * radius + y_radius * y_radius) / 2);
    }

    void count_area()
    {
        area = M_PI * radius * y_radius;
    }
};

// II. В качестве демонстрационного примера написать программу
// 1. Создать объекты всех классов кроме класса Фигура с инициализацией разными конструкторами.
// 2. Вычислить длину линий, вывести на экран.
// 3. Вычислить периметры и площади квадратов и прямоугольников - вывести на экран.
// 4. Создать динамический массив из 3 элементов объектов класса Прямоугольник с инициализацией
// с помощью конструктора с параметрами.
// 5. Вычислить периметры и площади всех 3х объектов, вывести на экран
// 6. Удалить динамический массив

int main()
{
    srand((time(NULL)));

    Line line1(10, 5, 5, 10);
    line1.print();
    Line line2;
    line2.print();

    Square square1(0, 4, 4, 4, 4, 0);
    square1.print();
    Square square2;
    square2.print();

    Rectangle rectangle1(0, 10, 4, 10, 4, 0);
    rectangle1.print();
    Rectangle rectangle2;
    rectangle2.print();

    Circle circle1(2, 4, 10);
    circle1.print();
    Circle circle2;
    circle2.print();

    Ellipse ellipse1(2, 4, 10, 4);
    ellipse1.print();
    Ellipse ellipse2;
    ellipse2.print();

    Rectangle *rect_arr = new Rectangle[3]{
        Rectangle(0, 10, 4, 10, 4, 0),
        Rectangle(0, 25, 25, 25, 25, -10),
        Rectangle(-2, 2, 2, 2, 2, -8)};

    cout << "\n\tМассив прямоугольников: " << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << "Периметр прямоугольника " << i + 1 << ": " << rect_arr[i].get_perimeter() << endl;
        cout << "Площадь прямоугольника " << i + 1 << ": " << rect_arr[i].get_area() << endl;
    }

    delete[] rect_arr;

    return 0;
}