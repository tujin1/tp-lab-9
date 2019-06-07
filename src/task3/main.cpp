#include <queue>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

mutex g;

struct CUSTOMER{
    int id;
    int time;
};

template <int maxLen = 5>
class Queue{

public:
    queue<CUSTOMER> * q;
    int id;
    thread * th = nullptr;

    Queue(){
        static int ID = 0;
        q = new queue<CUSTOMER>();
        id = ++ID;
    }

    bool add(CUSTOMER& customer){

        if (q->size() == maxLen)
            return false;

        q->push(customer);

        if (q->size() == 1)
            serve();

        return true;

    }

    void run(){

        while (!q->empty()){
            g.lock();
            cout << id << " start serve: " << q->front().id << endl;
            g.unlock();
            usleep(q->front().time);
            g.lock();
            cout << id << " end serve: " << q->front().id << endl;
            g.unlock();
            q->pop();
        }

    }

    void serve(){
        if (th != nullptr)
            th->join();
        th = new thread(&Queue::run, this);
    }

};

vector<Queue<5>> queues;
int id = 1;

CUSTOMER& createCustomer(){
    auto * customer = new CUSTOMER{id++, rand() % 2000};
    return *customer;
}

void findQueueFor(CUSTOMER& customer){

    for (auto &q : queues)
        if (q.add(customer))
            return;

    auto newQueue = new Queue<5>();
    newQueue->add(customer);
    queues.push_back(*newQueue);

}

int main(){

    srand(time(nullptr));

    int n = 40;

    for (int i = 0; i < n; i++){
        auto customer = createCustomer();
        findQueueFor(customer);
    }

    for (auto &q : queues)
        q.th->join();

    return 0;

}