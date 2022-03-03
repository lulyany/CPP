// #include "dlist_impl.h"
#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

enum MEMBERSHIP
{
    PLATINUM,
    GOLD,
    SILVER,
    REGULAR
};
const string membership[4] = {"platinum", "gold", "silver", "regular"};

class Line
{
public:
    int timestamp;
    string name;
    MEMBERSHIP status;
    unsigned int duration;
};

MEMBERSHIP convert_membership(const string &str)
{
    for (int i = 0; i < 3; i++)
    {
        if (str == membership[i])
        {
            return static_cast<MEMBERSHIP>(i);
        }
    }
    return REGULAR;//must have a return value
}

int main()
{
    Dlist<Line> *queue = new Dlist<Line>[4];

    // initilize line nums
    int line_total;
    cin >> line_total;
    Line *list = new Line[line_total];

    string tmp = "";
    for (int i = 0; i < line_total; i++)
    {
        cin >> list[i].timestamp >> list[i].name >> tmp >> list[i].duration;
        list[i].status = convert_membership(tmp);
        queue[convert_membership(tmp)].insertBack(&list[i]);
    }
    int tick = 0;
    int time_end = 0;
    while (true)
    {
        cout << "Starting tick #" << tick << endl;
        for (int i = 0; i < line_total; i++)
        {
            if (&list[i] != nullptr && list[i].timestamp == tick)
            {
                cout << "Call from " << list[i].name << " a " << membership[list[i].status] << " member\n";
            }
        }
        
        bool busy = (tick < time_end);
        
        if (!busy)
        {
            int terminate = 0;
            for (int i = 0; i < 4; i++)
            {
                if (!queue[i].isEmpty())
                {
                    Line *now = queue[i].removeFront();
                    cout << "Answering call from " << now->name << endl;
                    time_end = tick + now->duration;
                    break;
                }
                else
                {
                    terminate++;
                }
            }
            if (terminate == 4) break;
        }
        tick++;
    }
    // delete[] list;
    // delete[] queue;
    return 0;
}
