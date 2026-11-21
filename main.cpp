#include <iostream>
#include <clocale>
#ifdef _WIN32
#include <cstdlib>
#endif
#include "subj.h"

using namespace std;

namespace
{
    void printAddresses(const SubjList& list)
    {
        cout << "\n-----------------------------------------------\n";
        cout << "СОСТОЯНИЕ СПИСКА\n";
        cout << "Количество элементов: " << list.Count() << "\n";
        cout << "-----------------------------------------------\n";

        if (list.Head() == nullptr)
        {
            cout << "Список пуст.\n";
            cout << "-----------------------------------------------\n\n";
            return;
        }

        const Item* cur = list.Head();
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
        cout << "HEAD: " << list.Head() << "\n";
        cout << "TAIL: " << list.Tail() << "\n";
        cout << "-----------------------------------------------\n\n";
    }

    ItemType selectType()
    {
        while (true)
        {
            cout << "Выберите тип:\n";
            cout << "1. " << TypeName[1] << "\n";
            cout << "2. " << TypeName[2] << "\n";
            cout << "3. " << TypeName[3] << "\n";
            cout << "4. " << TypeName[4] << "\n";
            int t = inputInt("Ваш выбор: ");
            if (cin.eof()) return itNone;
            if (t >= 1 && t <= 4) return static_cast<ItemType>(t);
            cout << "Ошибка: неверный тип.\n";
        }
    }

    Base* createObj()
    {
        Base* p = Base::Create(selectType());
        if (p == nullptr)
        {
            cout << "Ошибка: не удалось создать объект.\n";
            return nullptr;
        }
        p->Input();
        return p;
    }

    void runMenu(SubjList& list)
    {
        int choice, ind;
        Item* item;
        Item* found;
        Base* p;
        float minVal, maxVal;

        while (true)
        {
            cout << "\n            ----- Меню -----\n";
            cout << "1. Add        - добавить объект в конец\n";
            cout << "2. Insert     - вставить объект по индексу\n";
            cout << "3. Delete     - удалить объект по индексу\n";
            cout << "4. GetItem    - получить объект по индексу\n";
            cout << "5. Remove     - исключить объект по индексу\n";
            cout << "6. Count      - посчитать количество элементов\n";
            cout << "7. GetIndex   - определить индекс элемента\n";
            cout << "8. Clear      - очистить список\n";
            cout << "9. PrintList  - показать адреса списка\n";
            cout << "10. PrintAll  - вывести все объекты\n";
            cout << "11. PrintType - вывести объекты одного типа\n";
            cout << "12. Sort      - сортировать по названию\n";
            cout << "13. Find      - поиск по времени жизни\n";
            cout << "0. Выход\n";
            cout << "-----------------------------------------------\n";

            choice = inputInt("Ваш выбор: ");
            switch (choice)
            {
                case 1:
                    p = createObj();
                    if (p != nullptr)
                    {
                        list.Add(p);
                        cout << "Объект добавлен в конец списка.\n";
                    }
                    break;

                case 2:
                    ind = inputInt("Введите индекс: ");
                    p = createObj();
                    if (p != nullptr)
                    {
                        list.Insert(p, ind);
                        cout << "Операция вставки завершена.\n";
                    }
                    break;

                case 3:
                    ind = inputInt("Введите индекс: ");
                    list.Delete(ind);
                    cout << "Операция удаления завершена.\n";
                    break;

                case 4:
                    ind = inputInt("Введите индекс: ");
                    found = list.GetItem(ind);
                    if (found != nullptr)
                    {
                        cout << "Элемент с индексом " << ind << " найден. Адрес: " << found << "\n";
                        static_cast<const Base*>(found)->Print();
                    }
                    else
                    {
                        cout << "Ошибка: элемент не найден.\n";
                    }
                    break;

                case 5:
                    ind = inputInt("Введите индекс: ");
                    item = list.Remove(ind);
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
                    cout << "Количество элементов в списке: " << list.Count() << "\n";
                    break;

                case 7:
                    ind = inputInt("Введите индекс: ");
                    item = list.GetItem(ind);
                    if (item != nullptr)
                    {
                        cout << "Реальный индекс в списке: " << list.GetIndex(item) << "\n";
                    }
                    else
                    {
                        cout << "Ошибка: элемент не существует.\n";
                    }
                    break;

                case 8:
                    list.Clear();
                    cout << "Список очищен.\n";
                    break;

                case 9:
                    printAddresses(list);
                    break;

                case 10:
                    list.Print();
                    break;

                case 11:
                    list.PrintType(selectType());
                    break;

                case 12:
                    list.Sort();
                    cout << "Список отсортирован по названию.\n";
                    break;

                case 13:
                    minVal = inputFloat("Минимальное время жизни (в годах): ");
                    maxVal = inputFloat("Максимальное время жизни (в годах): ");
                    list.Find(minVal, maxVal);
                    break;

                case 0:
                    cout << "До свидания!\n";
                    return;

                default:
                    cout << "Ошибка: такого пункта нет.\n";
            }
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

    SubjList myList;
    runMenu(myList);
    return 0;
}