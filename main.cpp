#include "solitaireBoard.hpp"
#include <iostream>
#include <vector>
#include <limits>

void processInput();

int main() {
    SolitaireBoard game = SolitaireBoard();
    std::string userInput;
    while (game.gameComplete() == false) {
        game.printBoard();
        userInput = "";
        std::cout << "What move would you like to do (deck, move): ";
        std::cin >> userInput;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        int pile;

        try {
            if (userInput.compare("deck") == 0) {
                game.traverseDeck();
            } else if (userInput.compare("quit") == 0) {
                return 0;
            } else if (userInput.find("->") != std::string::npos) {
                pile = game.searchBoard(userInput.at(0), userInput.at(1));
                if (pile == -2) {
                    throw -1;
                } else if (pile == -1) {
                    throw -2;
                } else if (pile == 0) {
                    if ((userInput.at(12) - '0') > 0 && (userInput.at(12) - '0' < 8)) {
                        game.deckToPile(userInput.at(12));
                    } else {throw -1;}
                } else if (pile > 0 && pile < 8) {
                    if ((userInput.at(12) - '0') > 0 && (userInput.at(12) - '0' < 8)) {
                        if (pile == userInput.at(12)) {
                            throw -3;
                        } else {
                            game.pileToPile(userInput.at(12), userInput.at(0), userInput.at(1));
                        }
                    }
                }
            } else if (userInput.length() == 2) {
                pile = game.searchBoard(userInput.at(0), userInput.at(1));
                if (pile == -2) {
                    throw -1;
                } else if (pile == -1) {
                    throw -2;
                } else if (pile == 0) {
                    switch (userInput.at(0)) {
                        case 'h': 
                            game.deckToGameEnd(8);
                            break;
                        case 'd':
                            game.deckToGameEnd(9);
                            break;
                        case 's':
                            game.deckToGameEnd(10);
                            break;
                        case 'c':
                            game.deckToGameEnd(11);
                            break; 
                    }
                } else if (pile > 0 && pile < 8) {
                    switch (userInput.at(0)) {
                        case 'h': 
                            game.pileToGameEnd(pile, 8);
                            break;
                        case 'd':
                            game.pileToGameEnd(pile, 9);
                            break;
                        case 's':
                            game.pileToGameEnd(pile, 10);
                            break;
                        case 'c':
                            game.pileToGameEnd(pile, 11);
                            break;
                    }
                }
            } else {
                throw -1;
            }
        }
        catch (int errorNum) {
            switch (errorNum) {
                case -1: 
                    std::cout << "That is an invalid command. Try again." << std::endl;
                    break;
                case -2:
                    std::cout << "That card is not playable. Try again." << std::endl;
                    break;
                case -3: 
                    std::cout << "That card is an invalid move. Try again." << std::endl;
                    break;
            }
        }
    }
}
