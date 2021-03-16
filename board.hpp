#pragma once

#include <vector>
#include <iostream>
#include <array>

enum Color {EMPTY, RED, GREEN};

struct Board {
    static constexpr std::size_t height = 6;
    static constexpr std::size_t length = 7;
    std::array<std::array<Color, length>, height> board {{
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    }};

    int red_score = 0;
    int green_score = 0;

    void printBoard() {
        for (auto row = board.rbegin(); row != board.rend(); ++row) {
            for (auto const& value : *row) {
                switch (value) {
                    case EMPTY:
                        std::cout << ". ";
                        break;
                    case RED:
                        std::cout << "R ";
                        break;
                    case GREEN:
                        std::cout << "G ";
                        break;
                } 
            }
            std::cout << std::endl;
        }
        std::cout << "Red: " << red_score << "\t Green: " << green_score << "\n";
    }

    void filePrintBoard(Color nextPlayer, const char* fileName) {
        std::ofstream file;
        file.open(fileName);
        
        for (auto row = board.rbegin(); row != board.rend(); ++row) {
            for (auto const& value : *row) {
                switch (value) {
                    case EMPTY:
                        file << "0";
                        break;
                    case RED:
                        file << "1";
                        break;
                    case GREEN:
                        file << "2";
                        break;
                } 
            }
            file << std::endl;
        }
        switch (nextPlayer) {
                    case EMPTY:
                        file << "0";
                        break;
                    case RED:
                        file << "1";
                        break;
                    case GREEN:
                        file << "2";
                        break;
                } 
    }

    bool isValidMove(size_t col) {
        if (col < length && board[height-1][col] == EMPTY) {
            return true;
        }
        return false;
    }

    std::vector<std::pair<Board, size_t>> getPossibleMoves(Color player) {
        std::vector<std::pair<Board, size_t>> states;
        for (size_t col = 0; col < length; col++) {
            if (board[height-1][col] == EMPTY) {
                Board new_state = *this;
                new_state.playMove(player, col);
                states.push_back(std::make_pair(new_state, col));
            }
        }
        return states;
    }

    void playMove(Color player, size_t col) {
        for (size_t row = 0; row < height; row++) {
            if (board[row][col] == EMPTY) {
                board[row][col] = player;
                return;
            }
        }
    }

    bool isFull() {
        for (auto row = board.rbegin(); row != board.rend(); ++row) {
            for (auto const& value : *row) {
                if (value == EMPTY) {
                    return false;
                }
            }
        }
        return true;
    }

    void evaluateScore() {
        red_score = 0;
        green_score = 0;

        // Horizontal
        for (size_t row = 0; row < height; row++) {
            for (size_t col = 0; col < 4; col++) {
                if (isRow4(row, col)) {
                    switch (board[row][col]) {
                        case EMPTY:
                            break;
                        case RED:
                            ++red_score;
                            break;
                        case GREEN:
                            ++green_score;
                            break;
                    } 
                }
            }
        }

        // Vertical
        for (size_t row = 0; row < 3; row++) {
            for (size_t col = 0; col < length; col++) {
                if (isCol4(row, col)) {
                    switch (board[row][col]) {
                        case EMPTY:
                            break;
                        case RED:
                            ++red_score;
                            break;
                        case GREEN:
                            ++green_score;
                            break;
                    } 
                }
            }
        }

        // Forward Diagonal
        for (size_t row = 0; row < 3; row++) {
            for (size_t col = 0; col < 4; col++) {
                if (isForwardDiag4(row, col)) {
                    switch (board[row][col]) {
                        case EMPTY:
                            break;
                        case RED:
                            ++red_score;
                            break;
                        case GREEN:
                            ++green_score;
                            break;
                    } 
                }
            }
        }

        // Backward Diagonal
        for (size_t row = 3; row < height; row++) {
            for (size_t col = 0; col < 4; col++) {
                if (isBackwardDiag4(row, col)) {
                    switch (board[row][col]) {
                        case EMPTY:
                            break;
                        case RED:
                            ++red_score;
                            break;
                        case GREEN:
                            ++green_score;
                            break;
                    } 
                }
            }
        }
    }

    // Returns true if the current slot and the 3 to the right match colors
    bool isRow4(size_t row, size_t col) {
        Color player = board[row][col];
        for (size_t i = 1; i < 4; i++) {
            if (board[row][col+i] != player) {
                return false;
            }
        }
        return true;
    }

    // Returns true if the current slot and the 3 above match colors
    bool isCol4(size_t row, size_t col) {
        Color player = board[row][col];
        for (size_t i = 1; i < 4; i++) {
            if (board[row+i][col] != player) {
                return false;
            }
        }
        return true;
    }

    // Returns true if the current slot the 3 to the right and up match colors
    bool isForwardDiag4(size_t row, size_t col) {
        Color player = board[row][col];
        for (size_t i = 1; i < 4; i++) {
            if (board[row+i][col+i] != player) {
                return false;
            }
        }
        return true;
    }

    // Returns true if the current slot the 3 to the right and down match colors
    bool isBackwardDiag4(size_t row, size_t col) {
        Color player = board[row][col];
        for (size_t i = 1; i < 4; i++) {
            if (board[row-i][col+i] != player) {
                return false;
            }
        }
        return true;
    }
};