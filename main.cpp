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



class Recipe{
private:
    Ingredient* ingredients;
    char* instructions;
    int count;
    bool can_make;
public:
    Recipe();
    Recipe(const char*,const Ingredient*,int,bool);
    ~Recipe();
    Recipe(const Recipe &obj);
    Recipe& operator=(const Recipe &obj);
};
Recipe::Recipe() {
    ingredients = nullptr;
    instructions = new char[16];
    strcpy(instructions, "No recipes");
    count= 0;
    can_make=false;
}
Recipe::Recipe(const char *ins, const Ingredient *ingred,int count,bool canmake) {
        this->count= count;
        this->ingredients = new Ingredient[count];
        this->ingredients[count] = *ingred;
        this->instructions = new char[256];
        strcpy(this->instructions,ins);
        this->can_make = canmake;
}
Recipe::~Recipe() {
    delete[] ingredients;
    delete[] instructions;
}
Recipe::Recipe(const Recipe &obj) {
    this->count= obj.count;
    this->ingredients = new Ingredient[obj.count];
    this->ingredients[obj.count] = *obj.ingredients;
    this->instructions = new char[256];
    strcpy(this->instructions,obj.instructions);
    this->can_make = obj.can_make;
}
Recipe& Recipe::operator=(const Recipe &obj) {
    if (this == &obj) {
        return *this;
    }
    delete[] ingredients;
    this->ingredients = new Ingredient[obj.count];
    this->ingredients[obj.count] = *obj.ingredients;
    this->instructions = new char[256];
    strcpy(this->instructions,obj.instructions);
    this->can_make = obj.can_make;
    return *this;
}


class Fridge {
private:
    float temp;
    bool isOpen;
    int capacity;
    char *observations;
public:
    Fridge();
    Fridge(const char*,float,int,bool);
    ~Fridge();
    Fridge(const Fridge &obj);
    Fridge& operator=(const Fridge &obj);
};
Fridge::Fridge() {
    temp = 0.0;
    isOpen = false;
    capacity = 0;
    observations = new char[16];
    strcpy(observations,"No observations");
}
Fridge::Fridge(const char* observations, float temp, int capacity,bool isOpen) {
    this->capacity = capacity;
    this->observations = new char[strlen(observations)];
    strcpy(this->observations,observations);
    this->isOpen = isOpen;
    this->temp = temp;
}
Fridge::~Fridge() {
    delete[] observations;
}

Fridge::Fridge(const Fridge &obj) {
    this->capacity = obj.capacity;
    this->observations = new char[strlen(obj.observations)];
    strcpy(this->observations,obj.observations);
    this->isOpen = obj.isOpen;
    this->temp = obj.temp;
}
Fridge& Fridge::operator=(const Fridge &obj) {
    if(this == &obj) {
        return *this;
    }
    delete[] observations;
    this->observations= new char[strlen(obj.observations)];
    strcpy(this->observations,obj.observations);
    this->isOpen = obj.isOpen;
    this->temp = obj.temp;
    return *this;
}
int main()
{

    return 0;
}