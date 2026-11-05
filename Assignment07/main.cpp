#include "LempelZiv.h"
#include <iostream>
#include <string>

void printSizes(const std::string& label, const std::string& input) {
    std::string encoded = encode(input);
    std::cout << label << ": " << input.size() << " bytes -> "
              << encoded.size() << " bytes\n";
}

int main() {
    std::string repeatedLetter(120, 'a');

    std::string repeatedPhrase;
    for (int i = 0; i < 20; i++) {
        repeatedPhrase += "hello ";
    }

    std::string regularText = "I'm a junior and my suite basketball team is called the Big League Ballers, so obviously we're winning it all this year.";

    printSizes("Repeated letter", repeatedLetter);
    printSizes("Repeated phrase", repeatedPhrase);
    printSizes("Regular text", regularText);

    return 0;
}