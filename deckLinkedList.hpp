//deckLinkedList.hpp by Samuel Lee

#ifndef _DECKLINKEDLIST_H_
#define _DECKLINKEDLIST_H_

#include "card.hpp"
#include <vector>

class DeckLinkedList {
    public:
        DeckLinkedList();
        DeckLinkedList(Card card, DeckLinkedList* followingCard);
        void addCards(Card addingCard);
        void removeCards(char s, char v);
        void printCards();
        void printTop();
        std::vector<Card> cardsInPile();
        void next(); 
        void flipFinalCard();
        void flipFirstCard();
        void deckToPile(DeckLinkedList *destination);
        void deckToGameEnd(DeckLinkedList *destination);
        void pileToPile(DeckLinkedList *destination, char s, char v);
        void pileToGameEnd(DeckLinkedList *destination);
        int search(char s, char v);
    private:
        Card currentCard;
        DeckLinkedList *nextCard;
};

#endif