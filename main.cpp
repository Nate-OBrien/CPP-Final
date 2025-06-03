#include <iostream>

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
   


}
