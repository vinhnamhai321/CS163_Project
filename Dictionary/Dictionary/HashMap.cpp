#include "HashMap.h"
long long setIndex(std::wstring s) {
    int len = s.length();
    long long prev = (long long)getIndex(s[0]);
    long long ans = prev;
    for (int i = 1; i < len; ++i) ans = (prev * 26 + (long long)getIndex(s[i]) % base);
    return ans;
}

void HashMap::push(std::wstring s, std::wstring keyWord)
{
    int idx = setIndex(s);
    if (!myTable[idx])
        myTable[idx] = new Table(s, keyWord, nullptr);
    else
        resolveCollision(s, keyWord, idx);
}

void HashMap::resolveCollision(std::wstring s, std::wstring keyWord, int idx)
{
    Table* tmp = myTable[idx];
    myTable[idx] = new Table(s, keyWord, tmp);
}

std::wstring HashMap::search(std::wstring s)
{
    int idx = setIndex(s);
    for (Table* cur = myTable[idx]; cur; cur = cur->pNext)
    {
        if (s.compare(cur->def) == 0)
            return cur->keyWord;
    }
    return L" ";
}