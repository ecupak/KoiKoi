#pragma once

#include <vector>

#include "card.h"
#include "yaku.h"


class Player
{
public:
	Player(const std::vector<Card>& field);

	void ClearCards();
	void ClearScore();
	void ClearYakus();

	void AddCardToHand(const Card& card);
	void AddCardToCollection(const Card& card);
	const Card RemoveCard(const int card_in_hand_index);

	const std::vector<Card>& GetHand();
	
	const int GetScore() const;
	void SetScore(const int score);

	void AddYaku(const Yaku& yaku);
	const std::vector<Yaku>& GetYakus() const;

private:
	std::vector<Card> m_hand;
	std::vector<Card> m_collection;
	
	int m_score{ 0 };
	int m_total_score{ 0 };
	std::vector<Yaku> m_yakus;
};