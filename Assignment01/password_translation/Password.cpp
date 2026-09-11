#include "Password.h"

const std::string ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
const std::string ascii_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string digits = "0123456789";
const std::string punctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

bool not_common_password(const std::string& password)
{
    if (password == "123456" || password == "password" || password == "qwerty")
    {
        return false;
    }
    return true;
}

bool meets_length_restriction(const std::string& password)
{
    return password.size() >= 6 && password.size() <= 16;
}

int count_occurrences_in_string(const std::string& target,const std::string& characters_to_count)
{
    int occurrences = 0;

    for (char character : target)
    {
        if (characters_to_count.find(character) != std::string::npos)
        {
            occurrences++;
        }
    }

    return occurrences;
}

bool uses_all_character_classes(const std::string& password)
{
    const auto lowercase_count = count_occurrences_in_string(password, ascii_lowercase);
    const auto uppercase_count = count_occurrences_in_string(password, ascii_uppercase);
    const auto digits_count = count_occurrences_in_string(password, digits);
    const auto punctuation_count = count_occurrences_in_string(password, punctuation);

    return lowercase_count >= 1 && uppercase_count >= 1 && digits_count >= 1 && punctuation_count >= 1;
}

bool long_enough_or_all_rules(const std::string& password)
{
    if (password.size() > 16)
    {
        return true;
    }

    return not_common_password(password) && meets_length_restriction(password) && uses_all_character_classes(password);
}