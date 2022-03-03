#include "assignment.h"
#include <iostream>
using namespace std;

int ifunction_1(int a);
int ifunction_2(int M);

void ex4()
{
    int choice;
    int input;
    int ans;
    cin >> choice;
    cin >> input;
    switch (choice)
    {
    case 1:
        ans = ifunction_1(input);
        break;
    default:
        ans = ifunction_2(input);
        break;
    }
    cout << ans << endl;
}

int ifunction_1(int a)
{
    int times = 0;
    while (a != 1)
    {
        if (a % 2 == 0)
        {
            a /= 2;
        }
        else
        {
            a = 3 * a + 1;
        }

        times++;
    }
    return times;
}
int ifuntion_2(int M)
{
    int *n = new int(M);
    int max = 0;
    int answer = 0;
    int start = 2;
    int temp = 0;
    for (int i = start; i <= M; i++)
    {
        temp = ifunction_1(i);
        if (temp > max)
        {
            max = temp;
            answer = i;
        }
    }
    delete n;
    return answer;
}

#ifdef JOJ
int main()
{
    ex4();
    return 0;
}
#endif
