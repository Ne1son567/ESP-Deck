#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

#include "games/FlappyBird/Pillar.hpp"

class DynamicArray {
private:
    Pillar** array;
    int size;
    int capacity;

public:
    DynamicArray();
    ~DynamicArray();
    void add(const Pillar& pillar);
    void remove(int index);
    Pillar** getArray() const; // Hinzufügen von 'const' für getArray-Methode
    int getSize() const;
};

#endif
