/*
* File: LivkovSubtitution.cpp
* Author: trung.la
* Date: 08-03-2025
* Description: This file is the implementation of Liskov Substitution Principle
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <exception>

// ==========================================
// WITHOUT LISKOV SUBSTITUTION PRINCIPLE
// ==========================================

/**
 * @brief Rectangle class
 * This class represents a rectangle shape.
 * It has width and height properties and methods to set and get the dimensions.
 * The setWidth and setHeight methods set the width and height of the rectangle.
 * The area method calculates the area of the rectangle, and the display method
 * prints the dimensions of the rectangle.
 */
class Rectangle
{
protected:
    double m_width = 0.0;
    double m_height = 0.0;

public:
    Rectangle(double w, double h) : m_width(w), m_height(h) {}

    virtual void setWidth(double w) {
        m_width = w;
    }

    virtual void setHeight(double h) {
        m_height = h;
    }

    double getWidth() const {
        return m_width;
    }

    double getHeight() const {
        return m_height;
    }

    virtual double area() const {
        return m_width * m_height;
    }

    virtual void display() const {
        std::cout << "Rectangle width: " << m_width << ", height: " << m_height << std::endl;
    }

    virtual ~Rectangle() = default;
};

/**
 * @brief Square class
 * This class represents a square shape.
 * It inherits from the Rectangle class but violates the Liskov Substitution Principle.
 */
class Square : public Rectangle
{
public:
    explicit Square(double size) : Rectangle(size, size) {}

    void setWidth(double w) override {
        m_width = w;
        m_height = w; // Violates Liskov Substitution Principle, changes the behavior of the base class
    }

    void setHeight(double h) override {
        m_width = h; // Violates Liskov Substitution Principle, changes the behavior of the base class
        m_height = h;
    }

    void display() const override {
        std::cout << "Square size: " << m_width << std::endl;
    }
};

// Function that uses a Rectangle
void resizeRectangle(Rectangle &rect, double w, double h)
{
    rect.setWidth(w);
    rect.setHeight(h);

    std::cout << "Area: " << rect.area() << std::endl;
    rect.display();
}

// Demonstrate code without LSP
void demonstrateWithoutLSP()
{
    Rectangle rect(3, 4);
    resizeRectangle(rect, 5, 6);

    Square square(5);
    resizeRectangle(square, 5, 6);
    /**
     * The Square class violates the Liskov Substitution Principle because it changes the behavior of the base class.
     * The setWidth and setHeight methods in the Square class set both the width and height to the same value,
     * which is not the intended behavior for a Rectangle. When the resizeRectangle function is called with a Square object,
     * it produces unexpected results because the Square class does not behave like a Rectangle.
     */
}

// ==========================================
// WITH LISKOV SUBSTITUTION PRINCIPLE
// ==========================================

/**
 * @brief Shape interface
 * This interface defines the methods that a shape class should implement.
 * The area method calculates the area of the shape, and the display method
 * displays information about the shape.
 */
class Shape
{
public:
    virtual double area() const = 0;
    virtual void display() const = 0;
    virtual ~Shape() = default;
};

/**
 * @brief RectangleLSP class
 * This class represents a rectangle shape.
 * LSP compliant version of the Rectangle class.
 */
class RectangleLSP : public Shape
{
protected:
    double m_width = 0.0;
    double m_height = 0.0;

public:
    RectangleLSP(double w, double h) : m_width(w), m_height(h) {}

    void setWidth(double w) {
        m_width = w;
    }

    void setHeight(double h) {
        m_height = h;
    }

    double area() const override {
        return m_width * m_height;
    }

    void display() const override {
        std::cout << "Rectangle width: " << m_width << ", height: " << m_height << std::endl;
    }
};

/**
 * @brief SquareLSP class
 * This class represents a square shape.
 * LSP compliant version of the Square class.
 */
class SquareLSP : public Shape
{
private:
    double m_size = 0.0;

public:
    explicit SquareLSP(double size) : m_size(size) {}

    void setSize(double size) {
        m_size = size;
    }

    double area() const override {
        return m_size * m_size;
    }

    void display() const override {
        std::cout << "Square size: " << m_size << std::endl;
    }
};

// Function that uses a Shape
void displayInfoShape(Shape &shape)
{
    shape.display();
    shape.area();
}

void resizeRectangleLSP(RectangleLSP &rect, double w, double h)
{
    rect.setWidth(w);
    rect.setHeight(h);

    std::cout << "Area: " << rect.area() << std::endl;
    rect.display();
    /*
    * Now we're explicit that this function only works with RectangleLSP objects, so we can't pass a SquareLSP object to it.
    */
}

void resizeSquareLSP(SquareLSP &square, double size)
{
    square.setSize(size);
    /**
     * This function is specific to the SquareLSP class, so it only
     * works with SquareLSP objects. It does not work with RectangleLSP objects.
     */
}

// Demonstrate code with LSP
void demonstrateWithLSP()
{
    RectangleLSP rect(3, 4);
    resizeRectangleLSP(rect, 5, 6);
    displayInfoShape(rect);

    SquareLSP square(5);
    resizeSquareLSP(square, 6);
    displayInfoShape(square);
    /**
     * The SquareLSP class adheres to the Liskov Substitution Principle because it does not change the behavior of the base class.
     * The setWidth and setHeight methods in the RectangleLSP class set the width and height independently, as expected for a Rectangle.
     * When the resizeRectangleLSP function is called with a RectangleLSP object, it behaves as expected and produces the correct results.
     */
}