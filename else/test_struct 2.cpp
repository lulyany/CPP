#include <iostream>

using namespace std;

void get_age(struct Lover &lover);
void change_name(struct  Lover &lover);

const int  MAX_NAME_SIZE =  256;

struct Lover{
    string name;
    char boyfriend[MAX_NAME_SIZE];
    int age;
};

int main() {
    Lover ZixiZhou = {"ZixiZhou", "YanLushishabi", 20};
    

    cout << "What's your name?" << endl << "ZixiZhou" << endl;
    cout << "Who's your boyfriend?" << endl;
    cout << ZixiZhou.boyfriend << endl;
    change_name(ZixiZhou);
    get_age(ZixiZhou);
}

void get_age(struct Lover &lover){
    cout << "What's your age?" << endl;
    cout << lover.age << endl;
}

void change_name(struct Lover &lover){
    cout << "What's your name now" << endl;
    lover.name = "Mrs. Lu";
    cout << lover.name << endl;
}