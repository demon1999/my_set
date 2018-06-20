#include <iostream>
#include "my_set.h"

int file(int k) {
    static int p = k;
    return k;
}


int main() {
    static int a;
    int* b = new int(10);
    delete b;
    delete a;
    //my_set<int> a, b;
    //a.insert(5);
    my_set<int>::iterator const i = a.find(5);
    const my_set<int> a;
    a.rbegin();
    //const rbegin() rend()
    /*a.insert(-1);
    auto q = a.begin();
    std::next(q);
    b.insert(-2);
    swap(a, b);
    for (auto v = a.begin(); v!= a.end(); v++) {
        std::cout << (*v) << std::endl;
    }
    auto v = a.find(-2);
    if (v == a.end()) {
        std::cout << "KHEEE\n";
        return 0;
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
    }*/
    return 0;
}