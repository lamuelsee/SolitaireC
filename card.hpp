//card.hpp by Samuel Lee

#ifndef _CARD_H_
#define _CARD_H_

class Card {
    public:
        Card();
        Card(char s, char v, bool r);
        char returnColor(){
            if (suite == 'd' || suite == 'h') {
                return 'r';
            } else {return 'b';}
        };
        char returnSuite();
        char returnValue();
        bool returnRevealed();
        void flipReveal();
        int returnGameValue();
    private:
        char suite;
        char value;
        bool revealed;
};

#endif