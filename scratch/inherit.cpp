#include <cstdio>

class Animal {
public:
    virtual ~Animal() = default;
    void eat() { std::printf("eating\n"); }
};
class Dog : Animal {            // no `public` → private inheritance
public:
    void dinner() { eat(); }    // inside Dog: fine, Dog knows it's an Animal
};

int main() {
    Dog dog;
    dog.dinner();               // OK
    dog.eat();                  // outside: Animal's members are hidden
    Animal* a = &dog;           // outside: "Dog is an Animal" is hidden
    (void)a;
}
