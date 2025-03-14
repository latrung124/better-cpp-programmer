/*
* File: CyclicVisitor.cpp
* Author: trung.la
* Date: 03-14-2025
* Description: This is implementation of Cyclic Visitor design pattern.
*/
#include <iostream>
#include <vector>
#include <memory>

class Circle;
class Square;

class ShapeVisitor
{
public:
    virtual ~ShapeVisitor() = default;

    virtual void visit(Circle const &circle) const = 0;
    virtual void visit(Square const &square) const = 0;
};

class Shape
{
public:
    virtual ~Shape() = default;
    virtual void accept(ShapeVisitor const &visitor) = 0;
};

class Circle : public Shape
{
private:
    double m_radius = 0.0;
public:
    explicit Circle(double radius) : m_radius(radius) {}

    void accept(ShapeVisitor const &visitor) override { visitor.visit(*this); }
    double radius() { return m_radius; }
};

class Square : public Shape
{
private:
    double m_side = 0.0;
public:
    explicit Square(double side) : m_side(side) {}

    void accept(ShapeVisitor const &visitor) override { visitor.visit(*this); }
    double side() const { return m_side; }
};

class Draw : public ShapeVisitor
{
public:
    virtual ~Draw() = default;

    virtual void visit(Circle const &circle) const override { std::cout << "Draw circle! " << std::endl; }
    virtual void visit(Square const &square) const override { std::cout << "Draw Square! " << std::endl; }
};

void drawAllShapes(std::vector<std::unique_ptr<Shape>> const &shapes)
{
    for (auto const &shape : shapes)
    {
        shape->accept( Draw{} );
    }
}

int main()
{
    using Shapes = std::vector<std::unique_ptr<Shape>>;

    Shapes shapes;
    shapes.emplace_back(std::make_unique<Circle>( 2.3 ));
    shapes.emplace_back(std::make_unique<Square>( 1.2 ));
    shapes.emplace_back(std::make_unique<Circle>( 4.1 ));

    drawAllShapes(shapes);

    return EXIT_SUCCESS;
}