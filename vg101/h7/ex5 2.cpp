#include "assignment.h"
#include <iostream>

using namespace std;

static const char GRADES[] = {'F', 'F', 'F', 'F', 'F', 'F', 'D', 'C', 'B', 'A', 'A'};
class Grade
{
private:
    char ltr;
    char prct;

public:
    void GradePrct(Grade *grade, int prct)
    {

        grade->prct = (char)prct;
        grade->ltr = GRADES[prct / 10];
    }
    void GradeLtr(Grade *grade, char ltr)
    {
        grade->ltr = ltr;
        grade->prct = 100 - (ltr - 'A') * 10 - 5;
    }
    void printGrade(Grade *grade)
    {
        cout << "Grade: " << (int)grade->prct << " -> " << (char)grade->ltr << endl;
        // printf( "Grade: %d -> %c\n", grade->prct, grade->ltr );
    }
};

int main()
{
    Grade g;
    int prct;
    cout << "Input two space seprated grades (1st in %%, 2nd in letter): ";
    cin >> prct;
    g.GradePrct(&g, prct);
    g.printGrade(&g);
    while (cin.peek() == '\n' || cin.peek() == ' ')
    {
        cin.get();
    }
    g.GradeLtr(&g, (char)cin.get());
    g.printGrade(&g);
    return 0;
}