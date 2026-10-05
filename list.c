#include "list.h"
#include <stdlib.h>

int Count(const List* list)
{
    int count = 0;
    const Item* cur;
    if (list == NULL) return 0;
    cur = list->head;
    while (cur != NULL)
    {
        count++;
        cur = cur->next;
    }
    return count;
}

Item* GetItem(const List* list, int ind)
{
    Item* cur;
    int i = 0;
    if (list == NULL || ind < 0) return NULL;
    cur = list->head;
    while (cur != NULL && i < ind)
    {
        cur = cur->next;
        i++;
    }
    return cur;
}

int GetIndex(const List* list, const Item* item)
{
    const Item* cur;
    int ind = 0;
    if (list == NULL || item == NULL) return -1;
    cur = list->head;
    while (cur != NULL)
    {
        if (cur == item) return ind;
        cur = cur->next;
        ind++;
    }
    return -1;
}

void Add(List* list, Item* item)
{
    if (list == NULL || item == NULL) return;
    item->next = NULL;
    item->prev = list->tail;
    if (list->head == NULL)
    {
        list->head = item;
        list->tail = item;
    }
    else
    {
        list->tail->next = item;
        list->tail = item;
    }
}

void Insert(List* list, Item* item, int ind)
{
    Item* cur;
    if (list == NULL || item == NULL) return;
    cur = GetItem(list, ind);
    if (cur == NULL)
    {
        Add(list, item);
        return;
    }
    item->next = cur;
    item->prev = cur->prev;
    if (cur->prev != NULL)
    {
        cur->prev->next = item;
    }
    else
    {
        list->head = item;
    }
    cur->prev = item;
}

Item* Remove(List* list, int ind)
{
    Item* item;
    if (list == NULL) return NULL;
    item = GetItem(list, ind);
    if (item == NULL) return NULL;
    if (item->prev != NULL) item->prev->next = item->next;
    else list->head = item->next;
    if (item->next != NULL) item->next->prev = item->prev;
    else list->tail = item->prev;
    item->prev = NULL;
    item->next = NULL;
    return item;
}

void Delete(List* list, int ind)
{
    Item* item = Remove(list, ind);
    if (item != NULL) free(item);
}

void Clear(List* list)
{
    if (list == NULL) return;
    while (list->head != NULL) Delete(list, 0);
}