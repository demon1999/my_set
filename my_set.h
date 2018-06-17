//
// Created by demon1999 on 17.06.18.
//

#ifndef MY_SET_MY_SET_H
#define MY_SET_MY_SET_H


#include <cstdio>
#include <stdexcept>
#include <queue>

template <typename T>
struct my_set {
private:
    struct node {
        node* l;
        node* r;
        node* par;
        T* data;
        bool is_end, is_beg;
        node() {
            is_beg = is_end = false;
            data = NULL;
            l = r = par = NULL;
        }
        node(const T& a) {
            data = new T(a);
            l = r = par = NULL;
            is_beg = is_end = false;
        }
        ~node() {
            if (data != NULL)
                delete data;
        }
        node* prev_node() {
            node* we = this;
            if (we->l != NULL) {
                we = we->l;
                while (we->r != NULL)
                    we = we->r;
            } else {
                node* prev = we;
                we = we->par;
                while (we != NULL && (we->l) == prev) {
                    prev = we;
                    we = we->par;
                }
            }
            return we;
        };

        node* next_node() {
            node* we = this;
            if (we->r != NULL) {
                we = we->r;
                while (we->l != NULL)
                    we = we->l;
            } else {
                node* prev = we;
                we = we->par;
                while (we != NULL && (we->r) == prev) {
                    prev = we;
                    we = we->par;
                }
            }
            return we;
        }
    };
public:
    struct const_iterator;
    struct iterator : public std::iterator<
            std::bidirectional_iterator_tag,   // iterator_category
            T,                      // value_type
            long,                      // difference_type
            T*,               // pointer
            T&                       // reference
    > {
    private:
        node* we;
        iterator(node *a) {
            we = a;
        }
    public:
        iterator(const const_iterator & other) {
            we = other.we;
        }
        bool operator==(const iterator & other) {
            return we == other.we;
        }
        bool operator==(const const_iterator & other) {
            return const_iterator(we) == other.we;
        }
        bool operator==(const iterator & other) const {
            return we == other.we;
        }
        bool operator==(const const_iterator & other) const {
            return const_iterator(we) == other.we;
        }
        bool operator!=(const const_iterator & other) {
            return const_iterator(we) == other.we;
        }
        bool operator!=(const iterator & other) {
            return we != other.we;
        }
        bool operator!=(const const_iterator & other) const {
            return const_iterator(we) == other.we;
        }
        bool operator!=(const iterator & other) const {
            return we != other.we;
        }
        T& operator*() {
            return *(we->data);
        }
        T* operator->() {
            return we->data;
        }
        iterator &operator++() {
            we = we->next_node();
            return *this;
        }
        iterator operator++(int) {
            iterator a = we;
            ++(*this);
            return a;
        }
        iterator &operator--() {
            we = we->prev_node();
            return *this;
        }
        iterator operator--(int) {
            iterator a = we;
            --(*this);
            return a;
        }
        friend struct my_set<T>;
        friend struct const_iterator;
    };

    struct const_iterator : public std::iterator<
            std::bidirectional_iterator_tag,   // iterator_category
            T,                      // value_type
            long,                      // difference_type
            const T*,               // pointer
            const T&                       // reference
    >{
    private:
        node* we;
        const_iterator(node *a) {
            we = a;
        }
    public:
        const_iterator(const iterator & other) {
            we = other.we;
        }
        bool operator==(const const_iterator & other) {
            return we == other.we;
        }
        bool operator==(const const_iterator & other) const {
            return we == other.we;
        }
        bool operator!=(const const_iterator & other) {
            return we != other.we;
        }
        bool operator!=(const const_iterator & other) const{
            return we != other.we;
        }
        const T& operator*() {
            return *(we->data);
        }
        const T* operator->() {
            return we->data;
        }

        const_iterator &operator--() {
            we = we->prev_node();
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator a = we;
            --(*this);
            return a;
        }

        const_iterator &operator++() {
            we = we->next_node();
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator a = we;
            ++(*this);
            return a;
        }
        friend struct my_set<T>;
        friend struct iterator;
    };

    iterator begin() {
        return ++iterator(&start);
    }
    iterator end() {
        return &finish;
    }

    const_iterator begin() const {
        return ++const_iterator(&start);
    }

    const_iterator end() const {
        return (const_iterator(&finish)--)++;
    }

    const_iterator cbegin() {
        return ++const_iterator(&start);
    }

    const_iterator cend() {
        return &finish;
    }

    const_iterator cbegin() const {
        return ++const_iterator(&start);
    }

    const_iterator cend() const {
        return ++(--const_iterator(&finish));
    }

