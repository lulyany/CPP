#include "assignment.h"
//#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include<stack>
#include<queue>
//#include<cstring>
using namespace std;

void ex1_reverse_array()
{
    string s_input;
    getline(cin, s_input);
    int times = count(s_input.begin(), s_input.end(), ' ');
    string s_out[times + 1];
    int i, times_find, a, b = 0;
    string temp;
    while (times_find <= (times-1 ))
    {
        a = s_input.find(' ', i);
        b = s_input.find(' ', i + 1);
        if (i == 0)
          temp = s_input.substr(0, a);
        else
            temp = s_input.substr(a + 1, b);
        
        if (!temp.empty())  cout << temp << ' ';
        i = b;
        times_find++;
    }
    cout << endl;
}

void ex1_ordered_array()
{
    string s_input;
    getline(cin, s_input);
    cout << s_input << endl;
}

void ex1_reverse_vector()
{
    vector<string> s_input;
    string input;
    vector<string>::reverse_iterator it;
    getline(cin, input);
    for (int i = 0; i <= input.length(); i++)
    {
        for (int j = i; j <= input.length(); j++)
        {
            if (isspace(input[j]) || j == input.length())
            {
                s_input.push_back(input.substr(i, j - i));
                i = j;
                break;
            }
        }
    }
    for (it = s_input.rbegin(); it != s_input.rend(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
}
void ex1_ordered_vector()
{
    vector<string> s_input;
    string temp;
    vector<string>::iterator it;
    cin >> temp;
    s_input.push_back(temp);
    for (it = s_input.begin(); it != s_input.end(); it++)
    {
        cout << *it << endl;
    }
}

void ex1_reverse_stack(){
    stack<string> a;
    string input; getline(cin,input);
 for (int i = 0; i <= input.length(); i++)
    {
        for (int j = i; j <= input.length(); j++)
        {
            if (isspace(input[j]) || j == input.length())
            {
                a.push(input.substr(i, j - i));
                i = j;
                break;
            }
        }
    }
    int size =a.size(); 
    for(int i=1;i<=size;i++){
        cout<<a.top()<<' ';
        a.pop();
    }
    cout<<endl;

}
  
void ex1_ordered_queue(){
   queue <string> a;
   string input; getline(cin,input);
 for (int i = 0; i <= input.length(); i++)
    {
        for (int j = i; j <= input.length(); j++)
        {
            if (isspace(input[j]) || j == input.length())
            {
                a.push(input.substr(i, j - i));
                i = j;
                break;
            }
        }
    }
    int size =a.size(); 
    for(int i=1;i<=size;i++){
        cout<<a.front()<<' ';
        a.pop();
    }
    cout<<endl; 
}




int main()
{
    ex1_reverse_array();
}