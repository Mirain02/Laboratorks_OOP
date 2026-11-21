#ifndef LIST_H
#define LIST_H

class List;

class Item
{
private:
    Item* prev;
    Item* next;
    List* list;

    friend class List;

public:
    Item();
    ~Item();

    Item* Prev() const;
    Item* Next() const;
};

class List
{
private:
    Item* head;
    Item* tail;

public:
    List();
    ~List();

    Item* Head() const;
    Item* Tail() const;

    int Count() const;
    Item* GetItem(int ind) const;
    int GetIndex(const Item* item) const;
    void Add(Item* item);
    void Insert(Item* item, int ind);
    Item* Remove(int ind);
    void Delete(int ind);
    void Clear();
};

#endif