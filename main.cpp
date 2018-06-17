#include <iostream>
#include "my_set.h"
int main() {
    my_set<int> a, b;
    a.insert(-1);
    b.insert(1);
    swap(a, b);
    for (auto v = a.begin(); v!= a.end(); v++) {
        std::cout << (*v) << std::endl;
    }
    /*
    for (int i = 0; i < 10; i++) {
        a.insert(i);
        my_set<int> b = a;
        //swap(a, b);
        if (i % 2) a.clear();
        /*if (i % 2) {
            a.erase(a.find(i));
        }*/
        /*for (auto v = a.begin(); v != a.end(); v++)
            std::cout << (*v) << " ";
        std::cout << "\n";*/
        /*for (auto v = b.begin(); v != b.end(); v++) {
            std::cout << (*v) << " ";
        }
        std::cout << "\n";
    }*/
    return 0;
}