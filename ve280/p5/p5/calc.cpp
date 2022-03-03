// #include "dlist_impl.h"
#include "dlist.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

const string operators = "+-*/rndpcaq";

void binary_op(Dlist<int>& stack, int index);
void unary_op(Dlist<int>& stack, int index);
void zeronary_op(Dlist<int>& stack, int index);

int main()
{
    Dlist<int> stack;
    while (true) {
        // every loop is a line input
        // try
        try {
            // every cin is a line
            string line;
            cin >> line;

            if (line.length() == 1 && line[0] >= '0' && line[0] <= '9') {
                int* tmp = new int(line[0] - '0');
                stack.insertFront(tmp);
                // delete tmp;
                // continue;
            } else if (line.length() > 1) {
                int value(0);
                int symbol(1);

                // judge if a negative number

                for (int i = 0; i < (line.length()); i++) {
                    if ((i == 0) && (line[i] == '-')) {
                        symbol = -1;
                        continue;
                    }
                    int num = line[i] - '0';
                    if ((num >= 0) && (num <= 9)) {
                        value = value * 10 + num;
                    } else {
                        throw 1.5; // TODO:check
                    }
                }
                // int *tmp = new int(value * symbol);
                stack.insertFront(new int(value * symbol));
                // delete tmp;
                // continue;
            }

            else {
                int index = -1;
                char op = line[0];
                for (int i = 0; i < operators.length(); i++) {
                    if (op == operators[i]) {
                        index = i;
                        break;
                    }
                }
                if (index >= 0 && index <= 4)
                    binary_op(stack, index);
                else if (index >= 5 && index <= 7)
                    unary_op(stack, index);
                else if (index >= 8 && index < (operators.length())) {
                    zeronary_op(stack, index);
                    if (index == 10)
                        break;
                } else
                    throw 1.5;
            }
        }
        // catch
        catch (double e) {
            cout << "Bad input\n";
        }

        catch (emptyList e) {
            cout << "Not enough operands\n";
        }

        catch (int e) {
            cout << "Divide by zero\n";
        }
    }
    return 0;
}

void binary_op(Dlist<int>& stack, int index)
{
    // int e_it = 2;
    if (stack.isEmpty()) {
        emptyList e;
        throw e;
    }

    // initialize
    int* a = stack.removeFront();
    if (stack.isEmpty()) {
        stack.insertFront(a);
        emptyList e;
        throw e;
    }

    int* b = stack.removeFront();

    if (index == 0) {
        stack.insertFront(new int(*b + *a));
    } else if (index == 1) {
        stack.insertFront(new int(*b - *a));
    } else if (index == 2) {
        stack.insertFront(new int(*b * *a));
    } else if (index == 3) {
        if (*a == 0) {
            // put back as original
            stack.insertFront(b);
            stack.insertFront(a);
            throw 2;
        }
        stack.insertFront(new int(*b / *a));
    } else if (index == 4) {
        stack.insertFront(a);
        stack.insertFront(b);
        return;
    }
    // else cout<<"wrong in binary"<<endl;
    delete a;
    delete b;
}

void unary_op(Dlist<int>& stack, int index)
{
    int* a = stack.removeFront();

    if (index == 5) {
        *a = *a * (-1);
        stack.insertFront(a);
    } else if (index == 6) {
        stack.insertFront(a);
        stack.insertFront(new int(*a));
    } else if (index == 7) {
        cout << *a << endl;
        stack.insertFront(a);
    }
    // else cout<<"wrong in unary"<<endl;
}

void zeronary_op(Dlist<int>& stack, int index)
{
    if (index == 8) {
        // while(!stack.isEmpty()){
        // 	int* tmp = stack.removeFront();
        // 	delete tmp;
        // }
        stack.~Dlist();
    } else if (index == 9) {
        Dlist<int> copy(stack);

        while (!copy.isEmpty()) {
            int* ob = copy.removeFront();
            cout << *ob << " ";
            delete ob;
            // cout << endl;
        }
        cout << endl;
    } else if (index == 10) {
        exit(0); // return 0?
    }
    // else cout<<"wrong in zeronary"<<endl;
}