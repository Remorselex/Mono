#include <iostream>
#include "src/Containers/Vector/Vector.h"


void fillVector(Vector<int>& vector, int value) {
    for(int i = 1; i <= value; ++i)
        vector.push_back(i);
}


int main() {
    Vector<int> myVector;
    fillVector(myVector, 10);

    Vector<int> newVector = myVector;

    newVector.print();


    return 0;
}
