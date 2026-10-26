#include "subj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

typedef struct Plant
{
    struct Item* prev;
    struct Item* next;
    ItemType type;
    char name[100];
    char area[100];
    float temp;
    float hum;
    float life;
    float rep_age;
    char kind[80];
    char reprod[80];
    int fruits;
} Plant;

typedef struct Fish
{
    struct Item* prev;
    struct Item* next;
    ItemType type;
    char name[100];
    char area[100];
    float temp;
    float hum;
    float life;
    float rep_age;
    int in_days;
    int salt;
} Fish;

typedef struct Bird
{
    struct Item* prev;
    struct Item* next;
    ItemType type;
    char name[100];
    char area[100];
    float temp;
    float hum;
    float life;
    float rep_age;
    int eggs;
    int fly;
    int swim_top;
    int swim_sub;
} Bird;

typedef struct Animal
{
    struct Item* prev;
    struct Item* next;
    ItemType type;
    char name[100];
    char area[100];
    float temp;
    float hum;
    float life;
    float rep_age;
    char food[80];
} Animal;

const char* const TypeName[] =
{
    "(неизвестно)",
    "Растение",
    "Рыба",
    "Птица",
    "Животное"
};

int input_int(const char* prompt)
{
    int val;
    char buf;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d%c", &val, &buf) == 2 && buf == '\n') return val;
        printf("Ошибка ввода! Введите целое число.\n");
        while (getchar() != '\n');
    }
}

static int input_01(const char* prompt)
{
    int val;
    while (1)
    {
        val = input_int(prompt);
        if (val == 0 || val == 1) return val;
        printf("Ошибка ввода! Введите 1 или 0.\n");
    }
}

float input_float(const char* prompt)
{
    float val;
    char buf;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%f%c", &val, &buf) == 2 && buf == '\n') return val;
        printf("Ошибка ввода! Введите число.\n");
        while (getchar() != '\n');
    }
}

void input_str(const char* prompt, char* str, int size)
{
    size_t len;
#ifdef _WIN32
    wchar_t wstr[256];
#endif
    printf("%s", prompt);
    if (fgets(str, size, stdin) == NULL)
    {
        str[0] = '\0';
        return;
    }
    len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
    else while (getchar() != '\n');
#ifdef _WIN32
    MultiByteToWideChar(GetConsoleCP(), 0, str, -1, wstr, 256);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, size, NULL, NULL);
#endif
}

static void input_base(Base* p)
{
    input_str("Наименование: ", p->name, sizeof(p->name));
    input_str("Ареал обитания: ", p->area, sizeof(p->area));
    p->temp = input_float("Температура содержания: ");
    p->hum = input_float("Влажность: ");
    if (p->type != itFish)
    {
        p->life = input_float("Время жизни (в годах): ");
    }
    p->rep_age = input_float("Репродуктивный возраст: ");
}

static void input_plant(Plant* p)
{
    input_base((Base*)p);
    input_str("Тип растения (трава, кустарник и т.п.): ", p->kind, sizeof(p->kind));
    input_str("Способ размножения: ", p->reprod, sizeof(p->reprod));
    p->fruits = input_01("Наличие плодов (1 - да, 0 - нет): ");
}

static void input_fish(Fish* p)
{
    input_base((Base*)p);
    p->in_days = input_01("Единица времени жизни (1 - дни, 0 - годы): ");
    if (p->in_days) p->life = input_float("Время жизни (в днях): ");
    else p->life = input_float("Время жизни (в годах): ");
    p->salt = input_01("Тип воды (1 - соленая, 0 - пресная): ");
}

static void input_bird(Bird* p)
{
    input_base((Base*)p);
    p->eggs = input_int("Среднее количество яиц в кладке: ");
    p->fly = input_01("Умение летать (1 - да, 0 - нет): ");
    p->swim_top = input_01("Плавание на воде (1 - да, 0 - нет): ");
    p->swim_sub = input_01("Плавание под водой (1 - да, 0 - нет): ");
}

static void input_animal(Animal* p)
{
    input_base((Base*)p);
    input_str("Тип корма: ", p->food, sizeof(p->food));
}

void Input(Base* p)
{
    if (p == NULL) return;
    switch (p->type)
    {
        case itPlant:
            input_plant((Plant*)p);
            break;
        case itFish:
            input_fish((Fish*)p);
            break;
        case itBird:
            input_bird((Bird*)p);
            break;
        case itAnimal:
            input_animal((Animal*)p);
            break;
        default:
            printf("Ошибка: неизвестный тип объекта.\n");
            break;
    }
}

