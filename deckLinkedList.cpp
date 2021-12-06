#include "deckLinkedList.hpp"
#include <stdlib.h>
#include <iostream>

int gameValue(char input);

DeckLinkedList::DeckLinkedList() {}

DeckLinkedList::DeckLinkedList(Card card, DeckLinkedList* followingCard) {
    currentCard = card;
    nextCard = followingCard;
}

void DeckLinkedList::addCards(Card addingCard) {
    DeckLinkedList *ptr = this;

    if (ptr->currentCard.returnValue() == '\0') {
        ptr->currentCard = addingCard;
        ptr->nextCard = nullptr;
    }
    else {
        while (ptr->nextCard != nullptr) {
            ptr = ptr->nextCard;
        }
        ptr->nextCard = new DeckLinkedList(addingCard, nullptr);
    }
}

void DeckLinkedList::printCards() {
    DeckLinkedList* ptr = this;
    while(ptr->nextCard != nullptr) {
        std::cout << std::string() + (ptr->currentCard).returnSuite() + (ptr->currentCard).returnValue() << std::endl;
        ptr = ptr->nextCard;
    }
    std::cout << std::string() + (ptr->currentCard).returnSuite() + (ptr->currentCard).returnValue() << std::endl;
    std::cout << std::endl;
}

std::vector<Card> DeckLinkedList::cardsInPile() {
    DeckLinkedList* ptr = this;
    std::vector<Card> cardsPile;
    int counter=0;
    if ((ptr->currentCard).returnValue() == '\0') {return cardsPile;}
    while (ptr->nextCard != nullptr) {
        cardsPile.push_back(ptr->currentCard);
        ptr = ptr->nextCard;
        counter++;
    }
    cardsPile.push_back(ptr->currentCard);

    return cardsPile;
}

void DeckLinkedList::next() {
    Card movingCard = this->currentCard;
    (this->currentCard).flipReveal();
    
    DeckLinkedList* first = this;
    *this = *(this->nextCard);  //issue is within this line
    DeckLinkedList* last = this;

    while (last->nextCard != nullptr) {
        last = last->nextCard; 
    }
    

    this->flipFirstCard();
}

void DeckLinkedList::flipFinalCard() {
    DeckLinkedList* ptr = this;
    while (ptr->nextCard != nullptr) {
        ptr = ptr->nextCard;
    }
    (ptr->currentCard).flipReveal();
}

void DeckLinkedList::flipFirstCard() {
    (this->currentCard).flipReveal();
}

void DeckLinkedList::deckToPile(DeckLinkedList *destination) {
    DeckLinkedList* ptr = destination;
    while (ptr->nextCard != nullptr) {
        ptr = ptr->nextCard;
    }
    Card destinationCard = ptr->currentCard; 
    Card movingCard = currentCard;

    switch (destinationCard.returnSuite()) {
        case 'h': case 'd':
            if (movingCard.returnSuite() == 'h' || movingCard.returnSuite() == 'd') {
                std::cout << "That move is invalid. Try again." << std::endl; 
                return;
            }
            break;
        case 'c': case 's':
            if (movingCard.returnSuite() == 'c' || movingCard.returnSuite() == 's') {
                std::cout << "That move is invalid. Try again." << std::endl; 
                return;
            }
            break;
    }
    
    if (destinationCard.returnGameValue()-movingCard.returnGameValue() != 1) {
        std::cout << "That move is invalid. Try again." << std::endl; 
        return;
    }

    ptr->nextCard = new DeckLinkedList(movingCard, nullptr);

    DeckLinkedList* temp = this;
    *this = *(this->nextCard);
    delete temp;
    this->flipFirstCard();
}

