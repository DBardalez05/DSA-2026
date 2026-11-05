#include "AssociativeArray.h"
#include "LempelZiv.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

void testAssociativeArray() {
    AssociativeArray<std::string, int> table(1);

    // In this test the second insert hits the same bucket and triggers a rehash
    table.set("cat", 1);
    table.set("dog", 2);
    assert(table.get("cat").value() == 1);
    assert(table.get("dog").value() == 2);

    // When updating a key should keep the same size
    table.set("cat", 3);
    assert(table.get("cat").value() == 3);
    assert(table.size() == 2);
    assert(table.contains("cat"));

    auto pairs = table.keyValuePairs();
    std::sort(pairs.begin(), pairs.end());
    //The bucket order can vary
    assert(pairs.size() == 2);
    assert(pairs[0].first == "cat" && pairs[0].second == 3);
    assert(pairs[1].first == "dog" && pairs[1].second == 2);

    bool removed = table.remove("cat");
    assert(removed);
    assert(!table.contains("cat"));
    assert(!table.get("cat").has_value());
    assert(table.get("dog").value() == 2);
    assert(table.size() == 1);

    bool removedAgain = table.remove("cat");
    assert(!removedAgain);
}

void testEncoder() {
    // "abaaa" should output (0, 'a'), (0, 'b'), (1, 'a'), then just ID 1.
    std::string encoded = encode("abaaa");
    assert(encoded.size() == 5);
    assert(encoded[0] == 2);  
    // Two padding zeros at the end.
    assert(static_cast<unsigned char>(encoded[1]) == 0b00110000);
    assert(static_cast<unsigned char>(encoded[2]) == 0b10011000);
    assert(static_cast<unsigned char>(encoded[3]) == 0b10010110);
    assert(static_cast<unsigned char>(encoded[4]) == 0b00010100);
}

int main() {
    testAssociativeArray();
    testEncoder();
    std::cout << "All tests passed! :)\n";
    return 0;
}