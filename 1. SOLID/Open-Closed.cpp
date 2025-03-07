/*
* File: Open-Closed.cpp
* Author: trung.la
* Date: 07-03-2025
* Description: This file is the implementation of Open-Closed Principle
*/

#include <iostream>
#include <string>
#include <vector>

// ==========================================
// WITHOUT OPEN-CLOSED PRINCIPLE
// ==========================================

/**
 * @brief ShapeCalculator class
 * This class calculates the area of different shapes.
 * The calculateArea method takes a shape type and a vector of parameters
 * and calculates the area of the shape based on the parameters.
 * But this class violates the Open-Closed Principle because it is not
 * closed for modification. If we want to add a new shape, we need to
 * modify the ShapeCalculator class.
 */
class ShapeCalculator
{
public:
    enum ShapeType {
        Circle,
        Rectangle,
        Triangle
    };

    double calculateArea(ShapeType type, const std::vector<double>& params) {
        switch(type) {
            case Circle:
                return 3.14 * params[0] * params[0];
            case Rectangle:
                return params[0] * params[1];
            case Triangle:
                return 0.5 * params[0] * params[1];
            default:
                throw std::invalid_argument("Invalid shape type");
        }
    }
};

// Client code without OCP
void demonstrateWithoutOCP() {
    std::cout << "===== WITHOUT OPEN-CLOSED PRINCIPLE =====" << std::endl;

    ShapeCalculator calculator;

    std::vector<double> circleParams = {5.0};
    double circleArea = calculator.calculateArea(ShapeCalculator::Circle, circleParams);
    std::cout << "Circle area: " << circleArea << std::endl;

    std::vector<double> rectangleParams = {4.0, 6.0};
    double rectangleArea = calculator.calculateArea(ShapeCalculator::Rectangle, rectangleParams);
    std::cout << "Rectangle area: " << rectangleArea << std::endl;

    std::vector<double> triangleParams = {3.0, 8.0};
    double triangleArea = calculator.calculateArea(ShapeCalculator::Triangle, triangleParams);
    std::cout << "Triangle area: " << triangleArea << std::endl;

    /* To add a new shape (e.g., trapezoid), we would need to:
    * 1. Add a new enum value for the shape type.
    * 2. Add a new case to the switch statement in calculateArea.
    * This violates the Open-Closed Principle because we need to modify 
    * the ShapeCalculator class to add new functionality.
    */
}

// ==========================================
// WITH OPEN-CLOSED PRINCIPLE
// ==========================================

/**
 * @brief Abstract base class for shapes
 * This class defines the interface for different shapes.
 * Each shape class (e.g., Circle, Rectangle, Triangle) will inherit from this class
 * and implement the calculateArea method to calculate the area of the shape.
 * This adheres to the Open-Closed Principle because new shapes can be added
 * without modifying the ShapeCalculator class.
 */
class Shape
{
public:
    virtual double calculateArea() const = 0;
    virtual std::string getName() const = 0;
    virtual ~Shape() = default;
};

/**
 * @brief Circle class
 * This class represents a circle shape.
 * It inherits from the Shape class and implements the calculateArea method
 * to calculate the area of the circle.
 */
class Circle : public Shape
{
private:
    double m_radius = 0.0;

public:
    explicit Circle(double r) : m_radius(r) {}

    double calculateArea() const override {
        return 3.14 * m_radius * m_radius;
    }
};

/**
 * @brief Rectangle class
 * This class represents a rectangle shape.
 * It inherits from the Shape class and implements the calculateArea method
 * to calculate the area of the rectangle.
 */
class Rectangle : public Shape
{
private:
    double m_width = 0.0;
    double m_height = 0.0;

public:
    Rectangle(double w, double h) : m_width(w), m_height(h) {}

    double calculateArea() const override {
        return m_width * m_height;
    }

    std::string getName() const override {
        return "Rectangle";
    }
};

/**
 * @brief Triangle class
 * This class represents a triangle shape.
 * It inherits from the Shape class and implements the calculateArea method
 * to calculate the area of the triangle.
 */
class Triangle : public Shape
{
private:
    double m_base = 0.0;
    double m_height = 0.0;

public:
    Triangle(double b, double h) : m_base(b), m_height(h) {}

    double calculateArea() const override {
        return 0.5 * m_base * m_height;
    }

    std::string getName() const override {
        return "Triangle";
    }
};

/**
 * @brief AreaCalculator class
 * This class calculates the area of different shapes.
 * The calculateArea method takes a Shape object and calculates the area
 * based on the type of shape. This adheres to the Open-Closed Principle
 * because new shapes can be added by creating new classes that inherit
 * from the Shape base class without modifying the AreaCalculator class.
 */
class AreaCalculator
{
public:
    static double calculateArea(const Shape &shape) {
        return shape.calculateArea();
    }

    void printArea(const Shape &shape) {
        std::cout << shape.getName() << " area: " << shape.calculateArea() << std::endl;
    }
};

/**
 * @brief Trapezoid class
 * This class is a new shape (trapezoid) that inherits from the Shape class.
 * Can be added without modifying the existing classes.
 */
class Trapezoid : public Shape
{
private:
    double m_topBase = 0.0;
    double m_bottomBase = 0.0;
    double m_height = 0.0;

public:
    Trapezoid(double topBase, double bottomBase, double h) : m_topBase(topBase), m_bottomBase(bottomBase), m_height(h) {}

    double calculateArea() const override {
        return 0.5 * (m_topBase + m_bottomBase) * m_height;
    }

    std::string getName() const override {
        return "Trapezoid";
    }
};

// Demonstrate with OCP
void demonstrateWithOCP() {
    std::cout << "\n===== WITH OPEN-CLOSED PRINCIPLE =====" << std::endl;

    AreaCalculator areaCalculator;

    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);
    Triangle triangle(3.0, 8.0);
    Trapezoid trapezoid(3.0, 6.0, 4.0);

    areaCalculator.printArea(circle);
    areaCalculator.printArea(rectangle);
    areaCalculator.printArea(triangle);
    areaCalculator.printArea(trapezoid);

    /* To add a new shape (e.g., trapezoid), we would need to:
    * 1. Create a new class for the shape (e.g., Trapezoid).
    * 2. Inherit from the Shape base class and implement the calculateArea method.
    * 3. Use the new shape class with the AreaCalculator without modifying the existing classes.
    * This adheres to the Open-Closed Principle because new functionality can be added
    * without modifying existing code.
    */
}
