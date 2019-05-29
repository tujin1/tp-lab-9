#include <algorithm>
#include <mutex>
#include <thread>

std::mutex mu;
int l = 0;

template <class T, class lambda>
void mySort(T * begin, T * end, lambda comparator){

    auto i = begin;

    while (i != end){

        while(!mu.try_lock());

        auto cur = begin, prev = begin;

        while (++cur != end) {

            if (comparator(*cur, *prev))
                std::swap(*prev, *cur);

            prev = cur;

        }

        i++;

        l = 1;

        mu.unlock();

        while (l == 1);

    }

}