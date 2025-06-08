
#ifndef CARDS
#define CARDS 
#include <cstdlib>
#include <ctime>

int getRandomCard(){
    int randomCard = rand() % 10 + 2;
    return randomCard;    
}

#endif
