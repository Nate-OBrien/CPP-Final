#ifndef CARDS
#define CARDS 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

int card(){
srand(time(0));

    int randomCard = rand() % 52 + 1;
    cout << randomCard << endl; 
    return randomCard;
    
}

#endif