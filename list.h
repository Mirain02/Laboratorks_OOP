#ifndef LIST_H
#define LIST_H

typedef struct Item
{
    struct Item* prev;
    struct Item* next;
} Item;

typedef struct List
{
    Item* head;
    Item* tail;
} List;

int Count(const List* list);
Item* GetItem(const List* list, int ind);
int GetIndex(const List* list, const Item* item);
void Add(List* list, Item* item);
void Insert(List* list, Item* item, int ind);
Item* Remove(List* list, int ind);
void Delete(List* list, int ind);
void Clear(List* list);

#endif