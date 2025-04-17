/**
 * Implementation of double linked list template with reverse
 * and merge operations. All operations (except clear) are performed
 * in constant time.
 * Created on 10.01.2023
 */

#ifndef ALGORITHMS_DOUBLE_LINKED_LIST_HPP
#define ALGORITHMS_DOUBLE_LINKED_LIST_HPP

#include <iostream>

template <class T>
class Node {
public:
    T name;
    Node* next[2];
    Node( ) = default;
    Node(const T & _name) { name = _name; }

    friend std::ostream &operator<<(std::ostream &os, const Node & node) {
        os << node.name;
        return os;
    }
};

template <class T>
class DoubleList {
public:
    Node<T>* head;
    Node<T>* tail;
    DoubleList () {
        head = new Node<T>();
        tail = new Node<T>();
        head->next[0] = tail;
        head->next[1] = tail;
        tail->next[0] = head;
        tail->next[1] = head;
    }
    ~DoubleList () {
        clear();
        delete head;
        delete tail;
    }

    bool empty() {
        return (head->next[0] == tail && head->next[1] == tail);
    }

    /**
     * Add node initialized with name to the beginning of the list
     * @param name
     */
    void push_front(const T & name) {
        auto * node = new Node<T>(name);
        push_front(node);
    }

    /**
     * Add the node to the beginning of the list
     * @param n
     */
    void push_front(Node<T>* node) {
        bool dir_head = (head->next[0] == tail);
        bool dir_sec = (head->next[dir_head]->next[1] == head);
        node->next[dir_head] = head->next[dir_head];
        node->next[dir_head]->next[dir_sec] = node;
        node->next[1-dir_head] = head;
        head->next[dir_head] = node;
    }

    /**
     * Add node initialized with name to the end of the list
     * @param name
     */
    void push_back(const T & name) {
        auto * node = new Node<T>(name);
        push_back(node);
    }

    /**
     * Add node to the end of the list
     * @param node
     */
    void push_back(Node<T>* node) {
        bool dir_tail = (tail->next[0] == head);
        bool dir_last = (tail->next[dir_tail]->next[1] == tail);
        node->next[dir_tail] = tail->next[dir_tail];
        node->next[dir_tail]->next[dir_last] = node;
        node->next[1-dir_tail] = tail;
        tail->next[dir_tail] = node;
    }

    /**
     * Remove the first element from the list.
     * If list is empty, return nullptr;
     * @return      pointer to the removed node
     */
    Node<T> * pop_front() {
        if (empty()) return nullptr;
        bool dir_head = (head->next[0] == tail);
        bool dir_n = (head->next[dir_head]->next[0] == head);
        bool dir_after_n = (head->next[dir_head]->next[dir_n]->next[1] == head->next[dir_head]);
        Node<T>* node = head->next[dir_head];
        head->next[dir_head] = node->next[dir_n];
        node->next[dir_n]->next[dir_after_n] = head;
        node->next[0] = nullptr;
        node->next[1] = nullptr;
        return node;
    }

    /**
     * Remove the last element from the list.
     * If list is empty, return nullptr;
     * @return      pointer to the removed node
     */
    Node<T> * pop_back() {
        if (empty()) return nullptr;
        bool dir_tail = (tail->next[0] == head);
        bool dir_n = (tail->next[dir_tail]->next[0] == tail);
        bool dir_prev_n = (tail->next[dir_tail]->next[dir_n]->next[1] == tail->next[dir_tail]);
        Node<T>* node = tail->next[dir_tail];
        tail->next[dir_tail] = node->next[dir_n];
        node->next[dir_n]->next[dir_prev_n] = tail;
        node->next[0] = nullptr;
        node->next[1] = nullptr;
        return node;
    }

    /**
     *  Reverse the order of elements in the list
     */
    void reverse() {
        if (empty()) return;
        bool dir_head = (head->next[0] == tail);
        bool dir_tail = (tail->next[0] == head);
        bool dir_sec = (head->next[dir_head]->next[1] == head);
        bool dir_last = (tail->next[dir_tail]->next[1] == tail);
        head->next[1-dir_head] = tail->next[dir_tail];
        tail->next[1-dir_tail] = head->next[dir_head];
        head->next[dir_head] = tail;
        tail->next[dir_tail] = head;
        tail->next[1-dir_tail]->next[dir_sec] = tail;
        head->next[1-dir_head]->next[dir_last] = head;
    }

    /**
     * Add all elements of list L to the end of this list
     * After the operation, L becomes empty
     * @param L
     */
    void merge(DoubleList<T>& L) {
        if (L.empty()) return;
        bool dir_tail = (tail->next[0] == head);
        bool dir_last = (tail->next[dir_tail]->next[1] == tail);
        bool dir_head_L = (L.head->next[0] == L.tail);
        bool dir_sec_L = (L.head->next[dir_head_L]->next[1] == L.head);
        bool dir_tail_L = (L.tail->next[0] == L.head);
        bool dir_last_L = (L.tail->next[dir_tail_L]->next[1] == L.tail);

        tail->next[dir_tail]->next[dir_last] = L.head->next[dir_head_L];
        L.head->next[dir_head_L]->next[dir_sec_L] = tail->next[dir_tail];
        L.tail->next[dir_tail_L]->next[dir_last_L] = tail;
        tail->next[0] = L.tail->next[dir_tail_L];
        tail->next[1] = head;
        L.tail->next[0] = L.head;
        L.tail->next[1] = L.head;
        L.head->next[0] = L.tail;
        L.head->next[1] = L.tail;
    }

    /**
     * Remove elements from the list
     */
    void clear() {
        if (empty()) return;
        bool dir_head = (head->next[0] == tail);
        Node<T>* temp = head->next[dir_head];
        bool dir_this, dir_next = (temp->next[0] == head);
        while (temp != tail) {
            dir_this = dir_next;
            dir_next = (temp->next[dir_this]->next[0] == temp);
            head->next[dir_head] = temp->next[dir_this];
            head->next[dir_head]->next[1-dir_next] = head;
            delete temp;
            temp = head->next[dir_head];
        }
        head->next[0] = tail;
        head->next[1] = tail;
        tail->next[0] = head;
        tail->next[1] = head;
    }

    class Iterator {
    public:
        Node<T> *current = nullptr;
        Node<T> *prev = nullptr;

        Iterator(Node<T> *_current, Node<T> *_prev) : prev(_prev), current(_current) { }

        T & operator*() const {
            return current->name;
        }

        Iterator & operator++() {
            bool dir = (current->next[0] == prev);
            prev = current;
            current = current->next[dir];
            return *this;
        }

        bool operator!=(const Iterator &other) const {
            return current != other.current;
        }
    };

    Iterator begin() const {
        bool dir = (head->next[0] == tail);
        return Iterator(head->next[dir], head);
    }

    Iterator end() const {
        bool dir = (tail->next[0] == head);
        return Iterator(tail, tail->next[dir]);
    }
};

#endif //ALGORITHMS_DOUBLE_LINKED_LIST_HPP
