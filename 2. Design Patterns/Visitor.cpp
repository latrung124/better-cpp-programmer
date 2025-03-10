/*
* File: Visitor.cpp
* Author: trung.la
* Date: 10-03-2025
* Descriptions: This class is implementation of Visitor Design Pattern.
*/

#include <iostream>
#include <vector>
#include <memory>

template<typename T>
class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visit(T const&) const = 0;
    /**
     * We also can declare visit() with explicit parameter (type of Shape)
     * instead of using template, this would remove dynamic_cast and reduce runtime overhead checking.
     */
};

class AbstractVisitor
{
public:
    virtual ~AbstractVisitor() = default;
};

class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual void accept(AbstractVisitor const &) = 0;
};

class Circle : public Shape
{
private:
    double m_radius = 0.0;

public:
    Circle(double rad) : m_radius(rad) {}

    double getRadius() const { return m_radius; }
    void accept(AbstractVisitor const &visitor) override {
        if (auto const* cv = dynamic_cast<Visitor<Circle> const*>(&visitor)) {
            cv->visit(*this);
        }
    } 
};

class Square : public Shape
{
private:
    double m_side = 0.0;

public:
    Square(double side) : m_side(side) {}

    double getSide() const { return m_side; }
    void accept(AbstractVisitor const &visitor) override {
        if (auto const* cv = dynamic_cast<Visitor<Square> const*>(&visitor)) {
            cv->visit(*this);
        }

        /**
         * A dynamic_cast always leaves a bad feeling. If we used badly, it can break an architecture.
         * That would happen if we perform a cast from within the high level of the architecture to something that
         * resides in the low level of the architecture.
         * In this case, it's actually Ok to use it, since the use happens on the low level of our architecture.
         */
    } 

};

class Draw : public AbstractVisitor
            , public Visitor<Circle>
            , public Visitor<Square>
{
public:
    void visit(Circle const &circle) const override { std::cout << "Visit Circle! \n"; }
    void visit(Square const &square) const override { std::cout << "Visit Square! \n"; }
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Square>(8));
    Draw drawVisitor;
    for(const auto &shape : shapes) {
        shape->accept(drawVisitor);
    }

    return 0;
}