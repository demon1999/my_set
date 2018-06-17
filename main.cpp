#include <iostream>
#include "my_set.h"
int main() {
    my_set<int> a;
    for (int i = 0; i < 10; i++) {
        a.insert(i);
    }
    return 0;
}