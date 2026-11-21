#include <iostream>
#include <limits>
#include <clocale>
#ifdef _WIN32
#include <cstdlib>
#endif
#include "list.h"

using namespace std;

int inputInt(const char* prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value && cin.peek() == '\n')
        {
            cin.ignore();
            return value;
        }
        if (cin.eof()) return 0;
        cout << "Ошибка ввода! Введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

class DebugList : public List
{
public:
    void Print() const;
    void Menu();
};

void DebugList::Print() const
{
    cout << "\n-----------------------------------------------\n";
    cout << "СОСТОЯНИЕ СПИСКА\n";
    cout << "Количество элементов: " << Count() << "\n";
    cout << "-----------------------------------------------\n";

    if (Head() == nullptr)
    {
        cout << "Список пуст.\n";
        cout << "-----------------------------------------------\n\n";
        return;
    }

    const Item* cur = Head();
    int ind = 0;
    while (cur != nullptr)
    {
        cout << "[" << ind << "] Address: " << cur
             << " | Prev: " << cur->Prev()
             << " | Next: " << cur->Next() << "\n";
        cur = cur->Next();
        ind++;
    }

    cout << "-----------------------------------------------\n";
    cout << "HEAD: " << Head() << "\n";
    cout << "TAIL: " << Tail() << "\n";
    cout << "-----------------------------------------------\n\n";
}

void DebugList::Menu()
{
    int choice, ind;
    Item* item;
    Item* found;

    while (true)
    {
        cout << "\n            ----- Меню -----\n";
        cout << "1. Add         - добавить элемент в конец\n";
        cout << "2. Insert      - вставить элемент по индексу\n";
        cout << "3. Delete      - удалить элемент по индексу\n";
        cout << "4. GetItem     - получить элемент по индексу\n";
        cout << "5. Remove      - исключить элемент по индексу\n";
        cout << "6. Count       - посчитать количество элементов\n";
        cout << "7. GetIndex    - определить индекс элемента\n";
        cout << "8. Clear       - очистить список\n";
        cout << "9. Print       - показать состояние списка\n";
        cout << "10. Test ~Item - удалить элемент напрямую через delete\n";
        cout << "0. Выход\n";
        cout << "-----------------------------------------------\n";

        choice = inputInt("Ваш выбор: ");
        switch (choice)
        {
            case 1:
                item = new Item();
                Add(item);
                cout << "Элемент успешно добавлен в конец списка.\n";
                break;

            case 2:
                ind = inputInt("Введите индекс: ");
                item = new Item();
                Insert(item, ind);
                cout << "Операция вставки завершена.\n";
                break;

            case 3:
                ind = inputInt("Введите индекс: ");
                Delete(ind);
                cout << "Операция удаления завершена.\n";
                break;

            case 4:
                ind = inputInt("Введите индекс: ");
                found = GetItem(ind);
                if (found != nullptr)
                {
                    cout << "Элемент с индексом " << ind << " найден.\n";
                    cout << "Адрес: " << found << "\n";
                    cout << "Prev: " << found->Prev() << "\n";
                    cout << "Next: " << found->Next() << "\n";
                }
                else
                {
                    cout << "Ошибка: элемент не найден.\n";
                }
                break;

            case 5:
                ind = inputInt("Введите индекс: ");
                item = Remove(ind);
                if (item != nullptr)
                {
                    cout << "Элемент исключен. Адрес: " << item << "\n";
                    delete item;
                }
                else
                {
                    cout << "Ошибка: элемент не найден.\n";
                }
                break;

            case 6:
                cout << "Количество элементов в списке: " << Count() << "\n";
                break;

            case 7:
                ind = inputInt("Введите индекс: ");
                item = GetItem(ind);
                if (item != nullptr)
                {
                    cout << "Реальный индекс в списке: " << GetIndex(item) << "\n";
                }
                else
                {
                    cout << "Ошибка: элемент не существует.\n";
                }
                break;

            case 8:
                Clear();
                cout << "Список очищен.\n";
                break;

            case 9:
                Print();
                break;

            case 10:
                ind = inputInt("Введите индекс элемента для прямого delete: ");
                found = GetItem(ind);
                if (found != nullptr)
                {
                    delete found;
                    cout << "Элемент удален через delete. Проверьте состояние пунктом 9.\n";
                }
                else
                {
                    cout << "Ошибка: элемент не найден.\n";
                }
                break;

            case 0:
                cout << "Выход. Деструктор ~List() автоматически освободит память.\n";
                return;

            default:
                cout << "Ошибка: такого пункта нет.\n";
        }
    }
}

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

    DebugList myList;
    myList.Menu();
    return 0;
}