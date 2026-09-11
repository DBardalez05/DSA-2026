#pragma once
#include <cstddef>
#include <string>

// Prevents usign a blocked password
bool not_common_password(const std::string& password);

// Checks if password is long enough
bool meets_length_restriction(const std::string& password);

// Count target characters that belong to characters_to_count.
int count_occurrences_in_string(const std::string& target, const std::string& characters_to_count);

// Check for certain character types
bool uses_all_character_classes(const std::string& password);

// EIther the passwrod is long enough or the other three tests are good
bool long_enough_or_all_rules(const std::string& password);