#include "string.hpp"

namespace NHF
{

typedef basic_string::Iterator It;

It::Iterator(const basic_string::Iterator &i) : cell(i.cell)
{
    num = i.num;
}

It &It::operator=(const It &i)
{
    cell = i.cell;
    num = i.num;
    return *this;
}

It & It::operator++()
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
        throw "túl az utolsó utánin";
    }
    else
        num++;
    return *this;
}

It It::operator++(int)
{
    It copy(*this);
    ++(*this);
    return copy;
}

char &It::operator*() const
{
    if (num == 20)
        throw "túl az utolsón";
    return cell->data[num];
}
}

char &It::operator[](unsigned int pos){
    
}