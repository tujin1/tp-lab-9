#include <algorithm>

template <class T, class lambda>
void mySort(T * begin, T * end, lambda comparator){

    auto i = begin;

    while (i != end){

        auto cur = begin, prev = begin;

        while (++cur != end) {

            if (comparator(*cur, *prev))
                std::swap(*prev, *cur);

            prev = cur;

        }

        i++;

    }

}