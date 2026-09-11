#include "Password.h"
#include <cassert>
#include <iostream>

int main()
{
    // Blocked passwords
    assert(!not_common_password("123456"));
    assert(!not_common_password("qwerty"));
    assert(!not_common_password("password"));
    assert(not_common_password("QWERTY"));
    assert(not_common_password("mypassword"));
    assert(not_common_password(""));

    // Length boundaries
    assert(!meets_length_restriction(""));
    assert(!meets_length_restriction(std::string(5, 'a')));
    assert(meets_length_restriction(std::string(6, 'a')));
    assert(meets_length_restriction(std::string(16, 'a')));
    assert(!meets_length_restriction(std::string(17, 'a')));

    // Check if character countig is correct
    assert(count_occurrences_in_string("aaaabbcdef", "bcd") == 4);
    assert(count_occurrences_in_string("aaaa", "aa") == 4);
    assert(count_occurrences_in_string("abc", "xyz") == 0);
    assert(count_occurrences_in_string("", "abc") == 0);
    assert(count_occurrences_in_string("abc", "") == 0);

    // check if all four character types are there
    assert(uses_all_character_classes("Abc12!"));
    assert(!uses_all_character_classes("ABC12!"));
    assert(!uses_all_character_classes("abc12!"));
    assert(!uses_all_character_classes("Abcde!"));
    assert(!uses_all_character_classes("Abc123"));
    assert(!uses_all_character_classes(""));
    assert(!uses_all_character_classes("Abc12 "));
    assert(uses_all_character_classes("Abc12\\"));

    // Combining different rules
    assert(long_enough_or_all_rules("Abc12!"));
    assert(!long_enough_or_all_rules(""));
    assert(!long_enough_or_all_rules("password"));
    assert(!long_enough_or_all_rules("A1!a"));
    assert(!long_enough_or_all_rules("abcdef"));
    assert(!long_enough_or_all_rules(std::string(16, 'a')));
    assert(long_enough_or_all_rules(std::string(17, 'a')));
    assert(long_enough_or_all_rules("Ab1!" + std::string(12, 'a')));

    std::cout << "All password tests passed!\n";
    return 0;
}