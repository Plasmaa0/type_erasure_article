#include <iostream>
#include <memory>
#include <vector>

class Shape {
private:
    struct ShapeConcept {
        virtual void drawCall() const = 0;

        virtual std::unique_ptr<ShapeConcept> clone() const = 0;

        virtual ~ShapeConcept() = default;
    };

    template<typename T>
    struct ShapeModel : public ShapeConcept {
        T shape_instance;

        explicit ShapeModel(T &&shape) : shape_instance(std::move(shape)) {}

        explicit ShapeModel(const T &shape) : shape_instance(shape) {}

        [[nodiscard]] std::unique_ptr<ShapeConcept> clone() const override {
            return std::make_unique<ShapeModel>(*this);
        }

        void drawCall() const override {
            draw(shape_instance);
        }
    };

    std::unique_ptr<ShapeConcept> shapePtr;
public:
    template<typename T>
    explicit Shape(const T &shape): shapePtr(new ShapeModel<T>(shape)) {}

    friend void draw(const Shape &shape) {
        shape.shapePtr->drawCall();
    }

    Shape(const Shape &other) : shapePtr(other.shapePtr->clone()) {
    }
};


class Circle {
public:
    explicit Circle(double r)
            : radius(r) {}

    double getRadius() const {
        return radius;
    }

    void setRadius(double r) {
        radius = r;
    }

private:
    double radius;
};

void draw(const Circle &s) {
    std::cout << "I am Circle with radius = " <<
              s.getRadius() << std::endl;
}

struct Square {
};

void draw(const Square &s) {
    std::cout << "I am Square" << std::endl;
}

int main() {
    Shape circle(Circle{3.14});
    Shape square(Square{});
    // Shape not_supported(123); // error: no matching function for call to ‘draw(const NotSupported&)’
    draw(circle);
    draw(square);

    std::vector<Shape> v;
    for (int i = 0; i < 5; ++i) {
        if (rand() % 2 == 0)
            v.emplace_back(circle); // конструктор копирования!
        else
            v.emplace_back(square);
    }
    for (const auto &shape: v) {
        draw(shape);
    }
    return 0;
}