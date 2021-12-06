//solitaireBoard.hpp by Samuel Lee

#ifndef _SOLITAIREBOARD_H_
#define _SOLITAIREBOARD_H_

#include "deckLinkedList.hpp"

class SolitaireBoard {
    public:
        SolitaireBoard();
        ~SolitaireBoard();
        void printCards();
        void printBoard();
        void moveCard();
        void resetBoard();
        void undo();
        void traverseDeck();
        void deckToPile(int pileNum);
        void deckToGameEnd(int pileNum);
        void pileToPile(int destination, char s, char v);
        int searchBoard(char s, char v);
        bool checkRevealed(char s, char v);
        bool gameComplete();
        void pileToGameEnd(int pileNum, int destNum);
    private:
        DeckLinkedList *piles[12];
        Card deck[52];
};

#endif