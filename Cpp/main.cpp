#include <iostream>
#include "src/Containers/Vector/Vector.h"


void fillVector(Vector<int>& vector, int value) {
    for(int i = 1; i <= value; ++i)
        vector.push_back(i);
}


int main() {
    Vector myVector = Vector<int>(10);
    fillVector(myVector, 10);



    return 0;
}
