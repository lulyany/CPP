//header
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;

//claim
bool isTriangle(int n);
bool isPower(int n);
bool isSum(int n);
bool isAbundant(int n);

int main() {
    ifstream in("general-test.txt");
    ofstream outfile;
    outfile.open("ly_out.txt");
    string temp = string();
    vector<int> testNum, testCat;
    int val,cat;
    while (getline(in,temp)){
        stringstream ss;
        ss << temp;
        ss >> val >> cat;
        testNum.push_back(val);
        testCat.push_back(cat);
    }
    for (int i=0;i< testNum.size();++i){
        bool flag = 0;
        if (testCat[i] == 1)
            flag = isTriangle(testNum[i]);
        else if (testCat[i]==2)
            flag = isPower(testNum[i]);
        else if (testCat[i]==3)
            flag = isSum(testNum[i]);
        else
            flag = isAbundant(testNum[i]);

            if (flag == true)
                outfile << "Pass" << endl;
            else
                outfile << "Fail" << endl;
    }
    outfile.close();
    return 0;
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