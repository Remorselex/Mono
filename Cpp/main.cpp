#include <iostream>
#include <Containers/Vector/Vector.h>

void fillVector(Vector& vector, int value) {
    for(int i = 1; i <= value; ++i)
        vector.push_back(i);
}


int main() {
    Vector myVector = Vector(10);
    fillVector(myVector, 55);
    myVector.print();

    myVector.pop_back();

    myVector.print();

    return 0;
}
