//header
#include <iostream>
#include <cmath>

using namespace std;

//claim
bool isTriangle(int n);
bool isPower(int n);
bool isSum(int n);
bool isAbundant(int n);

int main()
{
    //initialize
    int number = 0;
    int choice = 0;
    bool flag;

    //judge the input
    while (!((number > 0 && number <= 10000000 && choice >= 1 && choice <= 4)))
    {
        cout << "Please enter the integer and the test choice: ";
        cin >> number >> choice;
    }

    //run the judger of choice 1
    if (choice == 1)
    {
        flag = isTriangle(number);
    }

    //run the judger of choice 2
    if (choice == 2)
    {
        flag = isPower(number);
    }

    //run the judger of choice 3
    if (choice == 3)
    {
        flag = isSum(number);
    }

    //run the judger of choice 4
    if (choice == 4)
    {
        flag = isAbundant(number);
    }

    //output the result
    if (flag == true)
        cout << "Pass" << endl;
    if (flag == false)
        cout << "Fail" << endl;
}

//judger of choice 1
bool isTriangle(int n)
{
    int i;

    for (i = 0; i * (i + 1) < 2 * n; i++);
    return (i * (i + 1) == 2 * n);
}

//judger of choice 2
bool isPower(int n)
{
    //int the flag of choice two
    int flag_2 = 0;
    //the max of i can be sqrt(n)
    for (int i = 0; i <= sqrt(n); i++)
    {
        for (int j = 2; j <= (log(n) / log(2)); j++)
        {
            if (pow(i, j) == n)
                flag_2 = 1;
        }
    }
    if (flag_2 == 0)
        return false;
    else
        return true;
}

//judger of choice 3
bool isSum(int n)
{
    //int the flag of choice 3
    int flag_3 = 0;
    int sum = 0;

    for (int i = 0; i <= sqrt(n); i++)
    {
        sum = 0;
        for (int j = 0; j <= n; j++)
        {
            sum += pow((i + j), 2);
            if (sum == n)
            {
                flag_3 = 1;
            }
        }
    }
    if (flag_3 == 0)
        return false;
    else
        return true;
}

//judger of choice 4
bool isAbundant(int n)
{
    //int the sum 
    int sum = 0;
    for (int i = 1; i < n; i++)
    {
        if ((n % i) == 0)
        {
            sum += i;
        }
        if (sum > n)
            break;  //here to save time
    }
    if (sum > n)
        return true;
    else
        return false;
}