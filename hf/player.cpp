#include "player.h"

#include <iostream>
#include <algorithm>


Player::Player(const std::vector<Card>& field) { }


void Player::ClearCards()
{
	m_hand.clear();
	m_collection.clear();
}


void Player::ClearScore()
{
	m_score = 0;
	ClearYakus();
}


void Player::ClearYakus()
{
	m_yaku_ids.clear();
}


void Player::AddCardToHand(const Card& card)
{
	m_hand.push_back(card);
}


void Player::AddCardToCollection(const Card& card)
{
	m_collection.push_back(card);
}


const std::vector<Card>& Player::GetHand()
{
	return m_hand;
}


const Card Player::RemoveCard(const int card_in_hand_index)
{
	const Card card{ m_hand.at(card_in_hand_index)};
	m_hand.erase(m_hand.begin() + card_in_hand_index);
	
	return card;
}


const int Player::GetScore() const
{
	return m_score;
}


void Player::SetScore(const int score)
{
	m_score = score;
}


void Player::AddYaku(const Yaku& yaku)
{
	m_yakus.push_back(yaku);
}


const std::vector<Yaku>& Player::GetYakus() const
{
	return m_yakus;
}