#include <iostream>
#include "src/Containers/Vector/Vector.h"


void fillVector(Vector<int> &vector, int value) {
    for (int i = 1; i <= value; ++i)
        vector.push_back(i);
}


int main() {

    Vector<int> myVector;
    fillVector(myVector, 10);

    myVector.print();

    std::cout << myVector.front() << std::endl;

    myVector.front() = 125;

    myVector.print();


    return 0;
}
