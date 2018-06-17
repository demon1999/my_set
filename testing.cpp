//
// Created by Andrew Berlin on 5/7/18.
//

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <string>
#include <utility>
#include <gtest/gtest.h>
#include <iterator>

#include "my_set.h"

template<typename C, typename T>
void mass_push_back(C &c, std::initializer_list<T> elems) {
    for (T const &e : elems)
        c.insert(e);
}

template<typename It, typename T>
void expect_eq(It i1, It e1, std::initializer_list<T> elems) {
    auto i2 = elems.begin(), e2 = elems.end();

    for (;;) {
        if (i1 == e1 || i2 == e2) {
            EXPECT_TRUE(i1 == e1 && i2 == e2);
            break;
        }

        EXPECT_EQ(*i2, *i1);
        ++i1;
        ++i2;
    }
}

template<typename C, typename T>
void expect_eq(C const &c, std::initializer_list<T> elems) {
    expect_eq(c.begin(), c.end(), elems);
}

template<typename C, typename T>
void expect_reverse_eq(C const &c, std::initializer_list<T> elems) {
    expect_eq(c.rbegin(), c.rend(), elems);
}

TEST(correctness, simple_order) {
    my_set<int> s;
    std::vector<int> res = {10, 3, 1};
    s.insert(3);
    s.insert(10);
    s.insert(1);
    for (auto x : s) {
        EXPECT_EQ(res.back(), x);
        res.pop_back();
    }
}

TEST(iterators, rbegin_inc) {
    my_set<int> s;
    s.insert(5);
    s.insert(3);
    s.insert(4);
    s.insert(11);
    s.insert(8);
    auto it = s.rbegin();
    EXPECT_EQ(11, *it);
    it++;
    EXPECT_EQ(8, *it);
}

TEST(correctness, erase_end) {
    my_set<int> l;
    auto i = l.end();
    l.insert(42);
    --i;
    EXPECT_EQ(42, *i);
}

TEST(correctness, empty) {
    my_set<int> s;
    ASSERT_TRUE(s.empty());
}

TEST(correctness, 3_4_5) {
    my_set<int> a;
    std::set<int> b;
    a.insert(5);
    a.insert(3);
    a.insert(4);
    b.insert({5});
    b.insert({3});
    b.insert({4});

    auto a_it = a.begin();
    auto b_it = b.begin();
    for (; a_it != a.end() && b_it != b.end(); ++a_it, ++b_it) {
        EXPECT_EQ(*b_it, *a_it);
    }
}

TEST(correctness, reverse_iterator_rbeg_to_rend) {
    my_set<int> a;
    std::set<int> b;
    a.insert(5);
    a.insert(3);
    a.insert(4);
    a.insert(11);
    a.insert(8);
    a.insert(20);
    b.insert(5);
    b.insert(3);
    b.insert(4);
    b.insert(11);
    b.insert(8);
    b.insert(20);
    auto a_it = a.rbegin();
    auto b_it = b.rbegin();

    for (; a_it != a.rend() && b_it != b.rend(); ++a_it, ++b_it) {
//        std::cerr << (*a_it) << std::endl;
        ASSERT_EQ(*a_it, *b_it);
    }
}

TEST(correctness, reverse_iterator_rend_to_rbeg) {
    my_set<int> a;
    std::set<int> b;
    a.insert(5);
    a.insert(3);
    a.insert(4);
    a.insert(11);
    a.insert(8);
    a.insert(20);
    b.insert(5);
    b.insert(3);
    b.insert(4);
    b.insert(11);
    b.insert(8);
    b.insert(20);
    auto a_it = a.rend();
    auto b_it = b.rend();
    --a_it;
    --b_it;
    for (; a_it != a.rbegin() && b_it != b.rbegin(); --a_it, --b_it) {
        ASSERT_EQ(*a_it, *b_it);
    }
}

