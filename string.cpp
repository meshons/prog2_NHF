#include "string.hpp"

namespace NHF{



template <typename T>
basic_string<T>::Iterator::Iterator(const basic_string<T>::Iterator& i):cell(i.cell){
    num = i.num;
}

template <typename T>
typename basic_string<T>::Iterator& basic_string<T>::Iterator::operator=(const basic_string<T>::Iterator& i){
    cell = i.cell;
    num = i.num;
    return *this;
}

template <typename T>
typename basic_string<T>::Iterator& basic_string<T>::Iterator::operator++(){
    if(num==19){
        if(cell->next==NULL)num=20;
        else{
            num=0;
            cell=cell->next;
        }
    }else
    if(num==20){
        throw "túl az utolsó utánin";
    }else
    num++;
    return *this;
}

template <typename T>
typename basic_string<T>::Iterator basic_string<T>::Iterator::operator++(int){
    basic_string<T>::Iterator copy(*this);
     ++(*this);
     return copy;
}

template <typename T>
T& basic_string<T>::Iterator::operator*() const{
    if(num==20)throw "túl az utolsón";
    return cell->data[num];
}

}