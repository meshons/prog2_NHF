#include "f12.h"

const char * F2::myId = "Stork Gabor,1MI,IMSC3,L3p <storkgaborka98@gmail.com> NO047V";

double F2::f(double szam) const
{
    double eredmeny;
    if (szam > 14)
        eredmeny = szam / 99.65;
    else
    {
        eredmeny = 0.389 * szam * szam * szam * szam;
        eredmeny -= 0.777 * szam * szam * szam;
        eredmeny += 49.75 * szam * szam;
        eredmeny += 14 * szam;
        eredmeny -= 14.0;
    }
    return eredmeny;
}

Queue::Queue(const char *p)
{
    if(p)
    for (int i = 0; p[i]; i++)
        q.push_back(p[i]);
    //q.push_back(0);
}

char Queue::pop_back()
{
    if (q.empty())
        throw std::underflow_error("Empty");
    char t = q.back();
    q.pop_back();
    return t;
}

void Queue::push_front(const char c)
{
    q.push_front(c);
}

char Queue::pop_front()
{
    if (q.empty())
        throw std::underflow_error("Empty");
    char t = q.front();
    q.pop_front();
    return t;
}

bool Queue::empty()
{
    return q.empty();
}

Queue::myIterator Queue::begin()
{
    return q.begin();
}

Queue::myIterator Queue::end()
{
    return q.end();
}