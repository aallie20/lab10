#include "deck.h"
#include <random>

/*******************************************************************************
 * These four functions are yours to write. Until you do, the program builds and
 * runs, but every Deck is empty and the Blackjack demonstration tells you so.
 * Do not change the other functions in this file.
 ******************************************************************************/

Deck::Deck() : m_cards{nullptr}, m_size{deck_size}, m_next{0} {
 m_cards = new Card[m_size];

  int index = 0;

  for (int suit = 0; suit < 4; ++suit) {
    for (int rank = 1; rank <= 13; ++rank) {
      m_cards[index] = Card(rank, static_cast<Suit>(suit));
      ++index;
    }
  }
}

Deck::~Deck() {
delete[] m_cards;
}

Deck::Deck(const Deck &other) : m_cards{nullptr}, m_sizei{other.m_size}, m_next{other.m_next} {

m_cards = new Card[m_size];

  for (int i = 0; i < m_size; ++i) {
    m_cards[i] = other.m_cards[i];
  }
}

Deck &Deck::operator=(const Deck &other) {
 
if (this == &other) {
    return *this;
  }

  delete[] m_cards;

  m_size = other.m_size;
  m_next = other.m_next;

  m_cards = new Card[m_size];

  for (int i = 0; i < m_size; ++i) {
    m_cards[i] = other.m_cards[i];
  }

  return *this;
}

/*******************************************************************************
 * Provided: Do Not Change
 ******************************************************************************/

void Deck::shuffle(std::mt19937 &gen) {
  // Fisher-Yates: walk from the last card down, swapping each card with a
  // randomly chosen card at or before it.
  for (int i{m_size - 1}; i > 0; --i) {
    std::uniform_int_distribution<int> pick{0, i};
    const int j = pick(gen);
    const Card held = m_cards[i];
    m_cards[i] = m_cards[j];
    m_cards[j] = held;
  }
  m_next = 0;
}

Card Deck::deal() {
  const Card top = m_cards[m_next];
  ++m_next;
  return top;
}

bool Deck::empty() { return m_next >= m_size; }

int Deck::remaining() { return m_size - m_next; }
