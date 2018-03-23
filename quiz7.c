#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#include "quiz7.h"

#define PRINT_DEBUG 1

// Implement the Hand and other functions in here

//----------------------------------------
// Hand functions
//----------------------------------------
 
Hand* createHand(){
  Hand* newList = (Hand*)malloc(sizeof(Hand));
  newList->num_cards_in_hand = 0;
  return newList;
}

CardNode* createCardNode(Card* card) {
  CardNode* node = (CardNode*)malloc(sizeof(CardNode));
  node->nextCard = NULL;
  node->prevCard = NULL;
  node->thisCard = card;
  return node;
}

void addCardToHand(Card *card, Hand *hand) {
  if (hand->num_cards_in_hand < NUM_CARDS_IN_HAND) {
    CardNode* node = createCardNode(card);
    if (hand->firstCard != NULL) {
      node->thisCard = card;
      node->nextCard = hand->firstCard;
      hand->firstCard->prevCard = node;
      hand->firstCard = node;
    }
    hand->firstCard = node;
    hand->num_cards_in_hand++;
  }
}

void removeCard(CardNode *currNode) {
  if (currNode->prevCard != NULL) currNode->prevCard->nextCard = currNode->nextCard;
  if (currNode->nextCard != NULL) currNode->nextCard->prevCard = currNode->prevCard;
}

Card* removeCardFromHand(Card *card, Hand *hand) {
  CardNode* currNode = hand->firstCard;
  while (currNode != NULL) {
    if (hand->firstCard->thisCard == card) {
      removeCard(hand->firstCard);
      hand->firstCard = hand->firstCard->nextCard;
      hand->num_cards_in_hand--;
      return card;
    } 
    else if (currNode->thisCard == card) {
      removeCard(currNode);
      hand->num_cards_in_hand--;
      return card;
    }
    currNode = currNode->nextCard;
  }
  return NULL;
}

int isHandEmpty(Hand* hand){
  if (hand->num_cards_in_hand == 0) return 0;
  return 1;
}

void destroyHand(Hand* hand) {
  while (hand->firstCard != NULL) {
    free(hand->firstCard->prevCard);
    free(hand->firstCard->nextCard);
    hand->firstCard = hand->firstCard->nextCard;
  } 
  free(hand);
}


//----------------------------------------
// Game functions
//----------------------------------------

void shuffle(Deck *aDeck) {
  for (int i = aDeck->topCard; i > 0; i--){
    int r = rand() % i;
    Card* temp;
    temp = aDeck->cards[i];
    aDeck->cards[i] = aDeck->cards[r];
    aDeck->cards[r] = temp;
  }
}
 
void deal(Deck *aDeck, Hand *p1hand, Hand *p2hand) {
  int i = 0;
  while (p1hand->num_cards_in_hand < NUM_CARDS_IN_HAND || p2hand->num_cards_in_hand < NUM_CARDS_IN_HAND) {
    if (p1hand->num_cards_in_hand < NUM_CARDS_IN_HAND && !isDeckEmpty(aDeck)) {
      addCardToHand(popCardFromDeck(aDeck), p1hand);
    }
    if (p2hand->num_cards_in_hand < NUM_CARDS_IN_HAND && !isDeckEmpty(aDeck)) {
      addCardToHand(popCardFromDeck(aDeck), p2hand);
    }
  }
}

Card card[24];
Deck* populateDeck() {
  Suit suits[4] = {HEARTS, CLUBS, SPADES, DIAMONDS};
  Name names[6] = {NINE, TEN, JACK, QUEEN, KING, ACE};
  Deck* deck = createDeck();
  for (int i = 0; i < 6; i++) {
    card[i].suit = suits[0];
    card[i].name = names[i];
    pushCardToDeck(&card[i], deck);
  }
  for (int i = 6; i < 12; i++) {
    card[i].suit = suits[1];
    card[i].name = names[i-6];
    pushCardToDeck(&card[i], deck);
  }
  for (int i = 12; i < 18; i++) {
    card[i].suit = suits[2];
    card[i].name = names[i-12];
    pushCardToDeck(&card[i], deck);
  }
  for (int i = 18; i< 24; i++) {
    card[i].suit = suits[3];
    card[i].name = names[i-18];
    pushCardToDeck(&card[i], deck);
  }   
  return deck;
}
 
int isLegalMove(Hand *hand, Card *leadCard, Card *playedCard) {
  for (int i = 0; i < hand->num_cards_in_hand; i++) {
    if (hand->firstCard->thisCard->suit == leadCard->suit) {
       if (playedCard->suit == leadCard->suit) return 1;
       else return 0;
    }
  } 
  return 1; 
}    

int whoWon(Card *leadCard, Card *followedCard, Suit trump) {
  if (leadCard->suit == followedCard->suit) {
    if (leadCard->name >= followedCard->name) return 1;
    else return 0;
  }
  else {
    if (followedCard->suit == trump) return 0;
    else return 1;
  }
}

void returnHandToDeck(Hand *hand, Deck *deck) {
  while (hand->firstCard != NULL) {
  pushCardToDeck(removeCardFromHand(hand->firstCard->thisCard, hand), deck);
  hand->firstCard = hand->firstCard->nextCard;
  }
}
   
