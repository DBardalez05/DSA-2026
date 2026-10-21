#include "Matrix.h"
#include "SequenceAlignment.h"
#include <cassert>
#include <iostream>
#include <string>

//check the same answer with regular multiplication and Strassen
void checkProduct(Matrix first, Matrix second, Matrix expected) {
    assert(first.multiply(second).value().data == expected.data);
    assert(first.strassenMultiply(second, 1).value().data == expected.data);
    assert(first.strassenMultiply(second, 2).value().data == expected.data);
}

//check the aligned strings and their score
void checkAlignment(std::string first, std::string second,
                    std::string expectedFirst, std::string expectedSecond,
                    int expectedScore) {
    auto result = needlemanWunsch(first, second);

    assert(result.firstAligned == expectedFirst);
    assert(result.secondAligned == expectedSecond);
    assert(result.score == expectedScore);
}

int main() {
    // check that matrix is made and ispossible to get and set values
    Matrix first(2);
    assert(first.n == 2);
    assert(first.get(0, 0).value() == 0.0);
    assert(first.set(0, 1, 7.0));
    assert(first.get(0, 1).value() == 7.0);

    // check when given invalid index
    assert(!first.set(2, 0, 5.0));
    assert(!first.get(-1, 0).has_value());
    first.data = {{1, 2}, {3, 4}};
    Matrix second(2);
    second.data = {{5, 6}, {7, 8}};

    //be ableto extract block and place it in matrix
    Matrix block = first.getBlock(0, 1, 1).value();
    assert(block.n == 1);
    assert(block.get(0, 0).value() == 2);
    Matrix larger(3);
    assert(larger.putBlock(1, 1, first));
    assert(larger.get(1, 1).value() == 1);
    assert(larger.get(2, 2).value() == 4);

    //reject blocks that cannot fit
    assert(!first.getBlock(1, 1, 2).has_value());
    assert(!larger.putBlock(2, 2, first));

    //check tha taddition and subtraction work
    Matrix expected(2);
    expected.data = {{6, 8}, {10, 12}};
    assert(first.add(second).value().data == expected.data);
    expected.data = {{-4, -4}, {-4, -4}};
    assert(first.subtract(second).value().data == expected.data);

    //test with a 2x2 matrix
    expected.data = {{19, 22}, {43, 50}};
    checkProduct(first, second, expected);

    //use a 3x3 to check Strassen
    Matrix biggerFirst(3);
    Matrix biggerSecond(3);
    Matrix biggerExpected(3);
    biggerFirst.data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    biggerSecond.data = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    biggerExpected.data = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    checkProduct(biggerFirst, biggerSecond, biggerExpected);

    //check when given 2 matrix of different sizes to multiply
    assert(!first.multiply(biggerFirst).has_value());
    assert(!first.strassenMultiply(biggerFirst).has_value());

    //String alignment section
    //check alignment with matching strings and a mismatch
    checkAlignment("ACGT", "ACGT", "ACGT", "ACGT", 4);
    checkAlignment("A", "G", "A", "G", -1);

    //test for string with a gap
    checkAlignment("AGC", "AC", "AGC", "A-C", 1);
    checkAlignment("AC", "AGC", "A-C", "AGC", 1);

    //test with empty input
    checkAlignment("", "AC", "--", "AC", -2);
    checkAlignment("AC", "", "AC", "--", -2);

    std::cout << "All tests passed!\n";
    return 0;
}