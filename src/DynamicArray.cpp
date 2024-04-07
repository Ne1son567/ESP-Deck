#include "DynamicArray.hpp"

DynamicArray::DynamicArray() : capacity(10), size(0), array(new Pillar*[capacity]) 
{
    
}
DynamicArray::~DynamicArray() {
    for (int i = 0; i < size; ++i) {
        delete array[i];
    }
    delete[] array;
}

void DynamicArray::add(const Pillar& pillar) {
    if (size >= capacity) {
       
        capacity *= 2;
        Pillar** newArray = new Pillar*[capacity];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    array[size++] = new Pillar(pillar);
}

void DynamicArray::remove(int index) {
    if (index < 0 || index >= size) {
        return;
    }
    delete array[index];
    for (int i = index; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
    size--;
}

Pillar** DynamicArray::getArray() const {
    return array;
}
int DynamicArray::getSize() const {
    return size;
}