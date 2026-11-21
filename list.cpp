#include "list.h"

Item::Item() : prev(nullptr), next(nullptr), list(nullptr)
{
}

Item::~Item()
{
    if (list != nullptr)
    {
        list->Remove(list->GetIndex(this));
    }
}

Item* Item::Prev() const
{
    return prev;
}

Item* Item::Next() const
{
    return next;
}

List::List() : head(nullptr), tail(nullptr)
{
}

List::~List()
{
    Clear();
}

Item* List::Head() const
{
    return head;
}

Item* List::Tail() const
{
    return tail;
}

int List::Count() const
{
    int count = 0;
    const Item* cur = head;
    while (cur != nullptr)
    {
        count++;
        cur = cur->next;
    }
    return count;
}

Item* List::GetItem(int ind) const
{
    if (ind < 0) return nullptr;
    Item* cur = head;
    int i = 0;
    while (cur != nullptr && i < ind)
    {
        cur = cur->next;
        i++;
    }
    return cur;
}

int List::GetIndex(const Item* item) const
{
    if (item == nullptr) return -1;
    const Item* cur = head;
    int ind = 0;
    while (cur != nullptr)
    {
        if (cur == item) return ind;
        cur = cur->next;
        ind++;
    }
    return -1;
}

void List::Add(Item* item)
{
    if (item == nullptr || item->list != nullptr) return;

    item->next = nullptr;
    item->prev = tail;
    item->list = this;

    if (head == nullptr)
    {
        head = item;
        tail = item;
    }
    else
    {
        tail->next = item;
        tail = item;
    }
}

void List::Insert(Item* item, int ind)
{
    if (item == nullptr || item->list != nullptr) return;

    Item* cur = GetItem(ind);
    if (cur == nullptr)
    {
        Add(item);
        return;
    }

    item->next = cur;
    item->prev = cur->prev;
    item->list = this;

    if (cur->prev != nullptr)
    {
        cur->prev->next = item;
    }
    else
    {
        head = item;
    }
    cur->prev = item;
}

Item* List::Remove(int ind)
{
    Item* item = GetItem(ind);
    if (item == nullptr) return nullptr;

    if (item->prev != nullptr) item->prev->next = item->next;
    else head = item->next;

    if (item->next != nullptr) item->next->prev = item->prev;
    else tail = item->prev;

    item->prev = nullptr;
    item->next = nullptr;
    item->list = nullptr;
    return item;
}

void List::Delete(int ind)
{
    Item* item = Remove(ind);
    if (item != nullptr)
    {
        delete item;
    }
}

void List::Clear()
{
    while (head != nullptr)
    {
        Delete(0);
    }
}