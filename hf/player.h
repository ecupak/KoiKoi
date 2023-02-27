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
	void AddCardToCaptures(const Card& card);
	const Card RemoveCard(const int card_in_hand_index);

	const std::vector<Card>& GetHand() const;
	const std::vector<Card>& GetCaptures() const;

	const int GetRoundScore() const;
	void SetRoundScore(const int score);

	const int GetTotalScore() const;
	void IncreaseTotalScore(const int final_round_score);

	void AddYaku(const Yaku& yaku);
	const std::vector<Yaku>& GetYakus() const;

	void SetKoiKoi(const bool has_koi_koi_bonus);
	const bool IsKoiKoiActive() const;

private:
	std::vector<Card> m_hand;
	std::vector<Card> m_captures;
	
	int m_score{ 0 };
	int m_total_score{ 0 };
	std::vector<Yaku> m_yakus;

	bool m_has_koi_koi_bonus{ false };
};