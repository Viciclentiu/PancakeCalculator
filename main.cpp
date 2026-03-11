#include <iostream>
#include <cstring>
using namespace std;
class Ingredient {
private:
    const int id;
    static int no_ingredients;
    char *name;
    double quantity;
public:
    Ingredient();
    Ingredient(const char* n, double q);
    ~Ingredient();
    Ingredient(const Ingredient &obj);
    Ingredient& operator=(const Ingredient &obj);
};
Ingredient::Ingredient(): id(++no_ingredients) {
    name = new char[1];
    name[0] = '\0';
    quantity = 0.0;
}
Ingredient::Ingredient(const char* n, double q): id(++no_ingredients), quantity(q) {
    this->name = new char[strlen(n)+1];
    strcpy(this->name, n);
};
Ingredient::~Ingredient() {
    delete[] name;
}
Ingredient::Ingredient(const Ingredient &obj) : id(++no_ingredients) {
    this->name = strcpy(new char[strlen(obj.name)+1],obj.name);
    this->quantity = obj.quantity;
};
Ingredient& Ingredient::operator=(const Ingredient &obj) {
    if (this == &obj) {
        return *this;
    }
    delete[] this->name;
    this->name = strcpy(new char[strlen(obj.name)+1],obj.name);
    this->quantity = obj.quantity;
    return *this;
}

int main()
{

    return 0;
}