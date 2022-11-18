#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include "Card.h"

int rand221(void) {
    return rand();
}

// You may want to write the following three functions, but they are not required

// std::istream& operator>>(std::istream& in, Suit& suit) {
//    
// }

// Rank to_rank(const std::string& string) {
//    
// }

// std::istream& operator>>(std::istream& in, Card& card) {
//    
// }

List<Card> buildDeck(std::istream& file) {

    List<Card> deck; 
    std::string tempSuit; 
    std::string tempRank; 

    while (!file.eof() && file >> tempSuit >> tempRank) {
        Card curr; 

        // cout << "!Temp Suit : " << tempSuit << " |Temp Rank : " << tempRank << "|"<< endl; 

        if (tempRank == "ace") {curr.rank = ACE;}
        else if (tempRank == "jack") {curr.rank = JACK;}
        else if (tempRank == "queen") {curr.rank = QUEEN;}
        else if (tempRank == "king") {curr.rank = KING;}
        else {curr.rank = stoi(tempRank);}

        if (tempSuit == "clubs") {curr.suit = Suit::CLUBS;}
        else if (tempSuit == "spades") {curr.suit = Suit::SPADES;}
        else if (tempSuit == "hearts") {curr.suit = Suit::HEARTS;}
        else if (tempSuit == "diamonds") {curr.suit = Suit::DIAMONDS;}
        else {cout << "invalid suit" << endl;}

        deck.push_back(curr);
    }
    return deck; 
}

List<Card> shuffle(const List<Card>& deck) {

    //Create a new empty deck to which we will add cards as we shuffle them. 
    List<Card> shuffle_deck; 

    //Iterate over the deck, and for each card, flip a coin (using the rand221)
    //If heads (even), add the card to the front of the shuffled deck; else, add it to the back of the shuffled deck.
    for (auto it=deck.begin(); it != deck.end(); it++) {
        bool isFront = rand221() % 2 == 0; 
        if (isFront) {
            shuffle_deck.push_front(*it); 
        }
        else {
            shuffle_deck.push_back(*it); 
        }
    }

    // Return this shuffled deck from the shuffle function.
    return shuffle_deck;

}