static void print_base(const Base* p)
{
    printf("\tНаименование: %s\n", p->name);
    printf("\tАреал обитания: %s\n", p->area);
    printf("\tТемпература: %.1f | Влажность: %.1f\n", p->temp, p->hum);
    if (p->type != itFish)
    {
        printf("\tВремя жизни: %.1f лет\n", p->life);
    }
    printf("\tРепродуктивный возраст: %.1f\n", p->rep_age);
}

static void print_plant(const Plant* p)
{
    print_base((const Base*)p);
    printf("\tТип растения: %s\n", p->kind);
    printf("\tСпособ размножения: %s\n", p->reprod);
    printf("\tПлоды: %s\n\n", p->fruits ? "да" : "нет");
}

static void print_fish(const Fish* p)
{
    print_base((const Base*)p);
    printf("\tВремя жизни: %.1f %s\n", p->life, p->in_days ? "дн." : "лет");
    printf("\tВода: %s\n\n", p->salt ? "соленая" : "пресная");
}

static void print_bird(const Bird* p)
{
    print_base((const Base*)p);
    printf("\tЯиц в кладке: %d\n", p->eggs);
    printf("\tЛетает: %s | На воде: %s | Под водой: %s\n\n",
           p->fly ? "да" : "нет",
           p->swim_top ? "да" : "нет",
           p->swim_sub ? "да" : "нет");
}

static void print_animal(const Animal* p)
{
    print_base((const Base*)p);
    printf("\tТип корма: %s\n\n", p->food);
}

void Print(const Base* p)
{
    if (p == NULL)
    {
        printf("Ошибка: пустой указатель.\n");
        return;
    }
    if (p->type <= itNone || p->type > itAnimal)
    {
        printf("Ошибка: неизвестный тип объекта.\n");
        return;
    }
    printf("%s:\n", TypeName[p->type]);
    switch (p->type)
    {
        case itPlant:
            print_plant((const Plant*)p);
            break;
        case itFish:
            print_fish((const Fish*)p);
            break;
        case itBird:
            print_bird((const Bird*)p);
            break;
        case itAnimal:
            print_animal((const Animal*)p);
            break;
        default:
            break;
    }
}

Base* Create(ItemType t)
{
    Base* p = NULL;
    switch (t)
    {
        case itPlant:
            p = (Base*)calloc(1, sizeof(Plant));
            break;
        case itFish:
            p = (Base*)calloc(1, sizeof(Fish));
            break;
        case itBird:
            p = (Base*)calloc(1, sizeof(Bird));
            break;
        case itAnimal:
            p = (Base*)calloc(1, sizeof(Animal));
            break;
        default:
            return NULL;
    }
    if (p != NULL) p->type = t;
    return p;
}

void PrintAll(const List* L)
{
    Item* p;
    int i = 0;
    if (L == NULL) return;
    if (L->head == NULL)
    {
        printf("Список пуст.\n");
        return;
    }
    p = L->head;
    while (p != NULL)
    {
        printf("%d. ", i++);
        Print((const Base*)p);
        p = p->next;
    }
}

void PrintType(const List* L, ItemType t)
{
    Item* p;
    int found = 0;
    if (L == NULL) return;
    p = L->head;
    while (p != NULL)
    {
        const Base* b = (const Base*)p;
        if (b->type == t)
        {
            found = 1;
            Print(b);
        }
        p = p->next;
    }
    if (!found) printf("Объекты данного типа не найдены.\n");
}

void Sort(List* L)
{
    int n, i, j;
    Base *a, *b;
    if (L == NULL) return;
    n = Count(L);
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            a = (Base*)GetItem(L, j);
            b = (Base*)GetItem(L, j + 1);
            if (strcmp(a->name, b->name) > 0)
            {
                Insert(L, Remove(L, j + 1), j);
            }
        }
    }
}

static float life_in_years(const Base* p)
{
    const Fish* f;
    if (p->type == itFish)
    {
        f = (const Fish*)p;
        if (f->in_days) return f->life / 365.0f;
    }
    return p->life;
}

void Find(const List* L, float min_val, float max_val)
{
    Item* p;
    int found = 0;
    float years;
    if (L == NULL) return;
    p = L->head;
    while (p != NULL)
    {
        const Base* b = (const Base*)p;
        years = life_in_years(b);
        if (years >= min_val && years <= max_val)
        {
            found = 1;
            Print(b);
        }
        p = p->next;
    }
    if (!found) printf("В заданном диапазоне ничего не найдено.\n");
}