#include <iostream>
#include <cmath>

class Point{
protected:
    int x, y;
public:
    Point(int x, int y): x(x), y(y) {} // конструктор
    int getX() const {return x;}
    int getY() const {return y;}
    Point operator+(const Point& a) const { // сложили две точки, вернули результат
        return Point(x + a.x, y + a.y);
    }
    Point operator-(const Point& a) const { // вычли две точки, вернули результат
        return Point(x - a.x, y - a.y);
    }
    Point operator*(double c) const { // умножили точку справа на коэффициент, вернули результат
        return Point(x * c, y * c);
    }
    double dist() const {
        return sqrt(x * x + y * y);
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << "; " << p.y << ")";
    return os;
}

class AABB{
public:
    Point min;
    Point max;

    AABB(const Point& lb, const Point& rt) : min(lb), max(rt){
    }
    bool correct() const{
        return max.getX() >= min.getX() && max.getY() << min.getY();
    }
    double diameter() const{
        return (max - min).dist();
    }
    bool contains(const Point& p) const{
        return min.getX() <= p.getX() && p.getX() <= max.getX() && min.getY() <= p.getY() && p.getY() <= max.getY();
    }
    bool contains(const AABB& ab) const{
        return this->contains(ab.min) && this->contains(ab.max);
    }
};

#include <iostream>
using namespace std;
int main()
{
    int xa, xb, ya, yb;
    cin >> xa >> ya;
    Point a(xa, ya);
    cout << "Point #a: " << a << endl;
    cin >> xb >> yb;
    Point b(xb, yb);
    cout << "Point #b: " << b << endl;
    AABB ab(a, b);
    if (!ab.correct())
    {
        cout << "Incorrect AABB" << endl;
        return 0;
    }
    cout.precision(2);
    cout << fixed;
    cout << "AABB diameter is " << ab.diameter() << endl;
    Point mid = (a + b) * 0.5;
    if (!ab.contains(mid))
    {
        cout << "AABB does not contain its mid point " << endl;
        return 0;
    }
    cout << "Mid point is " << mid << endl;
    Point inside = a + (b - a) * 0.9;
    if (!ab.contains(inside))
    {
        cout << "AABB does not contain its inside point " << endl;
        return 0;
    }
    cout << "Inside point is " << inside << endl;
    Point outside = a + (b - a) * 1.4 + Point(1, 1);
    if (ab.contains(outside))
    {
        cout << "AABB contains its outside point." << endl;
        return 0;
    }
    cout << "Outside point is " << outside << endl;
    cin >> xa >> ya >> xb >> yb;
    if (ab.contains(AABB(Point(xa, ya), Point(xb, yb))))
    {
        cout << "First AABB contains the second one." << endl;
    }
    else
    {
        cout << "First AABB does not contain the second one." << endl;
    }
    return 0;
}