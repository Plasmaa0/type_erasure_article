#include <iostream>
#include <memory>
#include <vector>

struct ShapeConcept {
    virtual ~ShapeConcept() = default;

    virtual void callDraw() const = 0;
};

template<typename T>
struct ShapeModel : public ShapeConcept {
    T shape_instance;

    explicit ShapeModel(T &&shape) : shape_instance(std::move(shape)) {}

    explicit ShapeModel(const T &shape) : shape_instance(shape) {}

    void callDraw() const override {
        draw(shape_instance);
    }
};

struct Circle {
};

void draw(const Circle &c) {
    std::cout << "I am Circle" << std::endl;
}

struct Square {
};

void draw(const Square &s) {
    std::cout << "I am Square" << std::endl;
}

int main() {
    srand(time(nullptr));
    // external polymorphism
    // allow classes unrelated by inheritance and/or
    // having no virtual methods to be treated polymorphically
    ShapeModel circle(Circle{});
    ShapeModel square(Square{});
//    ShapeModel m2(123); // ‘const Circle&’ не приводится ‘const int’
    circle.callDraw();
    square.callDraw();

    std::vector<std::unique_ptr<ShapeConcept>> v;
    for (int i = 0; i < 5; ++i) {
        if (rand() % 2 == 0)
            v.emplace_back(new ShapeModel<Circle>{Circle{}});
        else
            v.emplace_back(new ShapeModel<Square>{Square{}});
        v.back()->callDraw();
    }
    return 0;
    // 269 lines of assembly total
}