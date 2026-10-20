struct Dog {}; struct Car {};
int main() {
    Dog dog; const Dog* cd = &dog;
    Car* c = static_cast<Car*>(&dog);   // unrelated types
    Dog* p = static_cast<Dog*>(cd);     // dropping const
    (void)c; (void)p;
}
