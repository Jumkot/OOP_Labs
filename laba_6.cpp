#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

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

    virtual void create_print()
    {
        cout << "Количество созданных объектов класса ";
    }

    virtual void exist_print()
    {
        cout << "Количество существующих объектов класса ";
    }

    virtual double get_perimeter() const = 0;

    int get_x() const { return x; }
    int get_y() const { return y; }
};

class Line : public Figure
{
    static int create;
    static int exist;

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
        ++create;
        ++exist;
    }

    Line(int x1, int y1, int x2, int y2) : Figure(x1, y1), x2(x2), y2(y2)
    {
        count_length();
        ++create;
        ++exist;
    }

    ~Line()
    {
        --exist;
    };

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

    void create_print()
    {
        Figure::create_print();
        cout << "линия: " << create << endl;
    }

    void exist_print()
    {
        Figure::create_print();
        cout << "линия: " << exist << endl;
    }

    double get_length() const { return length; }
    double get_perimeter() const { return 0; }

    void count_length()
    {
        length = sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
    }
};

class Square : public Line
{
    static int create;
    static int exist;

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
        ++create;
        ++exist;
    }

    Square(int x, int y, int x2, int y2, int x3, int y3) : Line(x, y, x2, y2), x3(x3), y3(y3)
    {
        count_perimeter();
        count_area();
        ++create;
        ++exist;
    }

    ~Square()
    {
        --exist;
    };

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

    void create_print()
    {
        Figure::create_print();
        cout << "квадрат: " << create << endl;
    }

    void exist_print()
    {
        Figure::create_print();
        cout << "квадрат: " << exist << endl;
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
    static int create;
    static int exist;

protected:
    double height;

public:
    Rectangle() : Square()
    {
        y3 = y2 - get_rand();
        count_height();
        count_perimeter();
        count_area();
        ++create;
        ++exist;
    }

    Rectangle(int x, int y, int x2, int y2, int x3, int y3) : Square(x, y, x2, y2, x3, y3)
    {
        y3 = y2 - get_rand();
        count_height();
        count_perimeter();
        count_area();
        ++create;
        ++exist;
    }

    ~Rectangle()
    {
        --exist;
    };

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

    void create_print()
    {
        Figure::create_print();
        cout << "прямоугольник: " << create << endl;
    }

    void exist_print()
    {
        Figure::create_print();
        cout << "прямоугольник: " << exist << endl;
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
    static int create;
    static int exist;

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
        ++create;
        ++exist;
    }

    Circle(int x1, int y1, int radius) : Figure(x1, y1), radius(radius)
    {
        count_perimeter();
        count_area();
        ++create;
        ++exist;
    }

    ~Circle()
    {
        --exist;
    };

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

    void create_print()
    {
        Figure::create_print();
        cout << "круг: " << create << endl;
    }

    void exist_print()
    {
        Figure::create_print();
        cout << "круг: " << exist << endl;
    }

    int get_radius() const { return radius; }
    virtual double get_perimeter() const { return perimeter; }
    virtual double get_area() const { return area; }

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
    static int create;
    static int exist;

protected:
    int y_radius;

public:
    Ellipse() : Circle()
    {
        y_radius = get_rand();
        count_perimeter();
        count_area();
        ++create;
        ++exist;
    }

    Ellipse(int x1, int y1, int radius, int y_radius) : Circle(x1, y1, radius), y_radius(y_radius)
    {
        count_perimeter();
        count_area();
        ++create;
        ++exist;
    }

    ~Ellipse()
    {
        --exist;
    };

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

    void create_print()
    {
        Figure::create_print();
        cout << "эллипс: " << create << endl;
    }

    void exist_print()
    {
        Figure::create_print();
        cout << "эллипс: " << exist << endl;
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

int Line::create = 0;
int Line::exist = 0;

int Square::create = 0;
int Square::exist = 0;

int Rectangle::create = 0;
int Rectangle::exist = 0;

int Circle::create = 0;
int Circle::exist = 0;

int Ellipse::create = 0;
int Ellipse::exist = 0;

int main()
{
    srand((time(NULL)));

    Line line1(10, 5, 5, 10);
    Line line2;
    Square square1(0, 4, 4, 4, 4, 0);
    Square square2;
    Rectangle rectangle1(0, 10, 4, 10, 4, 0);
    Rectangle rectangle2;
    Circle circle1(2, 4, 10);
    Circle circle2;
    Ellipse ellipse1(2, 4, 10, 4);
    Ellipse ellipse2;

    rectangle2.create_print();
    rectangle2.exist_print();

    Rectangle *rect_ptr;

    rectangle2.create_print();
    rectangle2.exist_print();

    Figure *figures[4];
    figures[0] = new Square();
    figures[1] = new Rectangle();
    figures[2] = new Circle();
    figures[3] = new Ellipse();

    rectangle2.create_print();
    rectangle2.exist_print();

    cout << "\tМассив фигур: " << endl;
    for (int i = 0; i < 4; ++i)
    {
        cout << "    Периметр фигуры " << i + 1 << ": " << figures[i]->get_perimeter() << endl;
    }

    for (int i = 0; i < 4; ++i)
    {
        delete figures[i];
    }

    rectangle2.create_print();
    rectangle2.exist_print();

    return 0;
}