#include <iostream>

using namespace std;

const int  MAX_NAME_SIZE =  256;

typedef struct Lover{
    string name;
    char boyfriend[MAX_NAME_SIZE];
    int age;
}MakeLover;


enum ZixiZhou_t {laopo, baobei, xixi};

int main (){
    ZixiZhou_t Today = laopo;
    
    MakeLover ZixiZhou = {"ZixiZhou", "YanLu", 20};
    
    const string type[] = {"laopo","baobei", "xixi"};

    cerr << "123" << endl;
    cout << ZixiZhou.boyfriend << endl;
    cout << "Today ZixiZhou is " << type[Today] << endl;
    cout << "Today ZixiZhou is " << type[Today] << endl;
    
}