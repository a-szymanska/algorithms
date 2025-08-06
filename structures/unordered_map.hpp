/**
 * An implementation of unordered map template
 * using the cuckoo hashing which gives the amortised cost
 * of insertion and deletion operations O(1).
 */

#include <vector>
#ifndef ALGORITHMS_UNORDERED_MAP_H
#define ALGORITHMS_UNORDERED_MAP_H


template <class Key, class Value>
struct Node {
    std::pair<Key, Value> p;
    Node<Key, Value>* next = nullptr;
    Node<Key, Value>* prev = nullptr;
};

template <class Key, class Value>
class UnorderedMap {
public:
    class Iterator;
    class LinkedList;
    LinkedList list;
    Node<Key, Value>** tab1;
    Node<Key, Value>** tab2;
    int map_size = 0, capacity = 127;

    UnorderedMap() {
        tab1 = new Node<Key, Value>*[capacity];
        tab2 = new Node<Key, Value>*[capacity];
        std::fill_n(tab1, capacity, nullptr);
        std::fill_n(tab2, capacity, nullptr);
    }
    UnorderedMap(const UnorderedMap & m) : capacity(m.capacity) {
        tab1 = new Node<Key, Value>*[capacity];
        tab2 = new Node<Key, Value>*[capacity];
        std::fill_n(tab1, capacity, nullptr);
        std::fill_n(tab2, capacity, nullptr);
        for (auto n : m) {
            insert(n);
        }
    }
    ~UnorderedMap() {
        delete[] tab1; delete[] tab2;
        list.clearList();
    }
    UnorderedMap& operator=(const UnorderedMap & m) {
        if (&m == this) {
            return *this;
        }
        delete[] tab1; delete[] tab2;
        capacity = m.capacity;
        list.clearList();
        tab1 = new Node<Key, Value>*[capacity];
        tab2 = new Node<Key, Value>*[capacity];
        std::fill_n(tab1, capacity, nullptr);
        std::fill_n(tab2, capacity, nullptr);
        for (auto n : m) {
            insert(n);
        }
        return *this;
    }

    std::size_t getHash1(const Key& key) {
        std::size_t hash = std::hash<Key>()(key);
        return hash % capacity;
    }
    std::size_t getHash2(const Key & key) {
        std::size_t hash = std::hash<Key>()(key);
        return ((hash >> 32) ^ (hash * 1696969)) % capacity;
    }
    std::pair<Iterator, bool> insert(const std::pair<Key, Value> & p) {
        Iterator it = find(p.first);
        if (it != end()) {
            it->second = p.second;
            return std::pair<Iterator, bool>(it, false);
        }
        auto* n = new Node<Key, Value>;
        n->p = p;
        Node<Key, Value>* stored_n = n;
        list.insert(n);
        ++map_size;
        for (int i = 0; i < 50; ++i) {
            swap(n, tab1[getHash1(n->p.first)]);
            if (n == nullptr) {
                return std::pair<Iterator, bool>(Iterator(stored_n), true);
            }
            swap(n, tab2[getHash2(n->p.first)]);
            if (n == nullptr) {
                return std::pair<Iterator, bool>(Iterator(stored_n), true);
            }
        }
        rehash();
        return std::pair<Iterator, bool>(Iterator(stored_n), true);
    }
    bool insert(Node<Key, Value>* n) {
        for (int i = 0; i < 100; i++) {
            swap(n, tab1[getHash1(n->p.first)]);
            if (n == nullptr) {
                return true;
            }
            swap(n, tab2[getHash2(n->p.first)]);
            if (n == nullptr) {
                return true;
            }
        }
        return false;
    }
    std::size_t erase(const Key & key) {
        Iterator it = find(key);
        if (it != end()) {
            erase(it);
            return 1;
        }
        return 0;
    }
    Iterator erase(const Iterator & it) {
        if (it.tmp == list.tail || it.tmp == list.head) return end();
        Key key = it.tmp->p.first;
        Node<Key, Value>* tmp = nullptr;
        std::size_t h1 = getHash1(key), h2 = getHash2(key);
        if (tab1[h1] != nullptr && tab1[h1]->p.first == key) {
            tmp = tab1[h1]->next;
            list.erase(tab1[h1]);
            tab1[h1] = nullptr;
        } else if (tab2[h2] != nullptr && tab2[h2]->p.first == key) {
            tmp = tab2[h2]->next;
            list.erase(tab2[h2]);
            tab2[h2] = nullptr;
        }
        if (tmp != nullptr) {
            --map_size;
            return Iterator(tmp);
        }
        return end();
    }
    Iterator end() const {
        return Iterator(list.tail);
    }
    Iterator begin() const {
        return Iterator(list.head->next);
    }
    Iterator find(const Key& key) {
        std::size_t h1 = getHash1(key), h2 = getHash2(key);
        if (tab1[h1] != nullptr && tab1[h1]->p.first == key) {
            return Iterator(tab1[h1]);
        } else if (tab2[h2] != nullptr && tab2[h2]->p.first == key) {
            return Iterator(tab2[h2]);
        }
        return end();
    }
    std::size_t size() {
        return (std::size_t) map_size;
    }
    void rehash() {
        capacity *= 2;
        delete[] tab1; delete[] tab2;
        tab1 = new Node<Key, Value>*[capacity];
        tab2 = new Node<Key, Value>*[capacity];
        std::fill_n(tab1, capacity, nullptr);
        std::fill_n(tab2, capacity, nullptr);
        bool luckily_done = true;
        Node<Key, Value>* tmp = list.head->next;
        while (tmp != list.tail && luckily_done) {
            luckily_done = insert(tmp);
            tmp = tmp->next;
        }
        if (!luckily_done) {
            rehash();
        }
    }
    void clear() {
        list.clearList();
        delete[] tab1; delete[] tab2;
        capacity = 120; map_size = 0;
        tab1 = new Node<Key, Value>*[capacity];
        tab2 = new Node<Key, Value>*[capacity];
        std::fill_n(tab1, capacity, nullptr);
        std::fill_n(tab2, capacity, nullptr);
    }
    Value& operator[](const Key & key) {
        Iterator it = find(key);
        if(it == end()) {
            std::pair<Key, Value> p;
            p.first = key;
            it = insert(p).first;
        }
        return it->second;
    }
};