TEST(correctness, iter_down) {
    my_set<int> a;
    std::set<int> b;
    a.insert(5);
    a.insert(3);
    a.insert(4);
    a.insert(11);
    a.insert(8);
    a.insert(20);
    b.insert(5);
    b.insert(3);
    b.insert(4);
    b.insert(11);
    b.insert(8);
    b.insert(20);

    auto a_it = a.end();
    auto b_it = b.end();

    do {
        --a_it;
        --b_it;
        ASSERT_EQ(*a_it, *b_it);
    } while (a_it != a.begin() || b_it != b.begin());
}

TEST(correctness, find) {
    my_set<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(4);

    ASSERT_EQ(a.find(6), a.end());
    ASSERT_EQ(a.find(-120), a.end());
    ASSERT_EQ(*a.find(5), 5);
    ASSERT_EQ(*a.find(3), 3);
    ASSERT_EQ(*a.find(4), 4);
}

TEST(correctness, erase) {
    my_set<int> a;
    a.insert(5);
    a.insert(3);
    a.insert(4);
    a.insert(10);
    a.insert(20);
    a.insert(30);

    ASSERT_EQ(*a.erase(a.find(10)), 20);
    ASSERT_EQ(*a.erase(a.find(20)), 30);
    ASSERT_EQ(a.erase(a.find(30)), a.end());
    ASSERT_EQ(*a.erase(a.find(3)), 4);
    ASSERT_EQ(a.find(3), a.end());
    ASSERT_EQ(*a.erase(a.find(4)), 5);
    ASSERT_EQ(a.find(4), a.end());
    ASSERT_EQ(a.erase(a.find(5)), a.end());
    ASSERT_EQ(a.find(5), a.end());
}

TEST(correctness, random) {
    std::set<int> a;
    my_set<int> b;

    for (int i = 0, j = 100; i < 100; i++, j--) {
        a.insert(i);
        a.insert(j);
        b.insert(i);
        b.insert(j);
    }
    for (int i = 0; i < 10; i++) {
        int pos = rand() % a.size();
        auto it = a.begin();
        for (int j = 0; j < pos; j++) {
            ++it;
        }
        int x = *it;
        ASSERT_EQ(*(a.find(x)), *(b.find(x)));
        //cout<<x<<"|";
        a.erase(a.find(x));
        b.erase(b.find(x));
    }
    auto a_it = a.begin();
    auto b_it = b.begin();
    for (; a_it != a.end() && b_it != b.end(); ++a_it, ++b_it) {
        //     std::cout<<*a_it<<" ";
        ASSERT_EQ(*a_it, *b_it);
    }
    // std::cout<<endl;
}

TEST(iterators, const_iterator) {
    my_set<int> x;

    x.insert(5);
    x.insert(3);
    x.insert(4);
    x.insert(10);
    x.insert(20);
    x.insert(30);

    my_set<int>::const_iterator it(x.begin());
    ASSERT_EQ(*it, 3);
    it++;
    ASSERT_EQ(*it, 4);
}

TEST(iterators, const_iterator_cast) {
    my_set<int> x;

    x.insert(5);
    x.insert(3);
    x.insert(4);
    x.insert(10);
    x.insert(20);
    x.insert(30);

    my_set<int>::iterator z(x.begin());
    my_set<int>::const_iterator n(z);
}
TEST(iterators, const_iterator_equality) {
    my_set<int> x;

    x.insert(5);
    x.insert(3);
    x.insert(4);
    x.insert(10);
    x.insert(20);
    x.insert(30);

    my_set<int>::iterator i(x.begin());
    my_set<int>::const_iterator j(x.begin());
    EXPECT_TRUE(i == j && j == i);
    EXPECT_FALSE(++i == j || j == ++i);
}

TEST(swaps, swap_empty) {
    my_set<int> x;
    my_set<int> y;
    x.insert(2);
    swap(x, y);
    EXPECT_FALSE(y.empty());
    swap(x, y);
    EXPECT_FALSE(x.empty());
}

