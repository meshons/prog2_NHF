#include "string.hpp"

namespace NHF
{

typedef String::Iterator It;

inline static void copy(char *to, char *from)
{
    for (int i = 0; i < 20; i++)
        to[i] = from[i];
}

String::String()
{
    first = NULL;
}

String::String(const String &s)
{
    Cell *tmp, *c, *prev = NULL;
    if (s.first != NULL)
    {
        first = new Cell();
        tmp = first;
        copy(tmp->data, s.first->data);
        tmp->prev = NULL;
        tmp->next = NULL;
        prev = tmp;
        for (c = s.first->next; c != NULL; c = c->next)
        {
            tmp->next = new Cell();
            tmp = tmp->next;
            copy(tmp->data, c->data);
            tmp->prev = prev;
            tmp->next = NULL;
        }
    }
    else
        first = NULL;
}

String::String(const char *str)
{
    Cell *tmp = first, *prev = NULL;
    unsigned int x = 0;
    while (str[x])
    {
        if (x % 20 == 0)
        {
            if (!x)
            {
                first = new Cell();
                tmp = first;
            }
            else
            {
                prev = tmp;
                tmp->next = new Cell();
                tmp = tmp->next;
            }
            tmp->prev = prev;
            tmp->next = NULL;
        }
        tmp->data[x % 20] = str[x];
        x++;
    }
}
String::String(It begin, It end)
{
    Cell *tmp = first, *prev = NULL;
    unsigned int x = 0;
    while (&(*begin) != &(*end))
    {
        if (x % 20 == 0)
        {
            if (!x)
                first = new Cell();
            else
            {
                prev = tmp;
                tmp->next = new Cell();
                tmp = tmp->next;
            }
            tmp->prev = prev;
            tmp->next = NULL;
        }
        tmp->data[x % 20] = *begin;
        begin++;
        x++;
    }
}

String::~String()
{
    Cell *tmp = first;
    while (first != NULL)
    {
        tmp = first->next;
        delete first;
        first = tmp;
    }
}

String& String::operator=(const String & s){
    clear();
    Cell *tmp, *c, *prev = NULL;
    if (s.first != NULL)
    {
        first = new Cell();
        tmp = first;
        copy(tmp->data, s.first->data);
        tmp->prev = NULL;
        tmp->next = NULL;
        prev = tmp;
        for (c = s.first->next; c != NULL; c = c->next)
        {
            tmp->next = new Cell();
            tmp = tmp->next;
            copy(tmp->data, c->data);
            tmp->prev = prev;
            tmp->next = NULL;
        }
    }
    else
        first = NULL;
    return *this;
}
String& String::operator=(const char * str){
    clear();
    Cell *tmp = first, *prev = NULL;
    unsigned int x = 0;
    while (str[x])
    {
        if (x % 20 == 0)
        {
            if (!x)
            {
                first = new Cell();
                tmp = first;
            }
            else
            {
                prev = tmp;
                tmp->next = new Cell();
                tmp = tmp->next;
            }
            tmp->prev = prev;
            tmp->next = NULL;
        }
        tmp->data[x % 20] = str[x];
        x++;
    }
    return *this;
}
String& String::operator=(char c){
    clear();
    first = new Cell();
    first->prev=NULL;
    first->next=NULL;
    first->data[0]=c;
    first->data[1]=0;
    return *this;
}

It String::begin()
{
    return It(first);
}
const It String::begin() const
{
    return It(first);
}
It String::end()
{
    It a(first);
    while (*a != 0)
        a++;
    return a;
}
const It String::end() const
{
    It a(first);
    while (*a != 0)
        a++;
    return a;
}

size_t String::size() const
{
    size_t sum = 0;
    for (Cell *tmp = first; tmp != NULL; tmp = tmp->next)
    {
        int x = 0;
        while (tmp->data[x] && x < 20)
            x++;
        sum += x;
    }
    return sum;
}
size_t String::length() const
{
    size_t sum = 0;
    for (Cell *tmp = first; tmp != NULL; tmp = tmp->next)
    {
        int x = 0;
        while (tmp->data[x] && x < 20)
            x++;
        sum += x;
    }
    return sum;
}
size_t String::capacity() const
{
    size_t sum = 0;
    for (Cell *tmp = first; tmp != NULL; tmp = tmp->next)
        sum++;
    return sum * 20;
}
void String::clear()
{
    Cell *tmp = first;
    while (first != NULL)
    {
        tmp = first->next;
        delete first;
        first = tmp;
    }
    first = NULL;
}
bool String::empty() const
{
    return length() == 0;
}

It::Iterator(const It &i) : cell(i.cell)
{
    num = i.num;
}

It &It::operator=(const It &i)
{
    cell = i.cell;
    num = i.num;
    return *this;
}

It &It::operator++()
{
    if (num == 19)
    {
        if (cell->next == NULL)
            num = 20;
        else
        {
            num = 0;
            cell = cell->next;
        }
    }
    else if (num == 20)
    {
        if (cell->next == NULL)
            throw "túl az utolsó utánin";
        else
        {
            cell = cell->next;
            num = 0;
        }
    }
    else
        num++;
    return *this;
}

It It::operator++(int)
{
    It tmp(*this);
    ++(*this);
    return tmp;
}

char &It::operator*() const
{
    if (num == 20)
        throw "túl az utolsón";
    return cell->data[num];
}

/*char &It::operator[](unsigned int pos)
{
    return 
}*/
}