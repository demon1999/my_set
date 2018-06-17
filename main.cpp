#include <iostream>
#include "my_set.h"
int main() {
    my_set<int> a;
    auto qq = a.insert(-1).first;
    for (int i = 0; i < 10; i++) {
        a.insert(i);
        my_set<int> b = a;
        if (i % 2) {
            a.erase(a.find(i));
        }
        /*for (auto v = a.begin(); v != a.end(); v++)
            std::cout << (*v) << " ";
        std::cout << "\n";*/
        for (auto v = b.begin(); v != b.end(); v++) {
            std::cout << (*v) << " ";
        }
        std::cout << "\n";
        for (auto v = qq; v != a.end(); v++)
            std::cout << (*v) << " ";
        std::cout << "\n";
    }
    return 0;
}