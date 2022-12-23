#pragma once

#include <iostream>

class Circle {
    int radius;
public:
    explicit Circle(int r) : radius(r) {}

    Circle(const Circle &) = default;

    Circle(Circle &&) = default;

    friend void draw(const Circle &circle, const std::any &any);
};

struct CircleDrawSettings {
    int len;
};

void draw(const Circle &circle, const std::any &any) {
    auto settings = any_cast<CircleDrawSettings>(any);
    std::cout << "circle r = " << circle.radius << "; len = " << settings.len << std::endl;
}
