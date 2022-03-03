// #include "dlist_impl.h"
#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

const string operators = "+-*/rndpcaq";

void binary_op(Dlist<int> &stack, int index)
{
    // initialize
    int *a = stack.removeFront();
    int *b = stack.removeFront();

    if (index == 0)
    {
        stack.insertFront(new int(*b + *a));
        delete a;
        delete b;
    }
    else if (index == 1)
    {
        stack.insertFront(new int(*b - *a));
        delete a;
        delete b;
    }
    else if (index == 2)
    {
        stack.insertFront(new int(*b * *a));
        delete a;
        delete b;
    }
    else if (index == 3)
    {
        if (*a == 0)
        {
            // put back as original
            stack.insertFront(b);
            stack.insertFront(a);
            throw(1);
        }
        stack.insertFront(new int(*b / *a));
        delete a;
        delete b;
    }
    else if (index == 4)
    {
        stack.insertFront(a);
        stack.insertFront(b);
    }
}

void unary_op(Dlist<int> &stack, int index)
{
    int *a = stack.removeFront();

    if (index == 5)
    {
        *a = *a * (-1);
        stack.insertFront(a);
    }
    else if (index == 6)
    {
        stack.insertFront(a);
        stack.insertFront(a);
    }
    else if (index == 7)
    {
        cout << *a << endl;
        stack.insertFront(a);
    }
}

void zeronary_op(Dlist<int> &stack, int index)
{
    if (index == 8)
    {
        // while(!stack.isEmpty()){
        // 	int* tmp = stack.removeFront();
        // 	delete tmp;
        // }
        stack.~Dlist();
    }
    else if (index == 9)
    {
        Dlist<int> copy(stack);

        while (!copy.isEmpty())
        {
            cout << *copy.removeFront() << " ";
        }
        cout << endl;
    }
    else if (index == 10)
    {
        exit(0);
    }
}

int main()
{
    Dlist<int> stack;
    while (true)
    {
        // every loop is a line input
        // try
        try
        {
            // every cin is a line
            string line;
            cin >> line;

            int index = -1;
            char op = line[0];

            if (line.length() == 1)
            {
                for (int i = 0; i < operators.length(); i++)
                {
                    if (op == operators[i])
                    {
                        index = i;
                        break;
                    }
                }
                if (line[0] >= '0' && line[0] <= '9')
                {
                    stack.insertFront(new int(line[0] - '0'));
                    continue;
                }
            }
            else if (line.length() > 1)
            {

                int value(0);
                int symbol(1);

                // judge if a negative number
                if (line[0] == '-')
                    symbol = -1;

                for (int i = 0; i < (line.length()); i++)
                {
                    int num = line[i] - '0';
                    if ((num >= 0) && (num <= 9))
                    {
                        value = value * 10 + num;
                    }
                    else
                    {
                        throw(1.5); // TODO:check
                    }
                }
                stack.insertFront(new int(value * symbol));
                continue;
            }

            if (index >= 0 && index <= 4)
                binary_op(stack, index);
            else if (index >= 5 && index <= 7)
                unary_op(stack, index);
            else if (index >= 8 && index < (operators.length()))
            {
                zeronary_op(stack, index);
                if (index == 10)
                    break;
            }
            else
                throw(1.5);
        }

        // catch
        catch (double e)
        {
            cout << "Bad input\n";
        }

        catch (emptyList e)
        {
            cout << "Not enough operands\n";
        }

        catch (int e)
        {
            cout << "Divide by zero\n";
        }
    }
    return 0;
}