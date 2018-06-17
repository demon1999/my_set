#include <iostream>
#include "my_set.h"
int main() {
    my_set<int> a;
    for (int i = 0; i < 10; i++) {
        a.insert(i);
        for (auto v = a.begin(); v != a.end(); v++)
            std::cout << (*v) << " ";
        std::cout << "\n";
        for (auto v = a.rbegin(); v != a.rend(); v++)
            std::cout << (*v) << " ";
        std::cout << "\n";
    }
    return 0;
}