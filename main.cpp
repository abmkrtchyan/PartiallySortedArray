#include <iostream>
#include "PartiallySortedArray.h"

int main() {
    PartiallySortedArray<int> array1;
    array1.insert(8);
    array1.insert(-1);
    array1.insert(-3);
    array1.insert(0);
    array1.insert(0);
    array1.insert(6);
    std::cout << "Array 1: ";
    for (auto it: array1) {
        std::cout << it << "  ";
    }
    std::cout << "\n";

    PartiallySortedArray<int> array2;
    array2.insert(9);
    array2.insert(-3);
    array2.insert(-8);
    array2.insert(0);
    array2.insert(0);
    array2.insert(-6);
    array2.insert(62);
    std::cout << "Array 2: ";
    for (auto it: array2) {
        std::cout << it << "  ";
    }
    std::cout << "\n";
    std::vector<int> result(array1.getSize() + array2.getSize());
    merge(array1.begin(), array1.end(), array2.begin(), array2.end(), result.begin());
    std::cout << "Merged array: ";
    for (auto it: result) {
        std::cout << it << "  ";
    }
    std::cout << "\n";
    return 0;
}
