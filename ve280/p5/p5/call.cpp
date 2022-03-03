// #include "dlist_impl.h"
#include "dlist.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

enum MEMBERSHIP {
    PLATINUM,
    GOLD,
    SILVER,
    REGULAR
};
const string membership[4] = { "platinum", "gold", "silver", "regular" };

class Line {
public:
    int timestamp;
    string name;
    MEMBERSHIP status;
    unsigned int duration;
};

MEMBERSHIP convert_membership(const string& str)
{
    for (int i = 0; i < 4; i++) {
        if (str == membership[i]) {
            return static_cast<MEMBERSHIP>(i);
            // break;
        }
    }
    return GOLD; //must have a return value
}

int main()
{
    //an ADT containerd
    Dlist<Line>* queue = new Dlist<Line>[4];

    // initilize line nums
    int line_total;
    // int done(0);
    cin >> line_total;
    Line* list = new Line[line_total];

    for (int i = 0; i < line_total; i++) {
        //input
        string tmp = "";
        cin >> list[i].timestamp >> list[i].name >> tmp >> list[i].duration;
        list[i].status = convert_membership(tmp);
        queue[convert_membership(tmp)].insertBack(&list[i]);
        // cout << list[i].timestamp<<endl;
        //test
    }
    int tick = -1;
    int time_end = 0;
    bool queue_empty = queue[0].isEmpty() && queue[1].isEmpty() && queue[2].isEmpty() && queue[3].isEmpty();

    while (!queue_empty || (tick != time_end)) {
        // if (done==line_total) exit(0);
        tick++;
        // if (time_end < tick && queue->isEmpty())
        if (time_end < tick)
            time_end = tick;

        cout << "Starting tick #" << tick << endl;

        for (int i = 0; i < line_total; i++) {
            if (&list[i] != nullptr && list[i].timestamp == tick) {
                cout << "Call from " << list[i].name << " a " << membership[list[i].status] << " member\n";
            }
        }

        //Answer
        // bool busy = (tick < time_end);

        // if (!busy)
        if (time_end == tick && !(queue[0].isEmpty() && queue[1].isEmpty() && queue[2].isEmpty() && queue[3].isEmpty())) {
            // int terminate = 0;
            for (int i = 0; i < 4; i++) {
                // if (!(queue[i].isEmpty()) && tick == time_end)
                // {
                if (!queue[i].isEmpty()) {
                    Line* now = queue[i].removeFront();
                    // if ((tick >= now->timestamp) && (tick <= (now->timestamp + now->duration))) {
                    if ((tick >= now->timestamp)) {
                        cout << "Answering call from " << now->name << endl;
                        // done++;
                        // if (done==line_total) exit(0);
                        time_end = tick + now->duration;
                        // tick++;
                        // delete now;
                        break;
                        // continue;
                    } else {
                        queue[i].insertFront(now);
                    }
                }
                // else {
                //     queue[i].insertFront(now);
                // }
                // }
                // else
                // {
                //     terminate++;
                // }
                //     if (terminate == 4) break;
                //     }
            }
            // if (done==line_total) exit(0);
            // tick++;
            queue_empty = queue[1].isEmpty() && queue[2].isEmpty() && queue[3].isEmpty() && queue[0].isEmpty();
        }
    }
    delete[] list;
    delete[] queue;
    return 0;
}
