#include <iostream>
#include <fstream>
using namespace std;

void tryy(){
    return 3;
}


int main(){
    int foo;
    string line;
    ifstream iFile;
    

    // method 1
    cout<<"------method 1"<<endl;
    iFile.open("io_test_txt");
    while(iFile) { 
        getline(iFile, line); 
        if(iFile) {
            cout << line << endl;
        }
    }
    iFile.close(); 
    
    cout<<"------method 2"<<endl;

    // method 2
    iFile.open("io_test_txt");
    while(getline(iFile, line)) {
        cout << line << endl;   
    }
    iFile.close();
    
    
    cout<<"------method 3"<<endl;
    //method 3
    iFile.open("io_test_txt");
    // assert(!iFile);
    while(iFile) {
        getline(iFile, line);   
        cout << line << endl;
    }
    iFile.close();

}