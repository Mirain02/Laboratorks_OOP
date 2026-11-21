#include <iostream>
#include <limits>
#include <string>
#include "subj.h"

using namespace std;

const string TypeName[] =
{
    "(неизвестно)",
    "Растение",
    "Рыба",
    "Птица",
    "Животное"
};

namespace
{
    bool input01(const string& prompt)
    {
        while (true)
        {
            int val = inputInt(prompt);
            if (val == 0 || val == 1) return val == 1;
            cout << "Ошибка ввода! Введите 1 или 0.\n";
        }
    }

    string inputString(const string& prompt)
    {
        string value;
        cout << prompt;
        getline(cin >> ws, value);
        return value;
    }

    class Plant : public Base
    {
    private:
        string kind;
        string reprod;
        bool fruits;

    public:
        Plant();
        void Input();
        void Print() const;
    };

    class Fish : public Base
    {
    private:
        bool in_days;
        bool salt;

    public:
        Fish();
        void Input();
        void Print() const;
        float GetLifeYears() const;
    };

    class Bird : public Base
    {
    private:
        int eggs;
        bool fly;
        bool swim_top;
        bool swim_sub;

    public:
        Bird();
        void Input();
        void Print() const;
    };

    class Animal : public Base
    {
    private:
        string food;

    public:
        Animal();
        void Input();
        void Print() const;
    };

    Plant::Plant() : Base(itPlant), fruits(false)
    {
    }

    void Plant::Input()
    {
        InputBase();
        life = inputFloat("Время жизни (в годах): ");
        kind = inputString("Тип растения (трава, кустарник и т.п.): ");
        reprod = inputString("Способ размножения: ");
        fruits = input01("Наличие плодов (1 - да, 0 - нет): ");
    }

    void Plant::Print() const
    {
        PrintBase();
        cout << "\tВремя жизни: " << life << " лет\n";
        cout << "\tТип растения: " << kind << "\n";
        cout << "\tСпособ размножения: " << reprod << "\n";
        cout << "\tПлоды: " << (fruits ? "да" : "нет") << "\n\n";
    }

    Fish::Fish() : Base(itFish), in_days(false), salt(false)
    {
    }

    void Fish::Input()
    {
        InputBase();
        in_days = input01("Единица времени жизни (1 - дни, 0 - годы): ");
        if (in_days) life = inputFloat("Время жизни (в днях): ");
        else life = inputFloat("Время жизни (в годах): ");
        salt = input01("Тип воды (1 - соленая, 0 - пресная): ");
    }

    void Fish::Print() const
    {
        PrintBase();
        cout << "\tВремя жизни: " << life << " " << (in_days ? "дн." : "лет") << "\n";
        cout << "\tВода: " << (salt ? "соленая" : "пресная") << "\n\n";
    }

    float Fish::GetLifeYears() const
    {
        return in_days ? (life / 365.0f) : life;
    }

    Bird::Bird() : Base(itBird), eggs(0), fly(false), swim_top(false), swim_sub(false)
    {
    }

    void Bird::Input()
    {
        InputBase();
        life = inputFloat("Время жизни (в годах): ");
        eggs = inputInt("Среднее количество яиц в кладке: ");
        fly = input01("Умение летать (1 - да, 0 - нет): ");
        swim_top = input01("Плавание на воде (1 - да, 0 - нет): ");
        swim_sub = input01("Плавание под водой (1 - да, 0 - нет): ");
    }

    void Bird::Print() const
    {
        PrintBase();
        cout << "\tВремя жизни: " << life << " лет\n";
        cout << "\tЯиц в кладке: " << eggs << "\n";
        cout << "\tЛетает: " << (fly ? "да" : "нет")
             << " | На воде: " << (swim_top ? "да" : "нет")
             << " | Под водой: " << (swim_sub ? "да" : "нет") << "\n\n";
    }

    Animal::Animal() : Base(itAnimal)
    {
    }

    void Animal::Input()
    {
        InputBase();
        life = inputFloat("Время жизни (в годах): ");
        food = inputString("Тип корма: ");
    }

    void Animal::Print() const
    {
        PrintBase();
        cout << "\tВремя жизни: " << life << " лет\n";
        cout << "\tТип корма: " << food << "\n\n";
    }
}

