#include <iostream>
#include <cstring>
// using namespace std;
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
    void set_quantity(double q) {
        this->quantity = q;
    }
    void set_name(const char* n) {
        delete[] this->name;
        this->name = new char[strlen(n)+1];
        strcpy(this->name,n);
    }
    char* get_name() const{
        return this->name;
    }
    double get_quantity() const{
        return this->quantity;
    }
    const int get_id() const{
        return id;
    }
    // friend std::ostream& operator<<(std::ostream& out, const Ingredient& obj);
    // friend std::istream& operator>>(std::istream& in, Ingredient& obj);

};
int Ingredient::no_ingredients=0;
Ingredient::Ingredient(): id(++no_ingredients) {
    name = new char[1];
    name[0] = '\0';
    quantity = 0.0;
}
Ingredient::Ingredient(const char* n, double q): id(++no_ingredients), quantity(q) {
    this->name = new char[strlen(n)+1];
    strcpy(this->name, n);
    this->quantity = q;
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
std::ostream& operator<<(std::ostream& out, const Ingredient& obj) {
    out<<"ID: " << obj.get_id()<<'\n';
    out<<"Name: "<<obj.get_name()<<'\n';
    out<<"Quantity: "<<obj.get_quantity()<<'\n';
    return out;
}

std::istream& operator>>(std::istream& in, Ingredient& obj) {
    char buffer[100];
    std::cout<<"Name: ";
    in>>buffer;
    obj.set_name(buffer);
    std::cout<<"Quantity: ";
    double q;
    in>>q;
    obj.set_quantity(q);
    return in;
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
    int no_items;
    Ingredient* food;
    char *observations;
public:
    Fridge();
    Fridge(const char*,float,int,bool,int,const Ingredient*);
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
    no_items=0;
    food = nullptr;
}
Fridge::Fridge(const char* observations, float temp, int capacity,bool isOpen,int no_items, const Ingredient *food) {
    this->capacity = capacity;
    this->observations = new char[strlen(observations)];
    strcpy(this->observations,observations);
    this->isOpen = isOpen;
    this->temp = temp;
    this->food = new Ingredient[no_items];
    this->no_items = no_items;
    for (int i=0;i<no_items;i++) {
        this->food[i] = food[i];
    }
}
Fridge::~Fridge() {
    delete[] observations;
    delete[] food;
}

Fridge::Fridge(const Fridge &obj) {
    this->capacity = obj.capacity;
    this->observations = new char[strlen(obj.observations)];
    strcpy(this->observations,obj.observations);
    this->isOpen = obj.isOpen;
    this->temp = obj.temp;
    this->no_items = obj.no_items;
    this->food = new Ingredient[obj.no_items];
}
Fridge& Fridge::operator=(const Fridge &obj) {
    if(this == &obj) {
        return *this;
    }
    delete[] observations;
    delete[] food;
    this->observations= new char[strlen(obj.observations)];
    strcpy(this->observations,obj.observations);
    this->isOpen = obj.isOpen;
    this->temp = obj.temp;
    this->no_items = obj.no_items;
    this->food = new Ingredient[obj.no_items];
    for (int i=0;i<obj.no_items;i++) {
        this->food[i] = obj.food[i];
    }
    return *this;
}


class CookSesh {
private:
    int start_time;
    int* family_ratings;
    int num_rating;
    char* cookName;
public:
    CookSesh();
    CookSesh(const char*,int,int);
    ~CookSesh();
    CookSesh(const CookSesh &obj);
    CookSesh& operator=(const CookSesh &obj);
};

CookSesh::CookSesh() {
    cookName= new char[8];
    strcpy(cookName,"No cook");
    start_time = 0;
    family_ratings= nullptr;
    num_rating= 0;

}
CookSesh :: CookSesh(const char *name, int start, int num){
    this->start_time= start;
    this->family_ratings= new int[num];
    for (int i=0;i<num;i++) {
        family_ratings[i]= 10;
    }
    this->num_rating= num;
    this->cookName= new char[16];
    strcpy(this->cookName,name);
}

CookSesh::~CookSesh(){
    delete[] family_ratings;
    delete[] cookName;
}
CookSesh::CookSesh(const CookSesh &obj) {
    this->start_time= obj.start_time;
    this->family_ratings= new int[obj.num_rating];
    for (int i=0;i<obj.num_rating;i++) {
        family_ratings[i]= obj.family_ratings[i];
    }
    this->num_rating= obj.num_rating;
    this->cookName= new char[16];
    strcpy(this->cookName,obj.cookName);
}
CookSesh& CookSesh::operator=(const CookSesh &obj) {
    if (this == &obj ) {
        return *this;
    }
    delete[] family_ratings;
    delete[] cookName;
    this->start_time= obj.start_time;
    this->family_ratings= new int[obj.num_rating];
    for (int i=0;i<obj.num_rating;i++) {
        family_ratings[i]= obj.family_ratings[i];
    }
    this->num_rating= obj.num_rating;
    this->cookName= new char[16];
    strcpy(this->cookName,obj.cookName);
    return *this;
}
int main()
{

    return 0;
}