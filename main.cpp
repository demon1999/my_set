#include <iostream>
#include "my_set.h"
int main() {
    my_set<int> a, b;
    a.insert(-1);
    b.insert(-2);
    swap(a, b);
    for (auto v = a.begin(); v!= a.end(); v++) {
        std::cout << (*v) << std::endl;
    }
    for (int i = 0; i < 10; i++) {
        a.insert(i);
        //b.insert(i  *10 + 10);
        //if (i % 2) a.clear();
        swap(a, b);
        for (auto v = b.begin(); v != b.end(); v++) {
            std::cout << (*v) << " ";
        }
        std::cout << "\n";
        for (auto v = a.begin(); v != a.end(); v++) {
            std::cout << (*v) << " ";
        }
        std::cout << "\n";
    }
    return 0;
}