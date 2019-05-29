#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <pthread.h>

using namespace std;

int generateItem(int){

    return rand() % 100;

}

char generateItem(char){

    return (char)(rand() % 26 + 97);

}

string generateItem(const string &){

    string s;

    for (int i = 0; i < rand() % 10 + 1; i++)
        s += generateItem('a');

    return s;
}

template <class T>
void generate (T * arr, int n){

    srand(time(nullptr));

    for (int i = 0; i < n; i++)
        arr[i] = generateItem(*arr);

}

template <class T>
void print (T * arr, int n){

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;

}