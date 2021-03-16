#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>

#include "board.hpp"
#include "minimax.hpp"

void humanMakeMove(Board& board, Color humanColor) {
    size_t move = 10;
    while (!board.isValidMove(move)) {
        std::cout << "Enter a valid move: " << std::endl;
        std::cin >> move;
    }
    board.playMove(humanColor, move);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Incorrect number of arguments specified (" << argc << "). 5 arguments are required.\n"
                    << "Interactive: ./maxconnect4 interactive [input_file] [computer-next/human-next] [depth]\n"
                    << "One-move: ./maxconnect4 one-move [input_file] [output_file] [depth]\n";
        return 1;
    }

    std::ifstream fin(argv[2]);

    if (!fin.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    Board board;

    std::string line;

    for (int row = 5; row >= 0; row--) {
        std::getline(fin, line);
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        for (int col = 0; col < 7; col++) {
            board.board[row][col] = (Color)(line[col] - '0');
        }   
        line.clear();
    }    

    std::getline(fin, line);
    Color nextPlayer = (Color)(line[0] - '0');
    Color humanColor;

    Agent ai;
    int depth = std::atoi(argv[4]);

    if (strcmp(argv[1], "interactive") == 0) {

        if(strcmp(argv[3], "computer-next") == 0) {
            board.evaluateScore();
            board.printBoard();

            if (board.isFull()) {
                std::cout << "Game over!" << std::endl;
                return 0;
            }

            ai.color = nextPlayer;
            switch (ai.color) {
                case (RED):
                    humanColor = GREEN;
                    break;
                case (GREEN):
                    humanColor = RED;
                    break;
                case (EMPTY):
                    break;
            }

            // AI Chooses
            ai.makeBestMove(board, depth);

            board.filePrintBoard(humanColor, "computer.txt");
        }
        else if(strcmp(argv[3], "human-next") == 0) {    
            humanColor = nextPlayer;
            switch (nextPlayer) {
                case (RED):
                    ai.color = GREEN;
                    break;
                case (GREEN):
                    ai.color = RED;
                    break;
                case (EMPTY):
                    break;
            }
        }
        else {
            std::cerr << "Invalid next-player argument." << std::endl;
            return 1;
        }

        board.evaluateScore();
        board.printBoard();

        if (board.isFull()) {
            std::cout << "Game over!" << std::endl;
            return 0;
        }

        humanMakeMove(board, humanColor);
        board.filePrintBoard(ai.color, "human.txt");     

        while(true) {
            board.evaluateScore();
            board.printBoard();

            if (board.isFull()) {
                std::cout << "Game over!" << std::endl;
                return 0;
            }

            ai.makeBestMove(board, depth);

            board.filePrintBoard(humanColor, "computer.txt");

            board.evaluateScore();
            board.printBoard();

            if (board.isFull()) {
                std::cout << "Game over!" << std::endl;
                return 0;
            }

            humanMakeMove(board, humanColor);

            board.filePrintBoard(ai.color, "human.txt");
        }

    }
    else if (strcmp(argv[1], "one-move") == 0) {
        board.evaluateScore();
        board.printBoard();

        if (board.isFull()) {
            std::cout << "Game over!" << std::endl;
            return 0;
        }

        ai.color = nextPlayer;
            switch (ai.color) {
                case (RED):
                    humanColor = GREEN;
                    break;
                case (GREEN):
                    humanColor = RED;
                    break;
                case (EMPTY):
                    break;
            }

        ai.makeBestMove(board, depth);
        board.filePrintBoard(humanColor, argv[3]);

        board.evaluateScore();
        board.printBoard();

        if (board.isFull()) {
            std::cout << "Game over!" << std::endl;
            return 0;
        }
    }
    else {
        std::cerr << "Invalid game mode argument." << std::endl;
        return 1;
    }

    return 0;
}