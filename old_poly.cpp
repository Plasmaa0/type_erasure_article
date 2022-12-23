#include <iostream>
#include <memory>
#include <vector>

struct Shape {
    virtual void draw() = 0;
};

struct Circle : public Shape {
    void draw() override {
        std::cout << "I am Circle" << std::endl;
    }
};

struct Square : public Shape {
    void draw() override {
        std::cout << "I am Square" << std::endl;
    }
};

int main() {
    std::unique_ptr<Shape> circle(new Circle);
    std::unique_ptr<Shape> square(new Square);
    circle->draw();
    square->draw();
//    Shape ns(NotSupported{}); // error: no matching function for call to ‘draw(const NotSupported&)’
//    draw(circle);
//    draw(square);

    std::vector<std::unique_ptr<Shape>> v;
    for (int i = 0; i < 5; ++i) {
        if (rand() % 3 == 0)
            v.emplace_back(new Circle);
        else
            v.emplace_back(new Square);
        v.back()->draw();
    }
    return 0;
    // 211 lines of assembly total
}