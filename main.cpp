/*
Name: Nate, Jake, Josh
Date: 6/3/25
Program: CPP Final
Extra: GUI
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "cards.h"

using namespace std;

bool win_lose(int dealer, int  player){
    bool win;
    if (((dealer < player)&&(player <= 21))|| (player <= 21) && (dealer > 21)){
        win = true;
    }
    else{
        win = false;
    }
    return win;
}

bool deal (int delaer){
    bool deal;
    if (dealer < 17){
        deal = true;
    }
    else{
        deal = false;
    }
    return deal;
}

int winning (bool win, int bet, int bank){
    if win = true{
        bank = bank + (bet*2);
    }
    else{
        bank = bank;
    }
    return bank;
}


int main() {
    vector <int> cards; 

    cout << "Hello, World!" << endl;
    
    while(true){
        int newCard = card();
        auto it = find(cards.begin(), cards.end(), newCard);
        
        if(it == cards.end()){
            cards.push_back(newCard);
            break;
        }
    }
    
    cout << card();


    return 0;



}
