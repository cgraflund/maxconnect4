#pragma once

#include <limits>
#include <vector>
#include "board.hpp"

struct Agent {
    //Agent(Color c) : color(c){};

    Color color;

    void makeBestMove(Board& board, int depth) {
        std::cout << "Beep boop" << std::flush;
        std::vector<std::pair<Board, size_t>> states = board.getPossibleMoves(color);

        // std::cout << "OOGA\n\n\n";
        // for(auto s: states) {
        //     s.first.printBoard();
        // }

        int score;
        int bestScore = -std::numeric_limits<int>::max();;
        size_t bestMove = 0;
        for(auto s: states) {
            score = minimax(s.first, depth, -std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), false);
            std::cout << "." << std::flush;
            if (score > bestScore) {
                bestScore = score;
                
                bestMove = s.second;
            }
        }
        std::cout << "Move found!" << "\n";
        board.playMove(color, bestMove);
    }

    int minimax(Board state, int depth, int alpha, int beta, bool maximize) {
        //std::cout << "Alpha: " << alpha << " Beta: " << beta << std::endl;
        
        if (depth == 0 || state.isFull()) {
            state.evaluateScore();
            //state.printBoard();
            if (color == RED) {
                return state.red_score - state.green_score;
            }
            else {
                return state.green_score - state.red_score;
            }    
            
        }

        Color currentColor;
        if (maximize) {
            currentColor = color;
        } else {
            switch (color) {
                case RED:
                    currentColor = GREEN;
                    break;
                case GREEN:
                    currentColor = RED;
                    break;
                case EMPTY:
                    break;
            }
        }


        std::vector<std::pair<Board, size_t>> states = state.getPossibleMoves(currentColor);
        
        if (maximize) {
            int maxEval = -std::numeric_limits<int>::max();
            for(auto s: states) {
                int eval = minimax(s.first, depth-1, alpha, beta, false);
                if (eval > maxEval) {
                    maxEval = eval;
                }
                if (eval > alpha) {
                    alpha = eval;
                }
                if (beta <= alpha) {
                    break;
                }
            }
            return maxEval;
        }
        else {
            int minEval = std::numeric_limits<int>::max();
            for(auto s: states) {
                int eval = minimax(s.first, depth-1, alpha, beta, true);
                if (eval < minEval) {
                    minEval = eval;
                }
                if (eval < beta) {
                    beta = eval;
                }
                if (beta <= alpha) {
                    break;
                }
            }
            return minEval;
        }
    }
};