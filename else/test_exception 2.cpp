#include <iostream>
using namespace std;

    void test(int n=6) {
        int m;
        cin >> m;
        cout << m << n << endl;
    }

int main(){
    int input;
    cin >> input;
    
    test(input);
    

    
    
    struct lover {
        int age;
        int height;
    };

    lover ZhouZixi = {20, 165};
    try{
        if (input==9) throw ZhouZixi;
        // if (input) throw 20;
        // if (input) throw 20;
    }
    
    catch (int n) {
        if ( n==10 ) cout << "inappropriate" << endl;
        if ( n==20 ) cout << "appropriate" << endl;
    }

    catch (struct lover temp)
    {
        if (temp.age == 20) cout << temp.age << endl;
    }


    catch (double n) {
        if ( n==3.3 ) cout << "inappropriate" << endl;
    }    
}