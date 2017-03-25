package com.william.deck;

import com.william.card.MinionCard;

import java.util.Random;

// Decidi fazer a deck array pois prefiro manter o baralho default implementado com array list
public class DeckArray {
	MinionCard[] deck;
	Integer cardCount;
	static Random random = new Random();

	public DeckArray() {
		this.deck = new MinionCard[10];
		this.cardCount = 0;
	}

	public void addCard(MinionCard card) {
		this.deck[cardCount] = card;
		cardCount++;
	}

	public MinionCard pullCard() {
		cardCount--;
		return this.deck[cardCount];
	}

	public void shuffle() {
		int i, j;

		for (i = 1; i < this.cardCount; i++) {
			j = random.nextInt(i + 1);
			if (i != j) {
				MinionCard first = this.deck[i];
				MinionCard second = this.deck[j];
				this.deck[j] = first;
				this.deck[i] = second;
			}
		}

		printReverseDeck();
	}

	private void printReverseDeck() {
		for (int i = this.cardCount - 1; i >= 0; i--) {
			System.out.print(this.deck[i]);
		}
	}

	public MinionCard[] getDeck() {
		return deck;
	}

	public void setDeck(MinionCard[] deck) {
		this.deck = deck;
	}

	public Integer getCardCount() {
		return cardCount;
	}

	public void setCardCount(Integer cardCount) {
		this.cardCount = cardCount;
	}

	public static Random getRandom() {
		return random;
	}

	public static void setRandom(Random random) {
		DeckArray.random = random;
	}
}
