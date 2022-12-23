#pragma once

#include <memory>
#include <iostream>
#include <any>

class Shape {
    struct ShapeConcept {
        virtual void drawCall(const std::any&) = 0;
    };

    template<typename T>
    struct ShapeModel : public ShapeConcept {
        T shape;

        explicit ShapeModel(T &&s) : shape(std::move(s)) {}

        explicit ShapeModel(const T &s) : shape(s) {}

        void drawCall(const std::any& a) override {
            draw(shape, a);
        }
    };

    std::unique_ptr<ShapeConcept> shapePtr;
public:
    template<typename T>
    explicit Shape(const T &shape): shapePtr(new ShapeModel<T>(shape)) {}

    Shape(Shape &&) = default;

    friend void draw(const Shape &shape, const std::any& a) {
        shape.shapePtr->drawCall(a);
    }
};