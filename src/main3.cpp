#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "stdlib.h"
#include "time.h"
#include <windows.h>
using namespace std;
using namespace chrono;

const int MAXDELAY = 4;
const int MAXBASKET = 8; //+1

struct Till
{
    queue<int>* que;
    thread* tr;
};
vector<Till> shops;
mutex mx;

void worker(queue<int>* pr)
{
    while(true)
    {
        if (!pr->empty())
        {
            int basket = pr->front();
            for (int i = 0; i<basket; i++)
            {
                this_thread::sleep_for(seconds(1));
            }

            lock_guard<mutex> lock(mx);
            pr->pop();
            if (pr->empty()) return;
        }
        else
        {
            return;
        }
    }
}

int main()
{
    srand(time(NULL));
    while(true)
    {
        int delay = rand()%MAXDELAY + 1;
        this_thread::sleep_until(system_clock::now() + seconds(delay));

        auto End = remove_if(shops.begin(), shops.end(), [](Till obj){  if (obj.que->size()==0)
                                                                        {
                                                                            delete obj.que;
                                                                            delete obj.tr;
                                                                            return true;
                                                                        }
                                                                        return false;}            );
        shops.erase(End, shops.end());


        int basket_size = rand()%MAXBASKET + 3;
        bool added = false;
        for (auto obj = shops.rbegin(); obj != shops.rend(); ++obj)
        {
            if (obj->que->size() < 5)
            {
                lock_guard<mutex> lock(mx);
                obj->que->push(basket_size);
                added = true;
                break;
            }
        }
        if (!added)
        {
            lock_guard<mutex> lock(mx);
            Till nT;
            nT.que = new queue<int>;
            nT.que->push(basket_size);
            nT.tr = new thread (worker, nT.que);
            nT.tr->detach();
            shops.push_back(nT);
        }
        {
        lock_guard<mutex> lock(mx);
        for (auto obj : shops)
        {
            cout<<obj.que->size()<<"  id:"<<oendl;
        }
        cout<<"_________________"<<endl<<endl;
        }
    }
}
