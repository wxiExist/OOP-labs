#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <type_traits>

template <typename T>
struct Point {
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type.");
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
};

template <typename T>
class Figure {
public:
    virtual double Area() const = 0;
    virtual Point<T> Center() const = 0;
    virtual void Print() const = 0;
    virtual ~Figure() = default;
};

template <typename T>
class Octagon : public Figure<T> {
    std::unique_ptr<Point<T>[]> vertices;
public:
    Octagon(const std::vector<Point<T>>& points) {
        if (points.size() != 8) {
            throw std::invalid_argument("Octagon requires exactly 8 points.");
        }
        vertices = std::make_unique<Point<T>[]>(8);
        for (size_t i = 0; i < 8; ++i) {
            vertices[i] = points[i];
        }
    }

    double Area() const override {
        double area = 0;
        for (size_t i = 0; i < 8; ++i) {
            size_t j = (i + 1) % 8;
            area += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
        }
        return std::abs(area) / 2.0;
    }

    Point<T> Center() const override {
        T cx = 0, cy = 0;
        for (size_t i = 0; i < 8; ++i) {
            cx += vertices[i].x;
            cy += vertices[i].y;
        }
        return Point<T>(cx / 8, cy / 8);
    }

    void Print() const override {
        std::cout << "Octagon vertices:";
        for (size_t i = 0; i < 8; ++i) {
            std::cout << " (" << vertices[i].x << ", " << vertices[i].y << ")";
        }
        std::cout << "\n";
    }
};

template <typename T>
class Triangle : public Figure<T> {
    std::unique_ptr<Point<T>[]> vertices;
public:
    Triangle(const std::vector<Point<T>>& points) {
        if (points.size() != 3) {
            throw std::invalid_argument("Triangle requires exactly 3 points.");
        }
        vertices = std::make_unique<Point<T>[]>(3);
        for (size_t i = 0; i < 3; ++i) {
            vertices[i] = points[i];
        }
    }

    double Area() const override {
        return 0.5 * std::abs(
            vertices[0].x * (vertices[1].y - vertices[2].y) +
            vertices[1].x * (vertices[2].y - vertices[0].y) +
            vertices[2].x * (vertices[0].y - vertices[1].y)
        );
    }

    Point<T> Center() const override {
        T cx = 0, cy = 0;
        for (size_t i = 0; i < 3; ++i) {
            cx += vertices[i].x;
            cy += vertices[i].y;
        }
        return Point<T>(cx / 3, cy / 3);
    }

    void Print() const override {
        std::cout << "Triangle vertices:";
        for (size_t i = 0; i < 3; ++i) {
            std::cout << " (" << vertices[i].x << ", " << vertices[i].y << ")";
        }
        std::cout << "\n";
    }
};

template <typename T>
class Square : public Figure<T> {
    std::unique_ptr<Point<T>[]> vertices;
public:
    Square(const std::vector<Point<T>>& points) {
        if (points.size() != 4) {
            throw std::invalid_argument("Square requires exactly 4 points.");
        }
        vertices = std::make_unique<Point<T>[]>(4);
        for (size_t i = 0; i < 4; ++i) {
            vertices[i] = points[i];
        }
    }

    double Area() const override {
        T side = std::hypot(vertices[0].x - vertices[1].x, vertices[0].y - vertices[1].y);
        return side * side;
    }

    Point<T> Center() const override {
        T cx = 0, cy = 0;
        for (size_t i = 0; i < 4; ++i) {
            cx += vertices[i].x;
            cy += vertices[i].y;
        }
        return Point<T>(cx / 4, cy / 4);
    }

    void Print() const override {
        std::cout << "Square vertices:";
        for (size_t i = 0; i < 4; ++i) {
            std::cout << " (" << vertices[i].x << ", " << vertices[i].y << ")";
        }
        std::cout << "\n";
    }
};

template <class T>
class Array {
    std::shared_ptr<std::vector<std::shared_ptr<T>>> elements;
public:
    Array() : elements(std::make_shared<std::vector<std::shared_ptr<T>>>()) {}

    void Add(const std::shared_ptr<T>& element) {
        elements->push_back(element);
    }

    void Remove(size_t index) {
        if (index < elements->size()) {
            elements->erase(elements->begin() + index);
        }
    }

    double TotalArea() const {
        double total = 0;
        for (const auto& elem : *elements) {
            total += elem->Area();
        }
        return total;
    }

    void Print() const {
        for (const auto& elem : *elements) {
            elem->Print();
            std::cout << "Area: " << elem->Area() << ", Center: (" << elem->Center().x << ", " << elem->Center().y << ")\n";
        }
    }
};

int main() {
    Array<Figure<double>> figures;

    figures.Add(std::make_shared<Octagon<double>>(std::vector<Point<double>>{
        {0, 0}, {1, 0}, {1.5, 0.5}, {1.5, 1.5}, {1, 2}, {0, 2}, {-0.5, 1.5}, {-0.5, 0.5}}));

    figures.Add(std::make_shared<Triangle<double>>(std::vector<Point<double>>{
        {0, 0}, {1, 0}, {0.5, 1}}));

    figures.Add(std::make_shared<Square<double>>(std::vector<Point<double>>{
        {0, 0}, {1, 0}, {1, 1}, {0, 1}}));

    figures.Print();
    std::cout << "Total area: " << figures.TotalArea() << "\n";

    return 0;
}
