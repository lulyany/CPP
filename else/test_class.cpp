#include <iostream>
#include <iomanip>

using namespace std;


class Lover {
    char* name;
    int age;
    int height;

public:
    Lover(int new_age = 0) {age = new_age; }
    void set_age(int new_age);
    void show_age();
    ~Lover(){;}
};

 void Lover::set_age(int new_age){
     age = new_age;
 }

void Lover::show_age(){
    cout << age << endl;
}

 int main(){
    // Lover* ptr= new Lover;
    Lover *ptr= new Lover;
    *ptr = Lover(20);
    
    *(ptr+1) = Lover(21);    
    
    Lover zzx(25);
    
    cout << ptr << endl;
    
    ptr->show_age();
    
    cout << ptr+1<< endl;
    
    (ptr+1) -> show_age();
    
    cout << &zzx <<endl;
    zzx.show_age() ;

    cout<< sizeof(Lover);

    // ptr = new Lover;
    // *ptr -> set_age(20);
    // Lover zzx(20);
    // // ptr = &zzx;
    // zzx.show_age();
    // zzx.set_age(21);
    // zzx.show_age(); 
}