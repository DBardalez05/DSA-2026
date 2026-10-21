#pragma once
#include <vector>
#include <optional>

struct Matrix {
    int n = 0;
    std::vector<std::vector<double>> data;

    Matrix(int size) {
        n = size;
        //make matrix that is nxn size full of zeros to begin
        for (int row = 0; row < n; row++){
            std::vector<double> newRow(n,0.0);
            data.push_back(newRow);
        }
    
    }

    //set: Will change a cell's value. Return false if its indexes are out of range
    bool set(int row, int column, double value) {
        if((row >= n || column >= n) || (row < 0 || column < 0)){
            return false;
        }
        else{
            data[row][column] = value;
        }
        return true;
    }

    //get: Will return a cell's value, or std::nullopt if its indexes are out of range
    std::optional<double> get(int row, int column) {
        if((row >= n || column >= n) || (row < 0 || column < 0)){
        return std::nullopt;
        }
        else{
        return data[row][column];
        }
    }

    // getBlock: Copy a square block starting at the given row and column. Return std::nullopt if the block cannot be extracted
    std::optional<Matrix> getBlock(int s_row, int s_column, int b_size){
        if (b_size > n || b_size <= 0){
            return std::nullopt;
        }
        Matrix smallMatrix(b_size);
        for(int r = 0; r < b_size; r++){
            for (int c = 0; c < b_size; c++){
                std::optional<double> fetched_value = get(s_row + r, s_column + c);
                //we fetch values and add it to the smaller matrix
                if (fetched_value.has_value()){
                    double temp_num = fetched_value.value();
                    smallMatrix.set(r,c,temp_num);
                }
                else{
                    return std::nullopt;
                }
            }
        }
        return smallMatrix;
    }

    // add: Returns the sum of both matrices
    // Return std::nullopt if their sizes differ
    std::optional<Matrix> add(Matrix& other) {
        if (n != other.n) {
            return std::nullopt;
        }

        Matrix result(n);

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                double first = get(r, c).value();
                double second = other.get(r, c).value();

                result.set(r, c, first + second);
            }
        }

        return result;
    }

    // subtract: Return this matrix minus the other matrix
    // Return std::nullopt if their sizes differ
    std::optional<Matrix> subtract(Matrix& other) {
        if (n != other.n) {
            return std::nullopt;
        }

        Matrix result(n);

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                double first = get(r, c).value();
                double second = other.get(r, c).value();

                result.set(r, c, first - second);
            }
        }

        return result;
    }

    //putBlock: Copy another matrix into this matrix at the given position
    //Return false if the block does not fit
    bool putBlock(int s_row, int s_column, Matrix& block) {
        //first check that index are not negative
        if (s_row < 0 || s_column < 0) {
            return false;
        }
        if (block.n <= 0 || block.n > n) {
            return false;
        }

        //Check that the whole block actually fits
        if (s_row > n - block.n || s_column > n - block.n) {
            return false;
        }

        for (int r = 0; r < block.n; r++) {
            for (int c = 0; c < block.n; c++) {
                double value = block.get(r, c).value();
                set(s_row + r, s_column + c, value);
            }
        }

        return true;
    }

    // multiply: Return the product of two matrix using regular matrix multiplication
    // Return std::nullopt if their sizes differ
    std::optional<Matrix> multiply(Matrix& other) {
        if (n != other.n) {
            return std::nullopt;
        }

        Matrix result(n);

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                double total = 0.0;

                for (int k = 0; k < n; k++) {
                    double first = get(r, k).value();
                    double second = other.get(k, c).value();

                    total += first * second;
                }

                result.set(r, c, total);
            }
        }

        return result;
    }

    // strassenMultiply: Return the product using Strassen's algorithm
    // we swtich to regular multiplication when the block size is at or below the cutoff
    // Return std::nullopt for incompatible sizes or an invalid cutoff
    std::optional<Matrix> strassenMultiply(Matrix& other, int cutoff = 1) {
        if (n != other.n || n < 0 || cutoff < 1) {
            return std::nullopt;
        }

        //ordinary multiplication at cut off
        if (n <= cutoff) {
            return multiply(other);
        }

        //find the next power of two.
        int paddedSize = 1;
        while (paddedSize < n) {
            paddedSize *= 2;
        }

        //if needed, copy both inputs into larger zero-filled matrices so taht they become same size
        if (paddedSize != n) {
            Matrix paddedA(paddedSize);
            Matrix paddedB(paddedSize);

            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    paddedA.set(r, c, get(r, c).value());
                    paddedB.set(r, c, other.get(r, c).value());
                }
            }

            Matrix paddedResult =
                paddedA.strassenMultiply(paddedB, cutoff).value();

            //remove the extra padded rows and columns.
            return paddedResult.getBlock(0, 0, n);
        }

        //we then split both inputs into four quadrants
        int half = n / 2;

        Matrix A11 = getBlock(0, 0, half).value();
        Matrix A12 = getBlock(0, half, half).value();
        Matrix A21 = getBlock(half, 0, half).value();
        Matrix A22 = getBlock(half, half, half).value();

        Matrix B11 = other.getBlock(0, 0, half).value();
        Matrix B12 = other.getBlock(0, half, half).value();
        Matrix B21 = other.getBlock(half, 0, half).value();
        Matrix B22 = other.getBlock(half, half, half).value();

        //all of the 7 equations needed for this algorithm
        //M1 = (A11 + A22) * (B11 + B22)
        Matrix left = A11.add(A22).value();
        Matrix right = B11.add(B22).value();
        Matrix M1 = left.strassenMultiply(right, cutoff).value();
        //M2 = (A21 + A22) * B11
        left = A21.add(A22).value();
        Matrix M2 = left.strassenMultiply(B11, cutoff).value();
        //M3 = A11 * (B12 - B22)
        right = B12.subtract(B22).value();
        Matrix M3 = A11.strassenMultiply(right, cutoff).value();
        //M4 = A22 * (B21 - B11)
        right = B21.subtract(B11).value();
        Matrix M4 = A22.strassenMultiply(right, cutoff).value();
        //M5 = (A11 + A12) * B22
        left = A11.add(A12).value();
        Matrix M5 = left.strassenMultiply(B22, cutoff).value();
        //M6 = (A21 - A11) * (B11 + B12)
        left = A21.subtract(A11).value();
        right = B11.add(B12).value();
        Matrix M6 = left.strassenMultiply(right, cutoff).value();
        //M7 = (A12 - A22) * (B21 + B22)
        left = A12.subtract(A22).value();
        right = B21.add(B22).value();
        Matrix M7 = left.strassenMultiply(right, cutoff).value();
        //Top-left answer quadrant would be M1 + M4 - M5 + M7
        Matrix C11 = M1.add(M4).value();
        C11 = C11.subtract(M5).value();
        C11 = C11.add(M7).value();
        //Top-right answer quadrant is M3 + M5
        Matrix C12 = M3.add(M5).value();
        // Bottom-left answer quadrant is M2 + M4
        Matrix C21 = M2.add(M4).value();
        // Bottom-right answer quadrant is M1 - M2 + M3 + M6
        Matrix C22 = M1.subtract(M2).value();
        C22 = C22.add(M3).value();
        C22 = C22.add(M6).value();

        //finally place the four quadrants into the complete answer.
        Matrix result(n);
        result.putBlock(0, 0, C11);
        result.putBlock(0, half, C12);
        result.putBlock(half, 0, C21);
        result.putBlock(half, half, C22);

        return result;
    }

};

