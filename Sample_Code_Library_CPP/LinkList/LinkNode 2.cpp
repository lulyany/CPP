#include <iostream>

using namespace std;
struct ListNode
{
    double value;
    ListNode *next;
    // Constructor
    ListNode(double value1, ListNode *next1 = nullptr)
    {
        value = value1; next = next1;
    }
};
int main(){
    ListNode *secondPtr = new ListNode(13.5);
    ListNode *head = new ListNode(12.5, secondPtr);
    cout << head->value << endl;
}