#include "model.h"

#include <algorithm>	// for std::shuffle.
#include <iostream>

#include "deck.h"
#include "randomizer.h"


Model::Model()
	: m_player_1{ m_field }
	, m_player_2{ m_field }
{
	m_players[0] = &m_player_1;
	m_players[1] = &m_player_2;
}


void Model::PrepareNewRound()
{
	ClearCards();
	ClearScores();

	CreateDrawPile();
	ShuffleDrawPile();
	DealCards();
}


void Model::ClearCards()
{
	m_draw_pile.clear();
	m_field.clear();

	for (Player*& player : m_players)
	{
		player->ClearCards();
	}
}


void Model::ClearScores()
{
	for (Player*& player : m_players)
	{
		player->ClearScore();
	}
}


void Model::CreateDrawPile()
{
	Deck deck{};
	const std::array<Card, 48> cards{ deck.GetCards() };

	m_draw_pile.insert(m_draw_pile.end(), cards.begin(), cards.end());
}


void Model::ShuffleDrawPile()
{
	std::shuffle(std::begin(m_draw_pile), std::end(m_draw_pile), Randomizer::rng);
}


const Card Model::DrawCard()
{
	// Draw from the "back" of the deck.
	const Card card{ m_draw_pile.back() };
	m_draw_pile.pop_back();
	return card;
}


void Model::DealCards()
{
	for (int i{ 0 }; i < 8; ++i)
	{
		m_players[0]->AddCardToHand(DrawCard());
		m_players[1]->AddCardToHand(DrawCard());
		m_field.push_back(DrawCard());
	}
}


const std::vector<Card>& Model::GetField() const
{
	return m_field;
}


const std::vector<Card>& Model::GetPlayerHand() const
{
	return m_players[m_active_player_index]->GetHand();
}


const Card& Model::TakeFromHand(const int card_in_hand_index)
{	
	const Card card{ m_players[m_active_player_index]->RemoveCard(card_in_hand_index) };
	
	return card;
}


const Card& Model::TakeFromField(const int card_on_field_index)
{
	const Card card{ m_field[card_on_field_index] };
	m_field.erase(m_field.begin() + card_on_field_index);

	return card;
}


void Model::AddToField(const Card& card)
{
	m_field.push_back(card);
}


void Model::AddToCollection(const Card& card)
{
	m_players[m_active_player_index]->AddCardToCollection(card);
}


void Model::SwapActivePlayer()
{
	// Advance to next player. Modulo back to 0 (fist player) when value becomes last player + 1 (m_player_count = m_players.size).
	m_active_player_index = (m_active_player_index + 1) % m_player_count;
}


const int Model::GetActivePlayer() const
{
	return m_active_player_index;
}


void Model::GetNextDrawnCard()
{
	m_drawn_card = DrawCard();
}


const Card& Model::GetDrawnCard() const
{
	return m_drawn_card;
}


const int Model::GetPlayerScore() const
{
	return m_players[m_active_player_index]->GetScore();
}


void Model::SetPlayerScore(const int score)
{
	m_players[m_active_player_index]->SetScore(score);
}


void Model::ClearYakus()
{
	m_players[m_active_player_index]->ClearYakus();
}


void Model::AddYaku(const Yaku& yaku)
{
	m_players[m_active_player_index]->AddYaku(yaku);
}


const std::vector<Yaku>& Model::GetYakus() const
{
	return m_players[m_active_player_index]->GetYakus();
}


void Model::SetPhase(const Phase& phase)
{
	m_phase = phase;
}


const Phase& Model::GetPhase() const
{
	return m_phase;
}


void Model::SetScreen(const Screen& screen)
{
	m_screen = screen;
}


const Screen& Model::GetScreen() const
{
	return m_screen;
}