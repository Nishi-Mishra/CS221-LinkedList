#include <iostream>

#include "List.h"
#include "Card.h"

std::ostream& operator<< (std::ostream& out, const Suit& suit) {
    switch (suit) {
        case Suit::SPADES:
        return out << "Spades";
        case Suit::DIAMONDS:
        return out << "Diamonds";
        case Suit::CLUBS:
        return out << "Clubs";
        case Suit::HEARTS:
        return out << "Hearts";
        default:
        return out << "unknown";
    }
}

std::ostream& operator<< (std::ostream& out, const Card& card) {
    switch (card.rank) {
        case ACE:
        out << "Ace";
        break;
        case JACK:
        out << "Jack";
        break;
        case QUEEN:
        out << "Queen";
        break;
        case KING:
        out << "King";
        break;
        default:
        out << card.rank;
    }
    return out << " of " << card.suit << '.';
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const List<T>& list) {
    for (const auto& value : list) {
        out << value;
        if (&value != &list.back()) {
            out << " -> ";
        }
    }
    return out;
}

void nonTailRecur (int n) {
    if (n > 0) {
        nonTailRecur(n-1);
        cout << n << " ";
        nonTailRecur(n-1); 
    } else {
        cout << endl; 
    }
}


int main(int argc, char* argv[]) {


    //std::ifstream file("input-files/ordered-deck.dat"); 
    //List <Card> myList = buildDeck(file);   

    /*
    cout << "\x1B[96m== TESTS ==\x1B[0m" << endl;

    List <int> list{10, 1337};
    List<int> list2;
    list2.push_back(4674);
    list2.push_back(4674);
    list2.push_back(4674);
    list2.push_back(4674);
    list2.push_back(4674);

    for (auto it = list2.begin(); it != list2.end(); ++it) {
        cout << *it << endl;
    }

    return 0; 
    */
    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " <deck-file>\n\tDeck file is a formatted file containing Cards.\n\tsuit\trank\n\tsuit\trank\n\t...\t...\n\tIs the format.\n";
        return 1;
    }

    std::ifstream deck_file(argv[1]);
    
    List<Card> deck = buildDeck(deck_file);

    std::cout << "Deck: " << deck << std::endl;

    List<Card> shuffled_deck = shuffle(deck);

    std::cout << "Shuffled Deck: " << shuffled_deck << std::endl;

    return 0;
}
