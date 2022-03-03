#include <iostream>
using namespace std;

class Cow
{
public:
    Cow(int i = 0) { grass = i; }
    void eat();
    //void eat(int i=0){cout<<"It's not my food";}

protected:
    int grass;
};


void Cow::eat()
{
    if (grass > 0)
        cout << "I am full" << endl;
    else
        cout << "I am hungry" << endl;
}

class SickCow : public Cow
{
    public: 
        void eat(int i=100){grass=i; cout<<grass<<endl;}
    private:
};

int main()
{
    Cow cow1;
    cow1.eat();
    //Cow *cow2;
    //cow2=new Cow[2];
    //*(cow2+1)=Cow(5);
    //(cow2+1)->eat();
    SickCow cow3;
    cow3.eat();
    //delete[] cow2;
}