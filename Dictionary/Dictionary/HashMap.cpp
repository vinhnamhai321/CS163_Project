#include "HashMap.h"
#include "Trie.h"

long long setIndex(std::wstring s) {
    size_t len = s.length();
    long long ans = (long long)(s[0]) % base;
    for (int i = 1; i < len; ++i)
    {
        ans = ((ans * 26) % base + (long long)(s[i]) % base) % base;
    }
    return ans;
}

void HashMap::push(std::wstring s, std::wstring keyWord)
{
    long long idx = setIndex(s);
    if (!myTable[idx])
        myTable[idx] = new Table(s, keyWord, nullptr);
    else
        resolveCollision(s, keyWord, idx);
}

void HashMap::resolveCollision(std::wstring s, std::wstring keyWord, long long idx)
{
    Table* tmp = myTable[idx];
    myTable[idx] = new Table(s, keyWord, tmp);
}

std::wstring HashMap::search(std::wstring s)
{
    long long idx = setIndex(s);
    for (Table* cur = myTable[idx]; cur; cur = cur->pNext)
    {
        if (s.compare(cur->def) == 0)
            return cur->keyWord;
    }
    return L" ";
}

void HashMap::clearMap()
{
    for (int i = 0; i < 1000001; ++i)
    {
        while (myTable[i])
        {
            Table* tmp = myTable[i]->pNext;
            delete myTable[i];
            myTable[i] = tmp;
        }
    }
}