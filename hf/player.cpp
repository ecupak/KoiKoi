#include "player.h"

#include <iostream>
#include <algorithm>


Player::Player(const std::vector<Card>& field) { }


void Player::ClearCards()
{
	m_hand.clear();
	m_captures.clear();
}


void Player::ClearScore()
{
	m_score = 0;
	ClearYakus();
}


void Player::ClearYakus()
{
	m_yakus.clear();
}


void Player::AddCardToHand(const Card& card)
{
	m_hand.push_back(card);
}


void Player::AddCardToCaptures(const Card& card)
{
	m_captures.push_back(card);

	// Sort collection by category.
	std::sort(m_captures.begin(), m_captures.end(),
		[](Card& first_card, Card& second_card) {
			return static_cast<int>(first_card.GetCategory()) < static_cast<int>(second_card.GetCategory());
		}
	);
}


const std::vector<Card>& Player::GetHand() const
{
	return m_hand;
}


const std::vector<Card>& Player::GetCaptures() const
{
	return m_captures;
}


const Card Player::RemoveCard(const int card_in_hand_index)
{
	const Card card{ m_hand.at(card_in_hand_index)};
	m_hand.erase(m_hand.begin() + card_in_hand_index);
	
	return card;
}


const int Player::GetRoundScore() const
{
	return m_score;
}


void Player::SetRoundScore(const int score)
{
	m_score = score;
}


const int Player::GetTotalScore() const
{
	return m_total_score;
}


void Player::IncreaseTotalScore(const int final_round_score)
{
	m_total_score += final_round_score;
}


void Player::AddYaku(const Yaku& yaku)
{
	m_yakus.push_back(yaku);
}


const std::vector<Yaku>& Player::GetYakus() const
{
	return m_yakus;
}


void Player::SetKoiKoi(const bool has_koi_koi_bonus)
{
	m_has_koi_koi_bonus = has_koi_koi_bonus;
}


const bool Player::IsKoiKoiActive() const
{
	return m_has_koi_koi_bonus;
}