void DeckLinkedList::deckToGameEnd(DeckLinkedList *destination) {
    DeckLinkedList* ptr = destination;
    Card movingCard = currentCard;
    if (((*ptr).currentCard).returnValue() == '\0') {
        if (movingCard.returnGameValue() != 1) {
            std::cout << "That move is invalid. Try again." << std::endl;
            return;
        } else {
            ptr->currentCard = movingCard;
        }
    } else {
        while (ptr->nextCard != nullptr) {
            ptr = ptr->nextCard;
        }
        Card destinationCard = ptr->currentCard; 
        if (currentCard.returnGameValue() - destinationCard.returnGameValue() != 1) {
            std::cout << "That move is invalid. Try again." << std::endl;
            return;
        } else {
            ptr->nextCard = new DeckLinkedList(movingCard, nullptr);
        }
    }
    DeckLinkedList* temp = this;
    *this = *(this->nextCard);
    delete temp;
    (*this).flipFirstCard();
}

void DeckLinkedList::pileToPile(DeckLinkedList *destination, char s, char v) {
    DeckLinkedList* ptr = destination;
    while (ptr->nextCard != nullptr) {
        ptr = ptr->nextCard;
    }
    Card destinationCard = ptr->currentCard; 

    char color; 
    if (s == 'd' || s == 'h') {
        color = 'r';
    } else {color = 'b';}
    if (destinationCard.returnColor() == color || destinationCard.returnGameValue()-gameValue(v) != 1) {
        std::cout << "That move is invalid. Try again." << std::endl;
        return;
    }

    DeckLinkedList* thisPtr = this;
    DeckLinkedList* thisPtrPrevious;
    while ((this->currentCard).returnValue() != v || (this->currentCard).returnSuite() != s) {
        thisPtrPrevious = thisPtr;
        thisPtr = thisPtr->nextCard;
    }
    ptr->nextCard = thisPtrPrevious; 
    thisPtrPrevious->nextCard = nullptr;
    (*this).flipFinalCard();
}

void DeckLinkedList::pileToGameEnd(DeckLinkedList *destination) {
    DeckLinkedList* ptr = destination;

    DeckLinkedList* temp = this;
    DeckLinkedList* tempPrevious;
    while (temp->nextCard != nullptr) {
        tempPrevious = temp;
        temp = temp->nextCard;
    }

    if (((*ptr).currentCard).returnValue() == '\0') {
        if ((temp->currentCard).returnGameValue() != 1) {
            std::cout << "That move is invalid. Try again." << std::endl;
            return;
        } else {
            ptr->currentCard = temp->currentCard;
            ptr->nextCard = nullptr;
        }
    } else {
        while (ptr->nextCard != nullptr) {
            ptr = ptr->nextCard;
        }
        Card destinationCard = ptr->currentCard; 
        if (currentCard.returnGameValue() - destinationCard.returnGameValue() != 1) {
            std::cout << "That move is invalid. Try again." << std::endl;
            return;
        } else {
            ptr->nextCard = tempPrevious->nextCard;
        }
    }

    if (tempPrevious != nullptr) {
        tempPrevious->nextCard = nullptr;
    }
    if ((tempPrevious->currentCard).returnRevealed() == false) {
        (*this).flipFinalCard();
    }
}

int DeckLinkedList::search(char s, char v) {
    DeckLinkedList* ptr = this;
    while (ptr->nextCard != nullptr) {
        if ((ptr->currentCard).returnSuite() == s && (ptr->currentCard).returnValue() == v) {
            if ((ptr->currentCard).returnRevealed() == false) {
                return -1;
            } else {
                return 1;
            }
        }
        ptr = ptr->nextCard;
    }
    if ((ptr->currentCard).returnSuite() == s && (ptr->currentCard).returnValue() == v) {
        if ((ptr->currentCard).returnRevealed() == false) {
            return -1;
        } else {
            return 1;
        }
    }
    return 0;
}

int gameValue(char input) {
    if (input == 'A') {return 1;} 
    else if (input == 'T') {return 10;}
    else if (input == 'J') {return 11;}
    else if (input == 'Q') {return 12;}
    else if (input == 'K') {return 13;}
    else {return input - '0';}
}