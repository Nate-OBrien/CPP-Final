#include <iostream>
#include "cards.h"
#include <vector>
#include <algorithm>

using namespace std;

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
