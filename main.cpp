#include <algorithm>
#include <iostream>
#include <cstring>
#include <cfloat>
#include <random>
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

class Fridge;

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
    int get_count() const {
        return this->count;
    }
    void set_ingredients(const Ingredient* obj){
        delete[] this->ingredients;
        this->ingredients = new Ingredient[this->count];
        for (int i=0;i<this->count;i++) {
            this->ingredients[i] = obj[i];
        }
    }
    void set_can_make(bool can){
        this->can_make = can;
    }
    void set_instructions(const char* inst) {
        strcpy(this->instructions,inst);
    }
    void set_count(int cnt) {
        this->count = cnt;
    }
    Ingredient *get_ingredients() const{
        return this->ingredients;
    }

    char *get_instructions() const {
        return this->instructions;
    }
    bool get_can_make() const {
        return this->can_make;
    }
    void check_can_make(const Fridge&);
    void how_many(const Fridge&);
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
        for (int i=0;i<count;i++) {
            this->ingredients[i] = ingred[i];
        }

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
    for (int i=0;i<obj.count;i++) {
        this->ingredients[i] = obj.ingredients[i];
    }
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
    this->count= obj.count;
    for (int i=0;i<this->count;i++) {
        this->ingredients[i]= obj.ingredients[i];
    }
    this->instructions = new char[256];
    strcpy(this->instructions,obj.instructions);
    this->can_make = obj.can_make;
    return *this;
}
std::istream& operator>>(std::istream& Rin, Recipe& obj) {
    char buffer[256];
    std::cout<<"Instructions: ";
    Rin>>buffer;
    obj.set_instructions(buffer);
    std::cout<<"Can you make it? [Y/N]";
    char answer;
    Rin>>answer;
    if (answer=='Y') {
        obj.set_can_make(true);
    }
    else {
        obj.set_can_make(false);
    }
    std::cout<<"Count: ";
    int cnt;
    Rin>>cnt;
    obj.set_count(cnt);
    std::cout<<"Ingredients: ";
    Ingredient* ing = new Ingredient[cnt];
    for (int i=0;i<cnt;i++) {
        Rin>>ing[i];
    }
    obj.set_ingredients(ing);
    delete[] ing;
    return Rin;
}
std::ostream& operator<<(std::ostream& Rout, const Recipe& obj) {
    Rout<<"Recipe: "<<obj.get_instructions()<<"\n";
    Rout<<"Count: "<<obj.get_count()<<"\n";
    Rout<<"Can make: "<<obj.get_can_make()<<"\n";
    Rout<<"Ingredients: ";
    for (int i=0;i<obj.get_count();i++)
        Rout<<obj.get_ingredients()[i]<<'\n';
    return Rout;
}
class Fridge {
private:
    float temp;
    bool isOpen;
    int capacity;
    int no_items;
    Ingredient* food;
    char *observations;
    float rand_temp() {
        std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> number(0.0,30.0);
        float num=number(rng);
        return num;
    }
public:
    Fridge();
    Fridge(const char*,int,bool,int,const Ingredient*);
    ~Fridge();
    Fridge(const Fridge &obj);
    Fridge& operator=(const Fridge &obj);
    float get_temp() const {
        return this->temp;
    }
    bool is_open() const {
        return this->isOpen;
    }
    void set_open(bool open) {
        this->isOpen = open;
        if (open) {
            this->temp = rand_temp();
        }
        else {
            this->temp = 0.0;
        }
    }
    void set_capacity(int capa) {
        this->capacity = capa;
    }
    int get_capacity() const {
        return this->capacity;
    }
    int get_no_items() const {
        return this->no_items;

    }
    void set_no_items(int items) {
        this->no_items = items;
        delete[] this->food;
        this->food = new Ingredient[items];
    }
    Ingredient* get_food() const {
        return this->food;
    }
    void set_food(const Ingredient* f) {

        for (int i=0;i<this->no_items;i++) {
            this->food[i] = f[i];
        }
    }
    char* get_observations() const {
        return this->observations;
    }
    void set_observations(const char* obs) {
        strcpy(this->observations,obs);
    }
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
Fridge::Fridge(const char* observations, int capacity,bool isOpen,int no_items, const Ingredient *food) {
    this->capacity = capacity;
    this->observations = new char[strlen(observations)+1];
    strcpy(this->observations,observations);
    this->isOpen = isOpen;
    if (this->isOpen) {
        this->temp = rand_temp();
    }
    else {
        this->temp = 0.0;
    }

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
    this->observations = new char[strlen(obj.observations)+1];
    strcpy(this->observations,obj.observations);
    this->isOpen = obj.isOpen;
    this->temp = obj.temp;
    this->no_items = obj.no_items;
    this->food = new Ingredient[obj.no_items];
    for (int i=0;i<obj.no_items;i++) {
        this->food[i] = obj.food[i];
    }
}
Fridge& Fridge::operator=(const Fridge &obj) {
    if(this == &obj) {
        return *this;
    }
    delete[] observations;
    delete[] food;
    this->observations= new char[strlen(obj.observations)+1];
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

std::ostream& operator<<(std::ostream& Fout, const Fridge &obj) {
    Fout<<"Temperature: " << obj.get_temp() << '\n';
    Fout<<"Capacity: " << obj.get_capacity() << '\n';
    Fout<<"Number of items: " << obj.get_no_items() << '\n';
    Fout<<"Observations: " << obj.get_observations() << '\n';
    Fout<<"Contents: ";
    for (int i=0;i<obj.get_no_items();i++) {
        Fout<<obj.get_food()[i] << ' ';
    }
    Fout<<'\n';
    return Fout;
}

std::istream& operator>>(std::istream& Fin, Fridge &obj) {
    std::cout<<"How many items are there? "<<'\n';
    int items;
    Fin>>items;

    obj.set_no_items(items);
    std::cout<<"Max capacity: ";
    int capacity;
    Fin>>capacity;
    obj.set_capacity(capacity);
    char ans;
    std::cout<<"Is it open?[Y/N] " <<'\n';
    std::cin>>ans;
    bool isOpen;
    if (ans == 'Y') {
        isOpen = true;
    }
    else {
        isOpen = false;
    }
    obj.set_open(isOpen);
    char buffer[100];
    std::cout<<"Any observations? ";
    Fin>>buffer;
    obj.set_observations(buffer);
    Ingredient* food = new Ingredient[items];
    for (int i=0;i<items;i++) {
        Fin>>food[i];
    }
    obj.set_food(food);
    return Fin;
}



class CookSesh {
private:
    int start_time;
    int* family_ratings;
    int num_rating;
    char* cookName;
    int rand_ratenum() {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> number(1,10);
        int num=number(rng);
        return num;
    }
    int rand_rating() {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> rating(1,10);
        int rate = rating(rng);
        return rate;
    }
public:
    CookSesh();
    CookSesh(const char*,int);
    ~CookSesh();
    CookSesh(const CookSesh &obj);
    CookSesh& operator=(const CookSesh &obj);
    void set_start_time(int s) {
        start_time = s;
    };
    void set_name(const char* name) const {
        strcpy(this->cookName,name);
    };
    char* get_name() const {
        return this->cookName;
    };
    int get_start_time() const {
        return this->start_time;
    }
    int get_num_rating() const {
        return this->num_rating;
    }
    int* get_family_ratings() const {
        return this->family_ratings;
    }
};

CookSesh::CookSesh() {
    cookName= new char[8];
    strcpy(cookName,"No cook");
    start_time = 0;
    family_ratings= nullptr;
    num_rating= 0;

}
CookSesh :: CookSesh(const char *name, int start){
    this->start_time= start;
    this->num_rating= rand_ratenum();
    this->family_ratings= new int[this->num_rating];
    for (int i=0;i<this->num_rating;i++) {
        family_ratings[i]= rand_rating();
    }
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
std::istream& operator>>(std::istream &sin, CookSesh &obj) {
    std::cout<<"Enter cook name: ";
    char name[100];
    sin>>name;
    obj.set_name(name);
    std::cout<<"Enter start time: ";
    int start_time;
    sin>>start_time;
    obj.set_start_time(start_time);
    return sin;
}
std::ostream& operator<<(std::ostream &sout, const CookSesh &obj) {
    sout<<"Cook Name: "<<obj.get_name()<<"\n";
    sout<<"Start Time: "<<obj.get_start_time()<<"\n";
    sout<<"Number of Ratings: "<<obj.get_num_rating()<<"\n";
    sout<<"All Ratings: ";
    for (int i=0;i<obj.get_num_rating();i++) {
        sout<<obj.get_family_ratings()[i]<<" ";
    }
    return sout;
}
void Recipe::check_can_make( const Fridge &fridge) {
    bool possibility = this->get_can_make();
    if (possibility == false) {
        std::cout<<"You can't make that yet please learn and come back later."<<'\n';
        return;
    }
    std::cout<<"---- Checking ingredients available -----"<<'\n';
    if (fridge.get_temp()>10) {
        std::cout<<"Ingredients are spoiled! You will get sick!"<<'\n';
        return;
    }
    for (int i=0; i<this->get_count();i++) {
        Ingredient necessary= this->get_ingredients()[i];
        bool found = false;
        for (int j=0;j<fridge.get_no_items();j++) {
            Ingredient available= fridge.get_food()[j];
            if (strcmp(necessary.get_name(),available.get_name())==0) {
                found = true;
                if(available.get_quantity() < necessary.get_quantity()) {
                    std::cout<<"You don't have enough" <<available.get_name()<<'\n';
                    std::cout<<"You need:"<<necessary.get_quantity()-available.get_quantity()<<" "<<necessary.get_name()<<'\n';
                    possibility = false;

                }
                else {
                    std::cout<<"You have enough:"<<available.get_name()<<'\n';
                }

            }
        }
        if (!found) {
            std::cout<< "Missing ingredient" << necessary.get_name()<<'\n';
            possibility=false;
        }
    }
    if (possibility) {
        std:: cout<<"You can start cooking. Good luck and have fun! :))"<<'\n';
    }
    else {
        std:: cout<<"You can't cook that yet. Go to the store!"<<'\n';
    }
    this->set_can_make(possibility);
}

void Recipe::how_many( const Fridge &fridge) {
    check_can_make(fridge);
    double min_ratio= DBL_MAX;
    double ratio = 0;
    //irl with 1 egg  you can make 4 pancakes therefore the end result will be multiplied by 4
    if (this->get_can_make() == true) {
        for (int i=0;i<this->get_count();i++) {
            for (int j=0;j<fridge.get_no_items();j++) {

                if (strcmp(this->get_ingredients()[i].get_name(),fridge.get_food()[j].get_name()) == 0) {
                    ratio = this->get_ingredients()[i].get_quantity()/fridge.get_food()[j].get_quantity();
                }
                min_ratio = std::min(min_ratio,ratio);
            }
        }
        std::cout<<"You can make " << min_ratio*4<<" pancakes"<<'\n';
    }
}




int main()
{

    return 0;
}