#pragma once
#include <string>
#include <vector>
#include <algorithm>

// create object that has both of the strings but now aligned and also has the alignent score value
struct AlignmentResult {
    std::string firstAligned;
    std::string secondAligned;
    int score = 0;
};

AlignmentResult needlemanWunsch(std::string first, std::string second) {
    //values for three three possible conditions as we go down the string in the table
    int matchScore = 1;
    int mismatchScore = -1;
    int gapScore = -1;

    //+1 due to when one string has no letters yet
    int rows = first.size() + 1;
    int columns = second.size() + 1;

    //create the score table (rox x columns size)
    std::vector<std::vector<int>> table;
    for (int r = 0; r < rows; r++) {
        std::vector<int> newRow(columns, 0);
        table.push_back(newRow);
    }

    //align each prefix with an empty string using gaps
    for (int r = 0; r < rows; r++) {
        table[r][0] = r * gapScore;
    }

    for (int c = 0; c < columns; c++) {
        table[0][c] = c * gapScore;
    }

    //fill the remaining cells using the best of three choices
    //so since we start filling out table abfter previous step, we will have teh three numbers to compare to for each condiiotn of up left or diagonal
    for (int r = 1; r < rows; r++) {
        for (int c = 1; c < columns; c++) {
            int pairScore = mismatchScore;
            if (first[r - 1] == second[c - 1]) {
                pairScore = matchScore;
            }

            int diagonal = table[r - 1][c - 1] + pairScore;
            int up = table[r - 1][c] + gapScore;
            int left = table[r][c - 1] + gapScore;

            //current score for new entry is based on which outcome gives highest value
            table[r][c] = std::max({diagonal, up, left});
        }
    }

    //start backtracking at the bottom-right cell
    AlignmentResult result;
    int r = rows - 1;
    int c = columns - 1;
    result.score = table[r][c];

    //we first assume that the diagonal is a mismatch then if it isnt then we chagne the value to +1
    //we then go throuhg eahc of the three scenarios to check for which scenario is the one that led us to teh current number we are at based on that we edit both strigns.
    while (r > 0 || c > 0) {
        int pairScore = mismatchScore;
        if (r > 0 && c > 0 && first[r - 1] == second[c - 1]) {
            pairScore = matchScore;
        }

        // Diagonal: pair a letter from each string.
        if (r > 0 && c > 0 && table[r][c] == table[r - 1][c - 1] + pairScore) {
            result.firstAligned.push_back(first[r - 1]);
            result.secondAligned.push_back(second[c - 1]);
            r--;
            c--;
        }
        // Up: pair a letter from the first string with a gap.
        else if (r > 0 && table[r][c] == table[r - 1][c] + gapScore) {
            result.firstAligned.push_back(first[r - 1]);
            result.secondAligned.push_back('-');
            r--;
        }
        // Left: pair a gap with a letter from the second string.
        else {
            result.firstAligned.push_back('-');
            result.secondAligned.push_back(second[c - 1]);
            c--;
        }
    }

    //backtracking collected both answers backward so we then must reverse it
    std::reverse(result.firstAligned.begin(), result.firstAligned.end());
    std::reverse(result.secondAligned.begin(), result.secondAligned.end());

    return result;
}