int inputInt(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            return value;
        }
        if (cin.eof()) return 0;
        cout << "Ошибка ввода! Введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float inputFloat(const string& prompt)
{
    float value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            return value;
        }
        if (cin.eof()) return 0.0f;
        cout << "Ошибка ввода! Введите число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

Base::Base(ItemType t) : type(t), temp(0.0f), hum(0.0f), life(0.0f), rep_age(0.0f)
{
}

void Base::InputBase()
{
    name = inputString("Наименование: ");
    area = inputString("Ареал обитания: ");
    temp = inputFloat("Температура содержания: ");
    hum = inputFloat("Влажность: ");
    rep_age = inputFloat("Репродуктивный возраст: ");
}

void Base::PrintBase() const
{
    cout << "\tНаименование: " << name << "\n";
    cout << "\tАреал обитания: " << area << "\n";
    cout << "\tТемпература: " << temp << " | Влажность: " << hum << "\n";
    cout << "\tРепродуктивный возраст: " << rep_age << "\n";
}

ItemType Base::GetType() const
{
    return type;
}

const string& Base::GetName() const
{
    return name;
}

float Base::GetLifeYears() const
{
    switch (type)
    {
        case itFish:
            return static_cast<const Fish*>(this)->GetLifeYears();
        default:
            return life;
    }
}

void Base::Input()
{
    switch (type)
    {
        case itPlant:
            static_cast<Plant*>(this)->Input();
            break;
        case itFish:
            static_cast<Fish*>(this)->Input();
            break;
        case itBird:
            static_cast<Bird*>(this)->Input();
            break;
        case itAnimal:
            static_cast<Animal*>(this)->Input();
            break;
        default:
            cout << "Ошибка: неизвестный тип объекта.\n";
            break;
    }
}

void Base::Print() const
{
    if (type <= itNone || type > itAnimal)
    {
        cout << "Ошибка: неизвестный тип объекта.\n";
        return;
    }
    cout << TypeName[type] << ":\n";
    switch (type)
    {
        case itPlant:
            static_cast<const Plant*>(this)->Print();
            break;
        case itFish:
            static_cast<const Fish*>(this)->Print();
            break;
        case itBird:
            static_cast<const Bird*>(this)->Print();
            break;
        case itAnimal:
            static_cast<const Animal*>(this)->Print();
            break;
        default:
            break;
    }
}

Base* Base::Create(ItemType t)
{
    switch (t)
    {
        case itPlant:
            return new Plant();
        case itFish:
            return new Fish();
        case itBird:
            return new Bird();
        case itAnimal:
            return new Animal();
        default:
            return nullptr;
    }
}

void SubjList::Print() const
{
    if (Head() == nullptr)
    {
        cout << "Список пуст.\n";
        return;
    }

    int i = 0;
    for (const Item* p = Head(); p != nullptr; p = p->Next(), i++)
    {
        cout << i << ". ";
        static_cast<const Base*>(p)->Print();
    }
}

void SubjList::PrintType(ItemType t) const
{
    bool found = false;
    for (const Item* p = Head(); p != nullptr; p = p->Next())
    {
        const Base* b = static_cast<const Base*>(p);
        if (b->GetType() == t)
        {
            found = true;
            b->Print();
        }
    }
    if (!found)
    {
        cout << "Объекты данного типа не найдены.\n";
    }
}

void SubjList::Sort()
{
    int n = Count();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            Base* a = static_cast<Base*>(GetItem(j));
            Base* b = static_cast<Base*>(GetItem(j + 1));
            if (a->GetName() > b->GetName())
            {
                Insert(Remove(j + 1), j);
            }
        }
    }
}

void SubjList::Find(float minVal, float maxVal) const
{
    bool found = false;
    for (const Item* p = Head(); p != nullptr; p = p->Next())
    {
        const Base* b = static_cast<const Base*>(p);
        float years = b->GetLifeYears();
        if (years >= minVal && years <= maxVal)
        {
            found = true;
            b->Print();
        }
    }
    if (!found)
    {
        cout << "В заданном диапазоне ничего не найдено.\n";
    }
}