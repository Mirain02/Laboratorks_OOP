#ifndef SUBJ_H
#define SUBJ_H

#include <string>
#include "list.h"

enum ItemType
{
    itNone,
    itPlant,
    itFish,
    itBird,
    itAnimal
};

extern const std::string TypeName[];

int inputInt(const std::string& prompt);
float inputFloat(const std::string& prompt);

class Base : public Item
{
protected:
    ItemType type;
    std::string name;
    std::string area;
    float temp;
    float hum;
    float life;
    float rep_age;

    void InputBase();
    void PrintBase() const;

public:
    Base(ItemType t = itNone);

    ItemType GetType() const;
    const std::string& GetName() const;
    float GetLifeYears() const;

    void Input();
    void Print() const;

    static Base* Create(ItemType t);
};

class SubjList : public List
{
public:
    void Print() const;
    void PrintType(ItemType t) const;
    void Sort();
    void Find(float minVal, float maxVal) const;
};

#endif