#include <iostream>
#include "recursive.h"
#include "p2.h"
#include <cstdlib>
using namespace std;
const int MAXIMUM=200;
int count[2]={0};//global variable
   list_t listA=list_make();
    list_t listB=list_make();
    list_t list=list_make();
int divt=3;
void gen_modt(){
    divt=rand()%7+2;
    cout << endl;
    cout << "bool fn(int a){" << endl;
    cout << "   if (a%" << divt << "==0) return true;" << endl;
    cout << "   else return false;" << endl;
    cout << "}" << endl << endl;
}
void gen_ac(){
    cout <<"int acc(int x,int y){" <<endl;
    int type=0;
    int num=0;
    type=rand()%3;
    switch (type)
    {
    case 1:
        cout << "   return x^y;" << endl;
        break;
    case 2:
        cout << "   return x*y/2;" << endl;
        break;
    default:
        cout << "   return x";
        for (int i = 0; i < 10; i++)
        {   
            num=rand()%6-3;
            if (num<0) cout << num;
            else cout << "+" << num;
           if (i%2==0) cout << "*y";
           else cout << "*x";
        }
        cout <<";" << endl;
        break;
    }
    cout << "}" << endl;
}
bool modt(int a){
    if (a%divt==0) return true;
    else return false;
}
void app(){
    int object;
    int number;
    object=rand()%2;
    number=rand()%20-10;
    if (count[object]>10) return;
    count[object]++;
    if (object==0) {
        cout << "   list=list_make("<< number<< ",list_make());" << endl;
        cout << "   listA=append(listA,list);" << endl;
        list=list_make(number,list_make());
        listA=append(listA,list);
    }
    else {
        cout << "   list=list_make("<< number << ",list_make());" << endl;
        cout << "   listB=append(listB,list);" << endl;
        list=list_make(number,list_make());
        listB=append(listB,list);
    }
}
void combine(){
    cout << "   list_print(append(listA,listB));" << endl;
    cout << "   cout << endl;" << endl;
}
void rev(){
    cout << "   listA=reverse(listA);" << endl;
    cout << "   listB=reverse(listB);" << endl;
    listA=reverse(listA);
    listB=reverse(listB);
}
void ins(){
    int pos;
    if (count[1]+count[0]>40) return;
    if (count[0]==0) {pos=0;}
    else pos=rand()%count[0];
    cout << "   listA=insert_list(listA,listB," << pos << ");" << endl;
    count[0]+=count[1];
    listA=insert_list(listA,listB, (unsigned int )pos );
    if (count[1]+count[0]>40) return;
    if (count[1]==0) {pos=0;}
    else pos=rand()%count[1];
    cout << "   listB=insert_list(listB,listA," << pos << ");" << endl;
    listB=insert_list(listB,listA,(unsigned int )pos);
    count[1]+=count[0];
}
void cut(){
    int number;
    if (count[0]==0) number=0;
    else number=rand()%count[0];
    cout << "   listA=chop(listA," << number << ");" << endl;
    count[0]=count[0]-number;
    listA=chop(listA, (unsigned int )number);
    if (count[1]==0) number=0;
    else number=rand()%count[1];
    cout << "   listB=chop(listB," << number << ");" << endl;
    count[1]=count[1]-number;
    listB=chop(listB,(unsigned int )number);
}
void fil(){
    cout << "   listA=filter(listA,&fn);" << endl;
    cout << "   listB=filter(listB,&fn);" << endl;
    listA=filter(listA,&modt);
    listB=filter(listB,&modt);
    count[0]=size(listA);
    count[1]=size(listB);
}
void ac(){
    int ba=0;
    ba=rand()%6-3;
    cout << "   cout << accumulate(listA,&acc," << ba <<") << endl;" << endl;
    cout << "   cout << accumulate(listA,&acc," << ba <<") << endl;" << endl;
}
void su(){
    cout << "   cout << sum(listA); cout << endl;" << endl;
    cout << "   cout << sum(listB); cout << endl;" << endl;
}
void pr(){
    cout << "   cout << product(listA); cout << endl;" << endl;
    cout << "   cout << product(listB); cout << endl;" << endl;
}
void si(){
    cout << "   cout << size(listA); cout << endl;" << endl;
    cout << "   cout << size(listB); cout << endl;" << endl;
}
int main(){
    cout << "//This test-generator.cpp is written by Hamster." << endl;
    cout << "//Test generator for project 2" << endl;
    cout << "#include <iostream>" << endl;
    cout << "#include " << '"' << "recursive.h" << '"' << endl;
    cout << "#include " << '"' << "p2.h" << '"' << endl;
    cout << endl << "using namespace std;" << endl << endl;
    srand((unsigned int)time(NULL));
    gen_modt();
    gen_ac();
    cout << "int main(){" << endl;

    //main body
    //define variables
    cout << "   list_t listA=list_make();" << endl;
    cout << "   list_t listB=list_make();" << endl;
    cout << "   list_t list=list_make();" << endl; 
 
    
    int op;
    for (int i = 0; i < MAXIMUM; i++)
    {
        op=rand()%25;
        switch (op)
        {
        case 1:
            combine();
            break;
        case 2:
            rev();
            break;
        case 3:
            ins();
            break;
        case 4:
            cut();
            break;
        case 5:
            fil();
            break;
        case 6:
            ac();
            break;
        case 7:
            su();
            break;
        case 8:
            pr();
            break;
        case 9:
            si();
            break;
        default:
            app();
            break;
        }
        cout << "   list_print(listA);cout << endl;list_print(listB);cout << endl;" << endl;
    }
    
    cout << "   return 0;" << endl;
    cout << "}" << endl;
    return 0;
}