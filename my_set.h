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
        const T* data;
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
        const node* prev_node() const {
            const node* we = this;
            if (we->l != NULL) {
                we = we->l;
                while (we->r != NULL)
                    we = we->r;
            } else {
                const node* prev = we;
                we = we->par;
                while (we != NULL && (we->l) == prev) {
                    prev = we;
                    if ((we->par) == NULL) return we;
                    we = we->par;
                }
            }
            return we;
        };

        node* prev_node() {
            return const_cast<node*>((const_cast<const node*>(this))->prev_node());
        };
        const node* next_node() const {
            const node* we = this;
            if (we->r != NULL) {
                we = we->r;
                while (we->l != NULL)
                    we = we->l;
            } else {
                const node* prev = we;
                we = we->par;
                while (we != NULL && (we->r) == prev) {
                    prev = we;
                    if ((we->par) == NULL) return we;
                    we = we->par;
                }
            }
            return we;
        }
        node* next_node() {
            return const_cast<node*>((const_cast<const node*>(this))->next_node());
        };
    };

public:
    struct my_const_iterator;
    typedef my_const_iterator const_iterator;
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
        bool operator==(const iterator & other) const {
            return we == other.we;
        }
        bool operator==(const const_iterator & other) const {
            return const_iterator(we) == other.we;
        }
        bool operator!=(const const_iterator & other) const {
            return const_iterator(we) != other.we;
        }
        bool operator!=(const iterator & other) const {
            return we != other.we;
        }
        const T& operator*() const {
            return *(we->data);
        }
        const T* operator->() const {
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
        friend struct my_const_iterator;
    };

    struct my_const_iterator : public std::iterator<
            std::bidirectional_iterator_tag,   // iterator_category
            T,                      // value_type
            long,                      // difference_type
            const T*,               // pointer
            const T&                       // reference
    >{
    private:
        const node* we;
        my_const_iterator(const node *a) {
            we = a;
        }
    public:
        my_const_iterator(const iterator & other) {
            we = other.we;
        }
        bool operator==(const my_const_iterator & other) const {
            return we == other.we;
        }
        bool operator!=(const my_const_iterator & other) const{
            return we != other.we;
        }
        const T& operator*() const {
            return *(we->data);
        }
        const T* operator->() const {
            return we->data;
        }

        my_const_iterator &operator--() {
            we = we->prev_node();
            return *this;
        }

        my_const_iterator operator--(int) {
            my_const_iterator a = we;
            --(*this);
            return a;
        }

        my_const_iterator &operator++() {
            we = we->next_node();
            return *this;
        }

        my_const_iterator operator++(int) {
            my_const_iterator a = we;
            ++(*this);
            return a;
        }
        friend struct my_set<T>;
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
        return &finish;
    }

    const_iterator cbegin() const {
        return ++const_iterator(&start);
    }

    const_iterator cend() const {
        return &finish;
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
        bool operator==(const reverse_iterator & other) const {
            return we == other.we;
        }
        bool operator==(const const_reverse_iterator & other) const {
            return const_reverse_iterator(we) == other.we;
        }
        bool operator!=(const const_reverse_iterator & other) const {
            return const_reverse_iterator(we) != other.we;
        }
        bool operator!=(const reverse_iterator & other) const {
            return we != other.we;
        }
        const T& operator*() const {
            return *(we->data);
        }
        const T* operator->() const {
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
        const node* we;
        const_reverse_iterator(const node *a) {
            we = a;
        }
    public:
        const_reverse_iterator(const reverse_iterator & other) {
            we = other.we;
        }
        bool operator==(const const_reverse_iterator & other) const {
            return we == other.we;
        }
        bool operator!=(const const_reverse_iterator & other) const{
            return we != other.we;
        }
        const T& operator*() const {
            return *(we->data);
        }
        const T* operator->() const {
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
    };
    reverse_iterator rbegin() {
        return ++reverse_iterator(&finish);
    }
    reverse_iterator rend() {
        return &start;
    }

    const_reverse_iterator rbegin() const {
        return ++const_reverse_iterator(&finish);
    }

    const_reverse_iterator rend() const {
        return &start;
    }

    const_reverse_iterator crbegin() const {
        return ++const_reverse_iterator(&finish);
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(&start);
    }

    const_iterator find(T const& a) const;
    iterator find(T const& a);
    const_iterator lower_bound(T const& a) const;
    iterator lower_bound(T const& a);
    const_iterator upper_bound(T const& a) const;
    iterator upper_bound(T const& a);
    void swap(my_set & a) {
        if (this == &a) return;
        node* rr = start.r;
        start.r = a.start.r;
        a.start.r = rr;
        if (start.r != NULL)
            start.r->par = (&start);
        if (a.start.r != NULL)
            a.start.r->par = (&a.start);
    }

    void clear();
    iterator erase(const_iterator we);
private:
    iterator extract(iterator we);
public:
    std::pair<iterator, bool> insert(T const& a);
    bool empty() const;
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
    auto a = my_set<T>();
    a.finish.l = &a.start;
    a.finish.is_end = true;
    a.start.is_beg = true;
    a.start.par = &a.finish;
    std::queue<std::pair<node*, const node*> > data;
    data.push({a.rend().we, &other.start});
    while (!data.empty()) {
        auto v = data.front();
        data.pop();
        if (((v.second)->l) != NULL) {
            node* lch = (v.second)->l;
            node* nw = new node(*(lch->data));
            v.first->l = nw;
            nw->par = v.first;
            data.push({nw, lch});
        }
        if (((v.second)->r) != NULL) {
            node* rch = (v.second)->r;
            node* nw = new node(*(rch->data));
            v.first->r = nw;
            nw->par = v.first;
            data.push({nw, rch});
        }
    }
    a.swap(*this);
}

template<typename T>
my_set<T>::~my_set() {
    clear();
}

template<typename T>
my_set<T> &my_set<T>::operator=(my_set const &other) {
    if (this != &other) {
        my_set<T>(other).swap(*this);
        start.par = &finish;
        finish.l = &start;
    }
    return *this;
}

template<typename T>
void my_set<T>::clear() {
    if (!start.r) return;
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

    start.r = NULL;
}

template<typename T>
bool my_set<T>::empty() const {
    return start.r == NULL;
}

template<typename T>
typename my_set<T>::const_iterator my_set<T>::find(const T &a) const {
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
typename my_set<T>::const_iterator my_set<T>::upper_bound(const T &a) const {
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
typename my_set<T>::const_iterator my_set<T>::lower_bound(const T &a) const {
    if ((find(a)) != &finish) {
        return find(a);
    } else
        return upper_bound(a);
}

template<typename T>
std::pair<typename my_set<T>::iterator, bool> my_set<T>::insert(const T &a) {
    iterator we = lower_bound(a);
    if (we != iterator(&finish)) {
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
    if (we == end())
        return const_cast<node*>(we.we);
    auto me = extract(const_cast<node*>(we.we));
    auto ans = upper_bound((*(me.we->data)));
    delete me.we;
    return const_cast<node*>(ans.we);
}

template<typename T>
typename my_set<T>::iterator my_set<T>::extract(my_set::iterator we) {
    if (iterator(we.we) == end()) {
        return we;
    }
    auto ans = we;
    ans++;
    if (we.we->r == NULL) {
        auto nw = we.we->par;
        if ((nw->l) == we.we)
            nw->l = we.we->l;
        else
            nw->r = we.we->l;
        if (we.we->l != NULL) {
            ((we.we->l)->par) = nw;
        }
    } else if (we.we->l == NULL) {
        auto nw = we.we->par;
        if ((nw->l) == we.we)
            nw->l = we.we->r;
        else
            nw->r = we.we->r;
        ((we.we->r)->par) = nw;
    } else {
        auto nk = extract(ans);
        nk.we->par = we.we->par;
        if (((we.we->par)->l) == we.we){
            ((we.we->par)->l) = nk.we;
        } else
            ((we.we->par)->r) = nk.we;
        nk.we->l = (we.we->l);
        if ((we.we->l) != NULL) {
            ((we.we->l)->par) = nk.we;
        }
        nk.we->r = (we.we->r);
        if ((we.we->r) != NULL) {
            ((we.we->r)->par) = nk.we;
        }
    }
    return we;
}

template<typename T>
typename my_set<T>::iterator my_set<T>::lower_bound(const T &a) {
    return const_cast<node*>(((const_cast<const my_set*>(this))->lower_bound(a)).we);
}

template<typename T>
typename my_set<T>::iterator my_set<T>::upper_bound(const T &a) {
    return const_cast<node*>(((const_cast<const my_set*>(this))->upper_bound(a)).we);
}

template<typename T>
typename my_set<T>::iterator my_set<T>::find(const T &a) {
    return const_cast<node*>(((const_cast<const my_set*>(this))->find(a)).we);
}

template<typename T>
void swap(my_set<T>& a, my_set<T>& b) {
    a.swap(b);
}
#endif //MY_SET_MY_SET_H
