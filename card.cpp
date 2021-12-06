#include "card.hpp"

Card::Card() : suite('\0'), value('\0'), revealed(false) {}

Card::Card(char s, char v, bool r) {
    suite = s;
    value = v;
    revealed = r;
}

char Card::returnSuite() {
    return suite;
}

char Card::returnValue() {
    return value;
}

bool Card::returnRevealed() {
    return revealed;
}

void Card::flipReveal() {
    revealed = !revealed;
}

int Card::returnGameValue() {
    if (value == 'A') {return 1;} 
    else if (value == 'T') {return 10;}
    else if (value == 'J') {return 11;}
    else if (value == 'Q') {return 12;}
    else if (value == 'K') {return 13;}
    else {return value - '0';}
}