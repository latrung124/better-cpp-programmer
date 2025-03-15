/*
* File: Strategy.cpp
* Author: trung.la
* Date: 03-13-2025
* Description: This file is implementation of strategy pattern
*/

/**
 * What is Strategy Pattern?
 * 
 * Strategy Pattern is a behavioral design pattern that enables selecting
 * an algorithm at runtime.
 * 
 * When we use it?
 * 
 * When we have multiple variations of an algorithm and want to select one dynamically.
 * When we want to avoid multiple conditional statement.
 * When we want to separate and encapsulate concerns, make the code more maintainable.
 * 
 * How it works?
 * 
 * 1. Strategy Interface: Defines a common interface for algorithms
 * 2. Concrete Strategies: Implement different variations of the algorithm.
 * 3. Context Class: Uses a Strategy object and delegates works to it.
 */

#include <iostream>
#include <memory>
#include <vector>

class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default;

    virtual void draw() = 0;
};

template <typename T>
class DrawStrategy
{
public:
    virtual ~DrawStrategy() = default;

    virtual void draw(T const&) = 0;
};

class Circle;

class DrawCircleStrategy : public DrawStrategy<Circle>
{
public:
    void draw(Circle const& circle) override
    {
        std::cout << "Draw Circle with radius: " << std::endl;
    }
};

class Circle : public Shape
{
private:
    double m_radius = 0.0;
    std::unique_ptr<DrawStrategy<Circle>> m_strategy;

public:
    Circle(double rad, std::unique_ptr<DrawStrategy<Circle>> strategy) : m_radius(rad), m_strategy(std::move(strategy)) {}

    void draw() override { m_strategy->draw(*this); }
};

// when we want to add another algorithm to draw the circle
class OpenGLCircleStrategy : public DrawStrategy<Circle>
{
public:
    void draw(Circle const& circle) override
    {
        std::cout << "Draw Circle with OpenGL with radius: " << std::endl;
    }
};

int main()
{
    using Shapes = std::vector<std::unique_ptr<Shape>>;

    Shapes shapes{};

    shapes.emplace_back(std::make_unique<Circle>(10.0, std::make_unique<DrawCircleStrategy>()));
    shapes.emplace_back(std::make_unique<Circle>(20.0, std::make_unique<OpenGLCircleStrategy>()));

    for (auto const& shape : shapes)
    {
        shape->draw();
    }

    return 0;
}