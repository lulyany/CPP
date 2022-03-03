#include <iostream>

using namespace std;

// void f1(int x) { x *= 2; }

// int *f2(int &x) {
//   int *address = &x;
//   x *= 2;
//   return address;
// }

int main() {
  int a = 4;
  int b = 5;

  // int *p1 =&c;
  //       int *p2 = &b;
  //       *p1 = a;

  //     int *addr;
  //     f1(a);
  //     addr = f2(b);

  //       const int * cptr = &c;
  //       const int & cref = c;
  //       c = 24;

  //     cout << "a = "<< a << endl;
  //     cout << "b = " << b << endl;
  //     cout << "&b = "<< &b << endl;
  //     cout << "addr = "<< addr << endl;
  //     cout << "*addr = " << *addr << endl;
  //     cout << "c = "<< c << endl;
  //     cout << "cref = " << cref << endl;
  //     cout << p1 << endl;
  //     cout << *p1 << endl;
  //     cout << p2 << endl;

    const int * d = &a;        
    cout << *d << endl;

}
