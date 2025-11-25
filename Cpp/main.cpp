#include <iostream>
#include <Containers/Vector/Vector.h>

void fillVector(Vector<int>& vector, int value) {
    for(int i = 1; i <= value; ++i)
        vector.push_back(i);
}


int main() {
    Vector myVector = Vector<int>(10);
    fillVector(myVector, 10);
    myVector.print();
    myVector.insert(0, 1);
    myVector.print();
    myVector.insert(0, 2);
    myVector.print();
    myVector.remove(2);
    myVector.print();
    myVector.remove(1);
    myVector.print();
    std::cout << myVector.front() << std::endl;
    std::cout << myVector.back() << std::endl;


    return 0;
}
