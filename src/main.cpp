#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

void Buble_sort(vector<string> &vec, function<bool(string, string)> f)
{
    int vec_size = vec.size();
    string tmp;
    bool swapped = false;
    for (int i = 0; i < vec_size; i++)
    {
        for (int j = 0; j < (vec_size-i-1); j++)
        {
            if (f(vec[j], vec[j+1]))
            {
                tmp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = tmp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

int main()
{
    vector<string> v = {"January","February","March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    for_each(v.begin(), v.end(), [](string s) {cout<<s<<endl;} );
    //По размеру сдлва
    Buble_sort(v,
               [](string a, string b) {return (a.size()<b.size());} );
    //Алфавитный порядок по первой букве
    Buble_sort(v,
               [](string a, string b) {return ((int)a[0]>(int)b[0]);} );
    //Сначала четные
    Buble_sort(v,
               [](string a, string b) {return (b.size()%2==0 &&
                                               a.size()%2!=0);} );
}
