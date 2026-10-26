#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "subj.h"

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

int select_type(void)
{
    int t;
    while (1)
    {
        printf("Выберите тип:\n");
        printf("1. %s\n", TypeName[1]);
        printf("2. %s\n", TypeName[2]);
        printf("3. %s\n", TypeName[3]);
        printf("4. %s\n", TypeName[4]);
        t = input_int("Ваш выбор: ");
        if (t >= 1 && t <= 4) return t;
        printf("Ошибка: неверный тип.\n");
    }
}

Base* create_obj(void)
{
    Base* p = Create((ItemType)select_type());
    if (p == NULL)
    {
        printf("Ошибка: не удалось выделить память.\n");
        return NULL;
    }
    Input(p);
    return p;
}

void Menu(List* list)
{
    int choice, ind;
    Item *item, *found;
    Base* p;
    float min_v, max_v;
    while (1)
    {
        printf("\n            ----- Меню -----\n");
        printf("1. Add       - добавить объект в конец\n");
        printf("2. Insert    - вставить объект по индексу\n");
        printf("3. Delete    - удалить объект по индексу\n");
        printf("4. GetItem   - получить объект по индексу\n");
        printf("5. Remove    - исключить объект по индексу\n");
        printf("6. Count     - посчитать количество элементов\n");
        printf("7. GetIndex  - определить индекс элемента\n");
        printf("8. Clear     - очистить список\n");
        printf("9. PrintList - показать адреса списка\n");
        printf("10. PrintAll - вывести все объекты\n");
        printf("11. PrintType- вывести объекты одного типа\n");
        printf("12. Sort     - сортировать по названию\n");
        printf("13. Find     - поиск по времени жизни\n");
        printf("0. Выход\n");
        printf("-----------------------------------------------\n");
        choice = input_int("Ваш выбор: ");
        switch (choice)
        {
            case 1:
                p = create_obj();
                if (p != NULL)
                {
                    Add(list, (Item*)p);
                    printf("Объект добавлен в конец списка.\n");
                }
                break;
            case 2:
                ind = input_int("Введите индекс: ");
                p = create_obj();
                if (p != NULL)
                {
                    Insert(list, (Item*)p, ind);
                    printf("Операция вставки завершена.\n");
                }
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
                    printf("Элемент с индексом %d найден. Адрес: %p\n", ind, (void*)found);
                    Print((const Base*)found);
                }
                else
                {
                    printf("Ошибка: элемент не найден.\n");
                }
                break;
            case 5:
                ind = input_int("Введите индекс: ");
                item = Remove(list, ind);
                if (item != NULL)
                {
                    printf("Элемент исключен. Адрес: %p\n", (void*)item);
                    free(item);
                }
                else
                {
                    printf("Ошибка: элемент не найден.\n");
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
                    printf("Реальный индекс в списке: %d\n", GetIndex(list, item));
                }
                else
                {
                    printf("Ошибка: элемент не существует.\n");
                }
                break;
            case 8:
                Clear(list);
                printf("Список очищен.\n");
                break;
            case 9:
                PrintList(list);
                break;
            case 10:
                PrintAll(list);
                break;
            case 11:
                PrintType(list, (ItemType)select_type());
                break;
            case 12:
                Sort(list);
                printf("Список отсортирован по названию.\n");
                break;
            case 13:
                min_v = input_float("Минимальное время жизни (в годах): ");
                max_v = input_float("Максимальное время жизни (в годах): ");
                Find(list, min_v, max_v);
                break;
            case 0:
                Clear(list);
                printf("До свидания!\n");
                return;
            default:
                printf("Ошибка: такого пункта нет.\n");
        }
    }
}

int main(void)
{
#ifdef WIN32
    system("chcp 65001");
#endif

    List myList =
    {
        NULL, NULL
    };
    Menu(&myList);
    return 0;
}