    struct const_reverse_iterator;
    struct reverse_iterator : public std::iterator<
            std::bidirectional_iterator_tag,   // iterator_category
            T,                      // value_type
            long,                      // difference_type
            T*,               // pointer
            T&                       // reference
    > {
    private:
        node* we;
        reverse_iterator(node *a) {
            we = a;
        }
    public:
        reverse_iterator(const const_reverse_iterator & other) {
            we = other.we;
        }
        bool operator==(const reverse_iterator & other) {
            return we == other.we;
        }
        bool operator==(const const_reverse_iterator & other) {
            return const_reverse_iterator(we) == other.we;
        }
        bool operator==(const reverse_iterator & other) const {
            return we == other.we;
        }
        bool operator==(const const_reverse_iterator & other) const {
            return const_reverse_iterator(we) == other.we;
        }
        bool operator!=(const const_iterator & other) {
            return const_reverse_iterator(we) == other.we;
        }
        bool operator!=(const reverse_iterator & other) {
            return we != other.we;
        }
        bool operator!=(const const_reverse_iterator & other) const {
            return const_reverse_iterator(we) == other.we;
        }
        bool operator!=(const reverse_iterator & other) const {
            return we != other.we;
        }
        T& operator*() {
            return *(we->data);
        }
        T* operator->() {
            return we->data;
        }
        reverse_iterator &operator++() {
            we = we->prev_node();
            return *this;
        }
        reverse_iterator operator++(int) {
            reverse_iterator a = we;
            ++(*this);
            return a;
        }
        reverse_iterator &operator--() {
            we = we->next_node();
            return *this;
        }
        reverse_iterator operator--(int) {
            reverse_iterator a = we;
            --(*this);
            return a;
        }
        friend struct my_set<T>;
        friend struct const_reverse_iterator;
    };

    struct const_reverse_iterator : public std::iterator<
            std::bidirectional_iterator_tag,   // iterator_category
            T,                      // value_type
            long,                      // difference_type
            const T*,               // pointer
            const T&                       // reference
    >{
    private:
        node* we;
        const_reverse_iterator(node *a) {
            we = a;
        }
    public:
        const_reverse_iterator(const reverse_iterator & other) {
            we = other.we;
        }
        bool operator==(const const_reverse_iterator & other) {
            return we == other.we;
        }
        bool operator==(const const_reverse_iterator & other) const {
            return we == other.we;
        }
        bool operator!=(const const_reverse_iterator & other) {
            return we != other.we;
        }
        bool operator!=(const const_reverse_iterator & other) const{
            return we != other.we;
        }
        const T& operator*() {
            return *(we->data);
        }
        const T* operator->() {
            return we->data;
        }

        const_reverse_iterator &operator--() {
            we = we->next_node();
            return *this;
        }

        const_reverse_iterator operator--(int) {
            const_reverse_iterator a = we;
            --(*this);
            return a;
        }

        const_reverse_iterator &operator++() {
            we = we->prev_node();
            return *this;
        }

        const_reverse_iterator operator++(int) {
            const_reverse_iterator a = we;
            ++(*this);
            return a;

        }
        friend struct my_set<T>;
        friend struct reverse_iterator;
    };
    reverse_iterator rbegin() {
        return --reverse_iterator(&finish);
    }
    reverse_iterator rend() {
        return &start;
    }

    const_reverse_iterator rbegin() const {
        return --const_reverse_iterator(&finish);
    }

    const_reverse_iterator rend() const {
        return --(++const_reverse_iterator(&start));
    }

    const_reverse_iterator crbegin() {
        return --const_reverse_iterator(&finish);
    }

    const_reverse_iterator crend() {
        return &start;
    }

    const_reverse_iterator crbegin() const {
        return --const_reverse_iterator(&finish);
    }

    const_reverse_iterator crend() const {
        return --(++const_reverse_iterator(&start));
    }

    const_iterator find(T const& a);
    const_iterator lower_bound(T const& a);
    const_iterator upper_bound(T const& a);
    void swap(my_set & a) {
        std::swap(start, a.start);
        std::swap(finish, a.finish);
    }

    void clear();
    iterator erase(const_iterator we);
    iterator extract(const_iterator we);
    std::pair<iterator, bool> insert(T const& a);
    bool is_empty() const;
    my_set();
    my_set(my_set const &other);
    ~my_set();
    my_set& operator=(my_set const &other);
private:
    node start, finish;
};

template<typename T>
my_set<T>::my_set() {
    finish.l = &start;
    finish.is_end = true;
    start.is_beg = true;
    start.par = &finish;
}

