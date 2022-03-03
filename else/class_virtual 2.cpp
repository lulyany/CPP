#include <iostream>
using namespace std;

class A
{
public:
     virtual void display() { cout << "A" << endl; }//can be overwrite
     // void display() { cout << "A" << endl; }
};

class B : public A
{
public:
     void display() { cout << "B" << endl; }
};

void doDisplay(A *p)
{
     p->display();
     delete p;
}

int main(int argc, char *argv[])
{
     doDisplay(new B());
     return 0;
}

/*
————————————————
版权声明：本文为CSDN博主「yuanchunsi」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/yuanchunsi/article/details/78686417
*/