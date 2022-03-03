#include <iostream>
using namespace std;

class TestClass
{
private:
    int val;

public:
    TestClass() { cout << "A default constructor" << endl; }
    TestClass(int a) : val(a)
    {
        cout << "A one-param constructor" << endl;
    }
    ~TestClass() { cout << "A destructor" << endl; }
};
int main()
{
    size_t num = 3;
    TestClass *pointer_to_array = new TestClass[num];
    delete[] pointer_to_array;
    TestClass **array_of_pointers = new TestClass *[num];
    for (size_t i = 0; i < num; i++)
        array_of_pointers[i] = new TestClass(i);
    // First delete the objects pointing to, then delete the memory for
    // pointers themselves
    for (size_t i = 0; i < num; i++)
        delete (array_of_pointers[i]);
    delete[] array_of_pointers;
    return 0;
}