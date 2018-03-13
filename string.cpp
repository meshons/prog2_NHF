#include "string.hpp"

namespace NHF
{

basic_string::Iterator::Iterator(const basic_string::Iterator &i) : cell(i.cell)
{
    num = i.num;
}

basic_string::Iterator &basic_string::Iterator::operator=(const basic_string::Iterator &i)
{
    cell = i.cell;
    num = i.num;
    return *this;
}

basic_string::Iterator &basic_string::Iterator::operator++()
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

typename basic_string::Iterator basic_string::Iterator::operator++(int)
{
    basic_string::Iterator copy(*this);
    ++(*this);
    return copy;
}

char &basic_string::Iterator::operator*() const
{
    if (num == 20)
        throw "túl az utolsón";
    return cell->data[num];
}
}