template<typename T>
my_set<T>::my_set(my_set const &other) {
    finish.l = &start;
    finish.is_end = true;
    start.is_beg = true;
    start.par = &finish;
    std::queue<std::pair<node*, node*> > data;
    data.push({&start, &(other.start)});
    while (!data.empty()) {
        auto v = data.front();
        data.pop();
        if (((v.second)->l) != NULL) {
            node* lch = (v.second)->l;
            node* nw = new node(lch->data);
            v.first->l = nw;
            nw->par = v.first;
            data.push({nw, lch});
        }
        if (((v.second)->r) != NULL) {
            node* rch = (v.second)->r;
            node* nw = new node(rch->data);
            v.first->r = nw;
            nw->par = v.first;
            data.push({nw, rch});
        }
    }
}

template<typename T>
my_set<T>::~my_set() {
    clear();
}

template<typename T>
my_set<T> &my_set<T>::operator=(my_set const &other) {
    if (this != &other) {
        my_set<T>(other).swap(*this);
    }
    return *this;
}

template<typename T>
void my_set<T>::clear() {
    std::queue<node*> data;
    data.push(start.r);
    while (!data.empty()) {
        auto v = data.front();
        data.pop();
        if (v != NULL) {
            data.push(v->l);
            data.push(v->r);
            delete v;
        }
    }
}

template<typename T>
bool my_set<T>::is_empty() const {
    return start.r != NULL;
}

template<typename T>
typename my_set<T>::const_iterator my_set<T>::find(const T &a) {
    node* go = start.r;
    while (go != NULL) {
        if ((go->data) != NULL && (*(go->data)) == a) {
            return const_iterator(go);
        }
        if ((go->data) != NULL && (*(go->data)) > a)
            go = go->l;
        else
            go = go->r;
    }
    return const_iterator(&finish);
}

template<typename T>
typename my_set<T>::const_iterator my_set<T>::upper_bound(const T &a) {
    if (start.r == NULL)
        return const_iterator(&finish);
    node* go = start.r;
    while (go != NULL) {
        if ((go->data) != NULL && (*(go->data)) > a) {
            if ((go->l) == NULL) {
                break;
            }
            go = go->l;
        }
        else {
            if ((go->r) == NULL) {
                break;
            }
            go = go->r;
        }
    }
    const_iterator we = go;
    if ((go->data) != NULL && (*(go->data)) <= a)
        we++;
    return we;
}

template<typename T>
typename my_set<T>::const_iterator my_set<T>::lower_bound(const T &a) {
    if ((find(a)) != &finish) {
        return find(a);
    } else
        return upper_bound(a);
}

template<typename T>
std::pair<typename my_set<T>::iterator, bool> my_set<T>::insert(const T &a) {
    const_iterator we = lower_bound(a);
    if (we != (&finish)) {
        if ((*we) == a) {
            return {we, false};
        } else {
            auto nw = new node(a);
            nw->par = (we.we);
            nw->l = (we.we->l);
            if ((nw->l) != NULL) {
                (nw->l)->par = nw;
            }
            we.we->l = nw;
            return {nw, true};
        }
    } else {
        auto nw = new node(a);
        we--;
        we.we->r = nw;
        nw->par = we.we;
        return {nw, true};
    }
}

template<typename T>
typename my_set<T>::iterator my_set<T>::erase(my_set::const_iterator we) {
    if (we == (&finish))
        return we;
    auto me = extract(we);
    auto ans = upper_bound(me->data);
    delete me;
    return ans;
}

template<typename T>
typename my_set<T>::iterator my_set<T>::extract(my_set::const_iterator we) {
    if (we == (&finish)) {
        return we;
    }
    auto ans = we;
    ans++;
    if (we->r == NULL) {
        auto nw = we->par;
        if ((nw->l) == we)
            nw->l = we->l;
        else
            nw->r = we->l;
        if (we->l != NULL) {
            ((we->l)->par) = nw;
        }
    } else if (we->l == NULL) {
        auto nw = we->par;
        if ((nw->l) == we)
            nw->l = we->r;
        else
            nw->r = we->r;
        ((we->r)->par) = nw;
    } else {
        auto nk = extract(ans);
        nk->par = we->par;
        if (((we->par)->l) == we){
            ((we->par)->l) = nk;
        } else
            ((we->par)->r) = nk;
        nk->l = (we->l);
        nk->r = (we->r);
    }
    return we;
}


template<typename T>
void swap(my_set<T>& a, my_set<T>& b) {
    a.swap(b);
}
#endif //MY_SET_MY_SET_H
