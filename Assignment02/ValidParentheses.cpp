#include "ValidParentheses.h"
#include "Stack.h"


/** Checks whether the brackets in s are correctly paired and nested.
 * @param s The string to check.
 * @return true if every bracket matches, false otherwise.
 */
bool isValidParentheses(const std::string& s) {
    Stack<char> openings{};

    for (char c : s) {
        if (c == '{' || c == '[' || c == '(') {
            openings.push(c);//per opening parenthesis we add to the stack
        } else if (c == '}' || c == ']' || c == ')') {
            if (openings.isEmpty()) return false;//Chech first fail instance if no opening bracket availible for current cloding bracket

            std::string combo;//makes a current string of opening parenthesis on top of stack and current closing parenthesis we are on.
            combo += openings.peek().value();
            combo += c;

            if (combo == "{}" || combo == "[]" || combo == "()") {
                openings.pop();//remove the opening parenthesis from the stack if it has a correct closing parenthesis in the correct order
            } else {
                return false;
            }
        }
    }

    return openings.isEmpty();//If gone through all characters in string and no characters left in the stack that means all opening parenthesis found their correct closing parenthesis.
}