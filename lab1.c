#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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
    Item* cur = list->head;
    Item* prev_item = NULL;
    int i = 0;
    if (list == NULL || item == NULL) return;
    if (ind < 0)
    {
        free(item);
        return;
    }
    while (cur != NULL && i < ind)
    {
        prev_item = cur;
        cur = cur->next;
        i++;
    }
    if (i < ind)
    {
        free(item);
        return;
    }
    item->prev = prev_item;
    item->next = cur;
    if (prev_item != NULL)
    {
        prev_item->next = item;
    }
    else
    {
        list->head = item;
    }
    if (cur != NULL)
    {
        cur->prev = item;
    }
    else
    {
        list->tail = item;
    }
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

void PrintList(const List* list)
{
    const Item* cur;
    int ind = 0;
    if (list == NULL)
    {
        printf("\nСписок не существует.\n\n");
        return;
    }
    printf("\n-----------------------------------------------\n");
    printf("СОСТОЯНИЕ СПИСКА\n");
    printf("Количество элементов: %d\n", Count(list));
    printf("-----------------------------------------------\n");
    if (list->head == NULL)
    {
        printf("Список пуст.\n");
        printf("-----------------------------------------------\n\n");
        return;
    }
    cur = list->head;
    while (cur != NULL)
    {
        printf("[%d] Address: %p | Prev: %p | Next: %p\n", ind, (void*)cur, (void*)cur->prev, (void*)cur->next);
        cur = cur->next;
        ind++;
    }
    printf("-----------------------------------------------\n");
    printf("HEAD: %p\n", (void*)list->head);
    printf("TAIL: %p\n", (void*)list->tail);
    printf("-----------------------------------------------\n\n");
}

int input_int(const char* prompt)
{
    int value;
    char buf;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d%c", &value, &buf) == 2 && buf == '\n') return value;
        printf("Ошибка ввода! Введите целое число.\n");
        while (getchar() != '\n');
    }
}

void Menu(List* list)
{
    int choice, ind;
    Item *item, *found;
    while (1)
    {
        printf("\n            ----- Меню -----\n");
        printf("1. Add       - добавить элемент в конец\n");
        printf("2. Insert    - вставить элемент по индексу\n");
        printf("3. Delete    - удалить элемент по индексу\n");
        printf("4. GetItem   - получить элемент по индексу\n");
        printf("5. Remove    - исключить элемент по индексу\n");
        printf("6. Count     - посчитать количество элементов\n");
        printf("7. GetIndex  - определить индекс элемента\n");
        printf("8. Clear     - очистить список\n");
        printf("9. PrintList - показать состояние списка\n");
        printf("0. Выход\n");
        printf("-----------------------------------------------\n");
        choice = input_int("Ваш выбор: ");
        switch (choice)
        {
            case 1:
                item = (Item*)malloc(sizeof(Item));
                if (item == NULL)
                {
                    printf("Ошибка: не удалось выделить память.\n");
                    break;
                }
                Add(list, item);
                printf("Элемент успешно добавлен в конец списка.\n");
                break;
            case 2:
                ind = input_int("Введите индекс: ");
                item = (Item*)malloc(sizeof(Item));
                if (item == NULL)
                {
                    printf("Ошибка: не удалось выделить память.\n");
                    break;
                }
                Insert(list, item, ind);
                printf("Операция вставки завершена (если индекс корректный).\n");
                break;
            case 3:
                ind = input_int("Введите индекс: ");
                Delete(list, ind);
                printf("Операция удаления завершена.\n");
                break;
            case 4:
                ind = input_int("Введите индекс: ");
                found = GetItem(list, ind);
                if (found != NULL)
                {
                    printf("Элемент с индексом %d найден.\nАдрес элемента: %p\n", ind, (void*)found);
                    printf("Prev: %p\nNext: %p\n", (void*)found->prev, (void*)found->next);
                }
                else
                {
                    printf("Ошибка: элемент не найден (пустой список или неверный индекс).\n");
                }
                break;
            case 5:
                ind = input_int("Введите индекс: ");
                item = Remove(list, ind);
                if (item != NULL)
                {
                    printf("Элемент с индексом %d исключен из списка.\nАдрес исключенного элемента: %p\n", ind, (void*)item);
                    free(item);
                }
                else
                {
                    printf("Ошибка: элемент не найден (пустой список или неверный индекс).\n");
                }
                break;
            case 6:
                printf("Количество элементов в списке: %d\n", Count(list));
                break;
            case 7:
                ind = input_int("Введите индекс: ");
                item = GetItem(list, ind);
                if (item != NULL)
                {
                    printf("Адрес элемента найден, его реальный индекс в списке: %d\n", GetIndex(list, item));
                }
                else
                {
                    printf("Ошибка: элемент с таким индексом не существует.\n");
                }
                break;
            case 8:
                Clear(list);
                printf("Список полностью очищен.\n");
                break;
            case 9:
                PrintList(list);
                break;
            case 0:
                Clear(list);
                printf("Память освобождена. До свидания!\n");
                return;
            default:
                printf("Ошибка: такого пункта меню нет. Введите число от 0 до 9.\n");
        }
    }
}

int main(void)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    List myList = {NULL, NULL};
    Menu(&myList);
    return 0;
}
