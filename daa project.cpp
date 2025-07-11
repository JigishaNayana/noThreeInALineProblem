#include <iostream>
#include <vector>

using namespace std;

const int N = 5;  // Change this value for different grid sizes

// To check if three points are collinear using determinant method
bool areCollinear(int x1, int y1, int x2, int y2, int x3, int y3) {
    int det = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
    return det == 0;
}

bool isValid(int grid[N][N]) {
    // Check rows and columns
    for (int i = 0; i < N; ++i) {
        int rowCount = 0;
        int colCount = 0;
        for (int j = 0; j < N; ++j) {
            rowCount += grid[i][j];
            colCount += grid[j][i];
        }
        if (rowCount != 2 || colCount != 2) return false;
    }

    // Gather all cells with ones
    vector<pair<int, int>> ones;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 1) {
                ones.emplace_back(i, j);
            }
        }
    }

    // Check for any three collinear points
    for (size_t i = 0; i < ones.size(); ++i) {
        for (size_t j = i + 1; j < ones.size(); ++j) {
            for (size_t k = j + 1; k < ones.size(); ++k) {
                if (areCollinear(ones[i].first, ones[i].second, ones[j].first, ones[j].second, ones[k].first, ones[k].second)) {
                    return false;
                }
            }
        }
    }

    return true;
}

void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void generateSolutions(int grid[N][N], int row, int col) {
    if (row == N) {
        if (isValid(grid)) {
            printGrid(grid);
        }
        return;
    }

    int nextRow = row;
    int nextCol = col + 1;
    if (nextCol == N) {
        ++nextRow;
        nextCol = 0;
    }

    // Try placing 1 in the current cell
    grid[row][col] = 1;
    generateSolutions(grid, nextRow, nextCol);

    // Backtrack
    grid[row][col] = 0;

    // Try placing 0 in the current cell
    generateSolutions(grid, nextRow, nextCol);
}

int main() {
    int grid[N][N] = {0};

    generateSolutions(grid, 0, 0);

    return 0;
}