template <class Key, class Value>
class UnorderedMap<Key, Value>::LinkedList
{
public:
    Node<Key, Value>* head;
    Node<Key, Value>* tail;

    LinkedList() {
        head = new Node<Key, Value>;
        tail = new Node<Key, Value>;
        head->next = tail;
        tail->prev = head;
        head->prev = tail->next = nullptr;
    }
    ~LinkedList() {
        clearList();
        delete head;
        delete tail;
    }

    void insert(Node<Key, Value>* n) {
        tail->prev->next = n;
        n->prev = tail->prev;
        tail->prev = n;
        n->next = tail;
    }
    void erase(Node<Key, Value>* n) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        n->next = n->prev = nullptr;
        delete n;
    }
    void clearList() {
        Node<Key, Value>* tmp = head->next;
        while (tmp->next != nullptr) {
            head->next = tmp->next;
            delete tmp;
            tmp = head->next;
        }
        head->next = tail;
        tail->prev = head;
    }
};

template <class Key, class Value>
class UnorderedMap<Key, Value>::Iterator
{
public:
    Node<Key, Value>* tmp = nullptr;
    Iterator() = default;
    explicit Iterator(Node<Key, Value>* _tmp) {
        tmp = _tmp;
    }

    std::pair<Key, Value>& operator*() {
        return tmp->p;
    }
    std::pair<Key, Value>* operator->() {
        return &tmp->p;
    }
    Iterator operator++(int) {
        Iterator old_it = *this;
        if (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        return old_it;
    }
    Iterator& operator++() {
        if (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        return *this;
    }
    Iterator operator--(int) {
        Iterator old_it = *this;
        if (tmp == nullptr || tmp->prev == nullptr) {
            return *this;
        }
        if (tmp->prev->prev != nullptr) {
            tmp = tmp->prev;
        }
        return old_it;
    }
    Iterator& operator--() {
        if (tmp == nullptr || tmp->prev == nullptr) {
            return *this;
        }
        if (tmp->prev->prev != nullptr) {
            tmp = tmp->prev;
        }
        return *this;
    }
    friend bool operator==(const Iterator& it1, const Iterator& it2) {
        return (it1.tmp == it2.tmp);
    }
    friend bool operator!=(const Iterator& it1, const Iterator& it2) {
        return (it1.tmp != it2.tmp);
    }
};

#endif //ALGORITHMS_UNORDERED_MAP_H
