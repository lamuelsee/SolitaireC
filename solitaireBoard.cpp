#include "solitaireBoard.hpp"
#include <random>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <vector>

const static int RANK_SIZE = 13;
const static int SUIT_SIZE = 4;
const static char RANKS[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
const static char SUITS[] = {'h','d','s','c'};

//piles 1~7 are the "normal" piles, 0 is the deck, 8~11 is the "game ending" pile

SolitaireBoard::SolitaireBoard() {
    for (int i=0; i<SUIT_SIZE; i++) {
        for (int j=0; j<RANK_SIZE; j++) {
            deck[i*RANK_SIZE+j] = Card(SUITS[i],RANKS[j],false);
        }
    }

    srand(time(0));
    for (int i=0; i<SUIT_SIZE*RANK_SIZE; i++) {
        std::swap(deck[i], deck[rand() % 52]);
    }

    for (int i=0; i<12; i++) {
        piles[i] = new DeckLinkedList();
    }


    int counter = 0;
    for (int i=1; i<=7; i++) {
        for (int j=0; j<i; j++) {
            (*piles[i]).addCards(deck[counter]);
            counter++;
        }
    }
    for (int i=0; i<(SUIT_SIZE*RANK_SIZE-28); i++) {
        (*piles[0]).addCards(deck[counter]);
        counter++;
    }

    for (int i=1; i<=7; i++) {
        (*piles[i]).flipFinalCard();
    }
    (*piles[0]).flipFirstCard();
}

SolitaireBoard::~SolitaireBoard() {
    for (int i=0; i<12; i++) {
        delete[] piles[i];
    }
}

void SolitaireBoard::printCards() {
    for(int i=1; i<=7; i++) {
        std::cout << "Pile " + std::to_string(i) + ": " << std::endl;
        (*piles[i]).printCards();
    }
    std::cout << "Deck: " << std::endl;
    (*piles[0]).printCards();
}

void SolitaireBoard::printBoard() {
    std::cout << std::setw(12) << std::left << "Deck:";
    for (int i=0; i<7; i++) {
        std::cout << std::setw(12) << std::left << "Pile " + std::to_string(i+1) + ":";
    } 
    std::cout << std::setw(12) << std::left << "Hearts:";
    std::cout << std::setw(12) << std::left << "Diamonds:";
    std::cout << std::setw(12) << std::left << "Spades:";
    std::cout << std::setw(12) << std::left << "Clubs:";
    std::cout << std::endl;

    std::vector<Card> p[12];
    for (int i=0; i<12; i++) {
        p[i] = (*piles[i]).cardsInPile();
    }

    char suite, value;
    for (int i=0; i<52; i++) {
        for (int j=0; j<12; j++) {
            if ((int)p[j].size() <= i) {
                std::cout << std::setw(12) << std::left << std::string();
            } else if ((p[j].at(i)).returnRevealed() == true) {
                suite = (p[j].at(i)).returnSuite();
                value = (p[j].at(i)).returnValue();
                std::cout << std::setw(12) << std::left << std::string() + suite + value;
            } else {
                std::cout << std::setw(12) << std::left << "---";
            }   
        }
        std::cout << std::endl;
    }
    
    for (int i=0; i<12; i++) {
        p[i].clear();
    }
}

void SolitaireBoard::traverseDeck() {
    (*piles[0]).next();
}

void SolitaireBoard::deckToPile(int pileNum) {
    (*piles[0]).deckToPile(piles[pileNum]);
}

void SolitaireBoard::deckToGameEnd(int pileNum) {
    std::vector<Card> p = (*piles[0]).cardsInPile();
    switch (pileNum) {
        case 8:
            if ((p.at(0)).returnSuite() != 'h') {
                std::cout << "That move is invalid. Try again." << std::endl;
                return;
            } 
            break;
        case 9:
            if ((p.at(0)).returnSuite() != 'd') {
                std::cout << "That move is invalid. Try again." << std::endl;
                return;
            } 
            break;
        case 10:
            if ((p.at(0)).returnSuite() != 's') {
                std::cout << "That move is invalid. Try again." << std::endl;
                return;
            } 
            break;
        case 11:
            if ((p.at(0)).returnSuite() != 'c') {
                std::cout << "That move is invalid. Try again." << std::endl;
                return;
            } 
            break;
        default: 
            std::cout << "That move is invalid. Try again." << std::endl;
            return;
    }
    p.clear();
    (*piles[0]).deckToGameEnd(piles[pileNum]);
}

void SolitaireBoard::pileToPile(int destination, char s, char v) {
    for (int i=0; i<7; i++) {
        switch ((*piles[i]).search(s,v)) {
            case -1:
                std::cout << "That card is not playable. Try again." << std::endl;
                return;
            case 1:
                (*piles[i]).pileToPile(piles[destination], s, v);
                i=7;
                break;
            case 0: 
                break;
        }
    }
}

bool SolitaireBoard::gameComplete() {
    std::vector<Card> p[4];
    for (int i=0; i<4; i++) {
        p[i] = (*piles[i+8]).cardsInPile();
    }

    int counter = 0;
    for (int i=0; i<4; i++) {
        counter += p[i].size();
    }
    
    for (int i=0; i<4; i++) {
        p[i].clear();
    }

    if (counter == 52) {return true;} else {return false;}
}

int SolitaireBoard::searchBoard(char s, char v) {
    for (int i=0; i<12; i++) {
        if ((*piles[i]).search(s,v) == -1) {
            return -1;
        } else if ( (*piles[i]).search(s,v) != 0) {
            return i;
        }
    }
    return -2;
}

void SolitaireBoard::pileToGameEnd(int pileNum, int destNum) {
    (*piles[pileNum]).pileToGameEnd(piles[destNum]);
}