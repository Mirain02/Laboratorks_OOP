#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "list.h"

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
                printf("Операция вставки завершена.\n");
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
                    printf("Элемент с индексом %d найден.\nАдрес: %p\n", ind, (void*)found);
                    printf("Prev: %p\nNext: %p\n", (void*)found->prev, (void*)found->next);
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
    setlocale(LC_ALL, "ru_RU.UTF-8");
    List myList =
    {
        NULL, NULL
    };
    Menu(&myList);
    return 0;
}