TEST(correctness, swap) {
    my_set<int> c1, c2;
    mass_push_back(c1, {1, 2, 3, 4});
    mass_push_back(c2, {5, 6, 7, 8});
    swap(c1, c2);
    expect_eq(c1, {5, 6, 7, 8});
    expect_eq(c2, {1, 2, 3, 4});
}

TEST(correctness, swap_self) {
    my_set<int> c1;
    mass_push_back(c1, {1, 2, 3, 4});
    swap(c1, c1);
}

TEST(correctness, swap_empty1) {
    my_set<int> c1, c2;
    mass_push_back(c1, {1, 2, 3, 4});
    swap(c1, c2);
    EXPECT_TRUE(c1.empty());
    expect_eq(c2, {1, 2, 3, 4});
    swap(c1, c2);
    expect_eq(c1, {1, 2, 3, 4});
    EXPECT_TRUE(c2.empty());
}

TEST(correctness, swap_empty_empty) {
    my_set<int> c1, c2;
    swap(c1, c2);
}

TEST(correctness, swap_empty_self) {
    my_set<int> c1;
    swap(c1, c1);
}

TEST(correctness, clear_empty) {
    my_set<int> c;
    c.clear();
    EXPECT_TRUE(c.empty());
    c.clear();
    EXPECT_TRUE(c.empty());
    c.clear();
    EXPECT_TRUE(c.empty());
}

TEST(correctness, clear) {
    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 4});
    c.clear();
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(c.begin(), c.end());
    mass_push_back(c, {5, 6, 7, 8});
    expect_eq(c, {5, 6, 7, 8});
}

TEST(correctness, erase_begin) {
    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(c.begin());
    expect_eq(c, {2, 3, 4});
}

TEST(correctness, erase_middle) {
    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(std::next(c.begin(), 2));
    expect_eq(c, {1, 2, 4});
}

TEST(correctness, erase_end_s) {
    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(std::prev(c.end()));
    expect_eq(c, {1, 2, 3});
}

TEST(correctness, erase_iterators) {
    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 4});

    my_set<int>::iterator i2 = c.begin();
    ++i2;
    my_set<int>::iterator i3 = i2;
    ++i3;
    my_set<int>::iterator i4 = i3;
    ++i4;

    c.erase(i3);
    --i4;
    ++i2;
    EXPECT_EQ(2, *i4);
    EXPECT_EQ(4, *i2);
}

TEST(correctness, insert_begin) {

    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 4});
    c.insert(0);
    expect_eq(c, {0, 1, 2, 3, 4});
}

TEST(correctness, lower_bound_end) {
    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 10});
    EXPECT_EQ(c.lower_bound(11), c.end());
}

TEST(correctness, upper_bound_end) {
    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 10});
    EXPECT_EQ(c.upper_bound(10), c.end());
}

TEST(correctness, lower_bound_empty) {
    my_set<int> c;
    EXPECT_EQ(c.lower_bound(11), c.end());
}

TEST(correctness, upper_bound_empty) {
    my_set<int> c;
    EXPECT_EQ(c.upper_bound(10), c.end());
}

TEST(correctness, lower_bound) {
    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 10});
    EXPECT_EQ(c.lower_bound(10), (--c.end()));
}

TEST(correctness, upper_bound) {
    my_set<int> c;
    mass_push_back(c, {1, 2, 3, 10});
    EXPECT_EQ(c.upper_bound(3), (--c.end()));
}

template <typename T>
T const& as_const(T& obj)
{
    return obj;
}

