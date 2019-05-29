#include "task2.h"
#include "../common.h"

int main(){

    int n = 10;

    int * arr1 = new int[n];

    generate(arr1, n);

    auto comp = [] (int a, int b) -> bool {return a < b;};
    thread sorting(mySort<int, decltype(comp)>, arr1, arr1 + n, comp);

    while (sorting.joinable()) {

        while(!mu.try_lock());

        print(arr1, n);

        l = 0;

        mu.unlock();

        int counter = 100000;
        while (l == 0 && --counter != 0);

        if (counter <= 0)
            break;

    }

    sorting.join();

    return 0;

}
