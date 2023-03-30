#ifndef _LIST_H_
#define _LIST_H_

#include <memory>
#include "err.h"

template <class T> class list;
template <class T>

class list_node : public T
{
//private:
//    list_node* next = nullptr;
public:
    list_node<T>* next = nullptr;

    list_node() = default;
    list_node(const list_node& x) = delete;
    list_node(list_node&& x) : T((T&&)x)
    {
        next = nullptr;
    }
    ~list_node() = default;
    list_node& operator=(const list_node&) = delete;
    list_node& operator=(list_node&& x)
    {
        if (this != &x)
        {
            *(T*) this = (T&&) x;
            next = x.next;
            x.next = nullptr;
        }
        return *this;
    }

    friend class list<T>;
};


template <class T>

class list
{
private:
    list_node<T>* head = nullptr;
public:
    list() = default;
    list(const list&) = delete;
    list(list&& x)
    {
        head = x.head;
        x.head = nullptr;
    }
    ~list()
    {   delete_list(); }
    list& operator=(const list&) = delete;
    list& operator=(list&& x)
    {
        if (this != &x)
        {
            head = x.head;
            x.head = nullptr;
        }
        return *this;
    }

    list_node<T>* begin()
    {   return head;    }

    io_status add_value(T& a)
    {
        list_node<T>* node = new list_node<T>((list_node<T>&&)a);
        if (node == nullptr) return io_status::memory;
        add_node(node);
        return io_status::success;
    }

    void reverse()
    {
        list<T> a;
        list_node<T>* next = nullptr;

        for(; head; head = next)
        {
            next = head->next;
            head->next = a.head;
            a.head = head;
        }

        *this = (list<T>&&) a;
    }

private:

    io_status add_node(list_node<T>* a)
    {
        if (head == nullptr)
            head = a;
        else
        {
            a->next = head;
            head = a;
        }
        return io_status::success;
    }

    void delete_list()
    {
        while(head)
        {
            list_node<T>* next = head->next;
            delete head;
            head = next;
        }
    }
};

#endif // _LIST_H_
