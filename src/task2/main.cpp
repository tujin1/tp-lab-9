#include "task2.h"
#include "../common.h"

int main(){

    int n = 10;

    int * arr1 = new int[n];

    generate(arr1, n);

    auto comp = [] (int a, int b) -> bool {return a < b;};
    thread sorting(mySort<int, decltype(comp)>, arr1, arr1 + n, comp);

    while (l != 2 && sorting.joinable()) {

        while(!mu.try_lock());

        print(arr1, n);

        l = (l == 2 ? 2 : 0);

        mu.unlock();

        while (l == 0);

    }

    sorting.join();

    return 0;

}
