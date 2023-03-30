#include <iostream>

class Shape {
public:
    // if virtual is deleted, then override keyword
    // in Circle class will throw an exception 
    // because draw function in Circle overrides no
    // function in Shape. And all the output will be
    // "Drawing a Shape".
    virtual void draw() {
        std::cout << "Drawing a shape." << std::endl;
    }
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

class Triangle : public Shape {
public:
    void draw() {
        std::cout << "Drawing a triangle." << std::endl;
    }
};

class Rectangle : public Shape {
public:
    virtual void draw() {
        std::cout << "Drawing a rectangle." << std::endl;
    }
};

int main() {
    Shape* shape = new Circle();
    shape->draw(); // prints "Drawing a circle."
    delete shape;
    Shape* shape2 = new Triangle();
    shape2->draw();
    delete shape2;
    Shape* shape3 = new Rectangle();
    shape3->draw();
    delete shape3;
    return 0;
}