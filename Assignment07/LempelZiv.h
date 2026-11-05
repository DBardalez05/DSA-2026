#pragma once

#include "AssociativeArray.h"
#include <cstddef>
#include <string>

// To keep all of the bit sizes consistent we make the width of all bits the size of out largest bit
int IdWidth(std::size_t largestId){
    int width = 1;
    while (largestId > 1){
        // Since every bit position is to teh power of two by dividing by 2 we account fo one bit position if we get to the value1, we know we are at teh final bit
        largestId /= 2;
        width++;
    }
    return width;
}

// Writes the number into binary 
void AppendBits(std::string& bits, std::size_t number, int width){
    for (int shift = width - 1; shift >= 0; shift--){
        // Based on number shift till we look at the most left important value
        if ((number >> shift) & 1){
        // Move the bit we want to the far right then check if it is a 1
            bits.push_back('1');
        }
        else{
            bits.push_back('0');
        }
    }
}

// Store the padding count first, followed by groups of 8 bits.
std::string PackBits(std::string bits){
    //If the last byte isn't full fill the rest with zeros
    std::size_t padding = (8 - bits.size() % 8) % 8;
    bits.append(padding, '0');

    std::string encoded;
    // Put the count up front so we know how many zeros to skip at the end
    encoded.push_back(static_cast<char>(padding));

    // Grab 8 bits at a time and turn them into one byte
    for (std::size_t i = 0; i < bits.size(); i += 8){
        int byte = 0;
        for (int j = 0; j < 8; j++){
            // Make room on the right and put the next bit there
            byte = byte * 2 + (bits[i + j] - '0');
        }
        encoded.push_back(static_cast<char>(byte));
    }
    return encoded;
}

// Build the dictionary as we go and use it to encode the input
std::string encode(const std::string& input){
    AssociativeArray<std::string, std::size_t> dictionary;
    // Start with no prefix at 0
    dictionary.set("", 0);
    std::size_t nextId = 1;

    std::string prefix;
    std::string bits;

    for (char symbol : input) {
        std::string candidate = prefix + symbol;

        // Try to make it longer if we already know ht ephrase
        if (dictionary.contains(candidate)){
            prefix = candidate;
        } 
        // Write the ID of the part we know, then the character we just added
        else{
            AppendBits(bits, dictionary.get(prefix).value(), IdWidth(nextId - 1));
            AppendBits(bits, static_cast<unsigned char>(symbol), 8);
            // Give the new phrase an ID and start fresh for the next one
            dictionary.set(candidate, nextId);
            nextId++;
            prefix.clear();
        }
    }

    // If there's a known phrase left at the end, just write its ID
    if (!prefix.empty()){
        AppendBits(bits, dictionary.get(prefix).value(), IdWidth(nextId - 1));
    }
    // Pack all the 0s and 1s into actual bytes
    return PackBits(bits);
}