TEST(correctness, iterator_conversions)
{
    my_set<int> c;
    my_set<int>::const_iterator i1 = c.begin();
    my_set<int>::iterator i2 = c.end();
    EXPECT_TRUE(i1 == i1);
    EXPECT_TRUE(i1 == i2);
    EXPECT_TRUE(i2 == i1);
    EXPECT_TRUE(i2 == i2);
    EXPECT_FALSE(i1 != i1);
    EXPECT_FALSE(i1 != i2);
    EXPECT_FALSE(i2 != i1);
    EXPECT_FALSE(i2 != i2);

    EXPECT_TRUE(as_const(i1) == i1);
    EXPECT_TRUE(as_const(i1) == i2);
    EXPECT_TRUE(as_const(i2) == i1);
    EXPECT_TRUE(as_const(i2) == i2);
    EXPECT_FALSE(as_const(i1) != i1);
    EXPECT_FALSE(as_const(i1) != i2);
    EXPECT_FALSE(as_const(i2) != i1);
    EXPECT_FALSE(as_const(i2) != i2);

    EXPECT_TRUE(i1 == as_const(i1));
    EXPECT_TRUE(i1 == as_const(i2));
    EXPECT_TRUE(i2 == as_const(i1));
    EXPECT_TRUE(i2 == as_const(i2));
    EXPECT_FALSE(i1 != as_const(i1));
    EXPECT_FALSE(i1 != as_const(i2));
    EXPECT_FALSE(i2 != as_const(i1));
    EXPECT_FALSE(i2 != as_const(i2));

    EXPECT_TRUE(as_const(i1) == as_const(i1));
    EXPECT_TRUE(as_const(i1) == as_const(i2));
    EXPECT_TRUE(as_const(i2) == as_const(i1));
    EXPECT_TRUE(as_const(i2) == as_const(i2));
    EXPECT_FALSE(as_const(i1) != as_const(i1));
    EXPECT_FALSE(as_const(i1) != as_const(i2));
    EXPECT_FALSE(as_const(i2) != as_const(i1));
    EXPECT_FALSE(as_const(i2) != as_const(i2));
}

TEST(correctness, iterators_postfix)
{

    my_set<int> s;
    mass_push_back(s, {1, 2, 3});
    my_set<int>::iterator i = s.begin();
    EXPECT_EQ(1, *i);
    my_set<int>::iterator j = i++;
    EXPECT_EQ(2, *i);
    EXPECT_EQ(1, *j);
    j = i++;
    EXPECT_EQ(3, *i);
    EXPECT_EQ(2, *j);
    j = i++;
    EXPECT_EQ(s.end(), i);
    EXPECT_EQ(3, *j);
    j = i--;
    EXPECT_EQ(3, *i);
    EXPECT_EQ(s.end(), j);
}

TEST(correctness, const_iterators_postfix)
{

    my_set<int> s;
    mass_push_back(s, {1, 2, 3});
    my_set<int>::const_iterator i = s.begin();
    EXPECT_EQ(1, *i);
    my_set<int>::const_iterator j = i++;
    EXPECT_EQ(2, *i);
    EXPECT_EQ(1, *j);
    j = i++;
    EXPECT_EQ(3, *i);
    EXPECT_EQ(2, *j);
    j = i++;
    EXPECT_TRUE(i == s.end());
    EXPECT_EQ(3, *j);
    j = i--;
    EXPECT_EQ(3, *i);
    EXPECT_TRUE(j == s.end());
}

TEST(correctness, erase_root) {
    my_set<int> a, b;
    mass_push_back(a, {5, 3, 8, 1, 2});
    a.erase(a.find(5));
    mass_push_back(b, {3, 8, 1, 2});
    for (auto v = a.begin(); v != a.end(); v++) {
        if (b.find(*v) == b.end()) {
            assert(0);
        }
    }
    for (auto v = b.begin(); v != b.end(); v++) {
        if (a.find(*v) == a.end()) {
            assert(0);
        }
    }
}

TEST(correctness, copy_ctor) {
    my_set<int> a, b;
    mass_push_back(a, {1, 2, 3, 4});
    b = a;
    for (auto v = a.begin(); v != a.end(); v++) {
        if (b.find(*v) == b.end()) {
            assert(0);
        }
    }
    for (auto v = b.begin(); v != b.end(); v++) {
        if (a.find(*v) == a.end()) {
            assert(0);
        }
    }
}