#ifndef SUBJ_H
#define SUBJ_H

#include "list.h"

typedef enum ItemType
{
    itNone,
    itPlant,
    itFish,
    itBird,
    itAnimal
} ItemType;

extern const char* const TypeName[];

typedef struct Base
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
} Base;

int input_int(const char* prompt);
float input_float(const char* prompt);
void input_str(const char* prompt, char* str, int size);

Base* Create(ItemType t);
void Input(Base* p);
void Print(const Base* p);
void PrintAll(const List* L);
void PrintType(const List* L, ItemType t);
void Sort(List* L);
void Find(const List* L, float min_val, float max_val);

#endif