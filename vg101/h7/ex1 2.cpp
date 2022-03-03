#include "assignment.h"
#include <iostream>
using namespace std;

void ex1()
{
    int iCurrent_year, iCurrent_age, iAnother_year;
    //cout << "please enter the current year" << endl;
    cin >> iCurrent_year;
    //cout << "please enter your current age" << endl;
    cin >> iCurrent_age;
    //cout << "please enter another year" << endl;
    cin >> iAnother_year;
    cout << iAnother_year - iCurrent_year + iCurrent_age << endl;
}

#ifdef JOJ
int main()
{
    ex1();
    return 0;
}
#endif