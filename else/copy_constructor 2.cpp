#include<iostream>

using namespace std;

class People{
private:
	int m_age;
public:
	People(int age):m_age(age){
		cout << "constructor" << endl;
	}
 
	People(const People& p){
		cout << "copy constructor" << endl; 
	}
 
	People& operator=(const People& p1){
        cout << "assignment operator" << endl;
        m_age = p1.getAge();
        return *this;
    }
 
	~People(){
		cout << "destructor" << endl;
	}
	int getAge() const{
		return m_age;
	}
};

int main(){
//测试代码
    People p1(18);
    cout << "p1's age " << p1.getAge() << endl;
    People p2 = p1;
    cout << p2.getAge() << endl; 
    cout << "p2's age " << p2.getAge() << endl;
    p2 = p1;
    cout << p2.getAge() << endl; 
    
    //证明不是浅拷贝
    cout << &p1 << endl;
    cout << &p2 << endl;
    return 0;
}

//从结果可见destructor是程序最后默认执行的
//正如这里显式声明copy constructor了，才是深拷贝。地址不一样。
//https://baike.baidu.com/item/深拷贝/22785317