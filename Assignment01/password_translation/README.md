# Password Checker (Translating Python to C++)

## Purpose

This program translates my password checker from Software Design Assignment 1 into C++. It takes a password as a string and checks whether it follows the original assignment’s rules.

## Password Rules

The individual functions check whether the password:

* Is different from `"123456"`, `"qwerty"`, and `"password"`.
* Has between 6 and 16 characters, inclusive.
* Contains lowercase letters, uppercase letters, digits, and punctuation.
The combined checker accepts any password longer than 16 characters. Otherwise, the password must pass all three checks above.

## Original Code

The original Python file is [password.py in my Software Design repo](https://github.com/DBardalez05/softdes-2025-01/blob/main/assignments/1-python-basics/password.py).

## Files used

* `Password.h`: Function declarations.
* `Password.cpp`: The translated password-checking functions.
* `tests.cpp`: Unit tests.

## Compiling and Running

Open a terminal inside this folder and compile:

```powershell
g++ -std=c++17 tests.cpp Password.cpp -o tests.exe
```

Then run:

```powershell
.\tests.exe
```

If every test passes, the program should print:

```text
All password tests passed!
```

## Unit Tests

The many tests I did covered blocked passwords, case-sensitive comparisons, lengths around the allowed boundaries, character counting, missing character types, and empty strings. They also check that passwords longer than 16 characters pass the combined checker.

## Translation Experience

The main learning curve was getting used to the C++ syntax. The rest was pretty straightforward since I already had working Python code and understood its logic. That logic stayed the same in C++, so most of the work was translating the syntax rather than figuring out a new approach.