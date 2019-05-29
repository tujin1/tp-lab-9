#include "task1.h"
#include "../common.h"

int main(){

    int n = 20;

    int * arr1 = new int[n];
    char * arr2 = new char[n];
    auto * arr3 = new string[n];

    generate(arr1, n);
    generate(arr2, n);
    generate(arr3, n);

    // по возрастанию

    mySort(arr1, arr1 + n, [] (int a, int b) -> bool {return a < b;});
    mySort(arr2, arr2 + n, [] (char a, char b) -> bool {return a < b;});
    mySort(arr3, arr3 + n, [] (string a, string b) -> bool {return a < b;});

    print(arr1, n);
    print(arr2, n);
    print(arr3, n);

    // по убыванию

    mySort(arr1, arr1 + n, [] (int a, int b) -> bool {return a > b;});
    mySort(arr2, arr2 + n, [] (char a, char b) -> bool {return a > b;});
    mySort(arr3, arr3 + n, [] (string a, string b) -> bool {return a > b;});

    print(arr1, n);
    print(arr2, n);
    print(arr3, n);

    return 0;

}
