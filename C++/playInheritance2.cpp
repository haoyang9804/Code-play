#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() {
        cout << "Animal sound" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() {
        cout << "Meow" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() {
        cout << "Woof" << endl;
    }
};

int main() {
    Animal animal;
    Cat cat;
    Dog dog;

    // Polymorphism using references
    Animal& refAnimal = cat;
    refAnimal.makeSound(); // Output: "Meow"

    refAnimal = dog;
    refAnimal.makeSound(); // Output: "Woof"

    // Polymorphism using pointers
    Animal* ptrAnimal = &cat;
    ptrAnimal->makeSound(); // Output: "Meow"

    ptrAnimal = &dog;
    ptrAnimal->makeSound(); // Output: "Woof"

    return 0;
}
