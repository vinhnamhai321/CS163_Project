#pragma once
#include <string>
//base mode
const long long base = (long long)1e6 + 1;

//function
long long setIndex(std::wstring s);

//hash-map
struct Table
{
    //constructor
    Table(std::wstring Def, std::wstring KeyWord, Table* pointer) :def(Def), keyWord(KeyWord), pNext(pointer) {};
    std::wstring def, keyWord;
    Table* pNext{};
};
struct HashMap
{
    Table* myTable[1000001]{};
    void push(std::wstring s, std::wstring keyWord);
    void resolveCollision(std::wstring s, std::wstring keyWord, long long idx);
    void clearMap();
    std::wstring search(std::wstring s);
};
