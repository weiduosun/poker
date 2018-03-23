#include <stdio.h>
#include <stdlib.h>

#include "quiz7.h"

#define PRINT_DEBUG 1

// Put your deck functions in here
// Deck functions
//----------------------------------------
Deck* createDeck() {
  Deck* newStack = (Deck*)malloc(sizeof(Deck));
  newStack->topCard = -1;
  return newStack;
}

Deck* pushCardToDeck(Card* card, Deck* deck) {
  if (deck->topCard == NUM_CARDS_IN_DECK - 1) return deck;
  deck->topCard++;
  deck->cards[deck->topCard] = card;
  return deck;
}

Card* peekAtTopCard(Deck* deck){
  if (deck->topCard == -1) return NULL;
  return deck->cards[deck->topCard];
}

Card* popCardFromDeck(Deck* deck){
  if (deck->topCard == -1) return NULL;
  return deck->cards[deck->topCard--];
}

int isDeckEmpty(Deck* deck){
  if (deck->topCard == -1) return 1;
  return 0;
}

void destroyDeck(Deck* deck){
  free(deck); 
}
