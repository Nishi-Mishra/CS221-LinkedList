#include "executable.h"
#include "Card.h"
#include <sstream>

TEST(build_deck) {
    Typegen t;
    size_t constexpr N_SUITS = 4;

    {
        std::stringstream ss(FULL_DECK);
        List<Card> deck = buildDeck(ss);

        auto it = deck.cbegin();
        size_t i = 0;

        size_t constexpr CARDS_IN_SUIT = 13;
        Rank constexpr RANK_START = ACE;
        while(it != deck.cend()) {
            ASSERT_TRUE(it->suit == static_cast<Suit>(i / CARDS_IN_SUIT));
            ASSERT_TRUE(it->rank == static_cast<Rank>(i % CARDS_IN_SUIT + RANK_START));

            it++;
            i++;
        }

        ASSERT_EQ(CARDS_IN_SUIT * N_SUITS, i);
    }

    {
        std::stringstream ss(FACE_CARDS_DECK);
        List<Card> deck = buildDeck(ss);

        auto it = deck.cbegin();
        size_t i = 0;

        size_t constexpr CARDS_IN_SUIT = 4;
        Rank constexpr RANK_START = JACK;
        while(it != deck.cend()) {
            ASSERT_TRUE(it->suit == static_cast<Suit>(i / CARDS_IN_SUIT));

            if (it->rank != static_cast<Rank>(1)) {
                ASSERT_TRUE(it->rank == static_cast<Rank>(i % CARDS_IN_SUIT + RANK_START - 1));
            } else {
                ASSERT_TRUE(it->rank == static_cast<Rank>(i % CARDS_IN_SUIT + 1));
            }

            it++;
            i++;
        }

        ASSERT_EQ(CARDS_IN_SUIT * N_SUITS, i);
    }

}
