#include <cstdio>

class Animal { public: virtual ~Animal() = default; };
class Dog : public Animal { public: void bark() { std::printf("Bark\n"); } };
int main()
{
    Animal* dog = new Dog();
    Dog* d = dynamic_cast<Dog*>(dog);
    if (d) d->bark();
    delete dog;
    return 0;
}
