#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class Figure {
public:
    virtual ~Figure() = default;
    virtual void read(std::istream& in) = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual double area() const = 0;
    virtual std::pair<double, double> center() const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Figure& fig) {
        fig.print(out);
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Figure& fig) {
        fig.read(in);
        return in;
    }
};

class Octagon : public Figure {
private:
    double side_length;
    std::pair<double, double> center_point;

public:
    Octagon() : side_length(0), center_point({0, 0}) {}

    void read(std::istream& in) override {
        in >> side_length >> center_point.first >> center_point.second;
    }

    void print(std::ostream& out) const override {
        out << "Octagon: side length = " << side_length
            << ", center = (" << center_point.first << ", " << center_point.second << ")";
    }

    double area() const override {
        return 2 * (1 + sqrt(2)) * side_length * side_length;
    }

    std::pair<double, double> center() const override {
        return center_point;
    }
};

class Triangle : public Figure {
private:
    double base, height;
    std::pair<double, double> center_point;

public:
    Triangle() : base(0), height(0), center_point({0, 0}) {}

    void read(std::istream& in) override {
        in >> base >> height >> center_point.first >> center_point.second;
    }

    void print(std::ostream& out) const override {
        out << "Triangle: base = " << base << ", height = " << height
            << ", center = (" << center_point.first << ", " << center_point.second << ")";
    }

    double area() const override {
        return 0.5 * base * height;
    }

    std::pair<double, double> center() const override {
        return center_point;
    }
};

class Square : public Figure {
private:
    double side_length;
    std::pair<double, double> center_point;

public:
    Square() : side_length(0), center_point({0, 0}) {}

    void read(std::istream& in) override {
        in >> side_length >> center_point.first >> center_point.second;
    }

    void print(std::ostream& out) const override {
        out << "Square: side length = " << side_length
            << ", center = (" << center_point.first << ", " << center_point.second << ")";
    }

    double area() const override {
        return side_length * side_length;
    }

    std::pair<double, double> center() const override {
        return center_point;
    }
};

int main() {
    std::vector<std::unique_ptr<Figure>> figures;
    int choice;

    while (true) {
        std::cout << "1. Add Octagon\n2. Add Triangle\n3. Add Square\n4. Display Figures\n5. Compute Total Area\n6. Exit\n";
        std::cin >> choice;

        if (choice == 6) break;

        switch (choice) {
            case 1: {
                auto oct = std::make_unique<Octagon>();
                std::cin >> *oct;
                figures.push_back(std::move(oct));
                break;
            }
            case 2: {
                auto tri = std::make_unique<Triangle>();
                std::cin >> *tri;
                figures.push_back(std::move(tri));
                break;
            }
            case 3: {
                auto sq = std::make_unique<Square>();
                std::cin >> *sq;
                figures.push_back(std::move(sq));
                break;
            }
            case 4: {
                for (const auto& fig : figures) {
                    std::cout << *fig << "\n";
                }
                break;
            }
            case 5: {
                double total_area = 0;
                for (const auto& fig : figures) {
                    total_area += fig->area();
                }
                std::cout << "Total Area: " << total_area << "\n";
                break;
            }
            default:
                std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}
