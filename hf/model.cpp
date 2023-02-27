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

	SetDealer();
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
		player->SetKoiKoi(false);
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


void Model::SetDealer()
{
	m_dealer_index = m_player_1.GetTotalScore() >= m_player_2.GetTotalScore() ? 0 : 1;	
}


const std::vector<Card>& Model::GetField() const
{
	return m_field;
}


const std::vector<Card>& Model::GetHand(const PlayerIs& player_is) const
{
	int player_index{ GetPlayerIndex(player_is) };
	return m_players[player_index]->GetHand();
}


const std::vector<Card>& Model::GetCaptures(const PlayerIs& player_is) const
{
	int player_index{ GetPlayerIndex(player_is) };
	return m_players[player_index]->GetCaptures();
}


void Model::SetCardDisplayIndex(const CardAssignment& card_assignment, const int card_index)
{
	switch (card_assignment)
	{
		case CardAssignment::PLAYED:
			m_played_card_display_index = card_index;
			break;
		case CardAssignment::FIELD:
			m_field_card_display_index = card_index;
			break;
	}
}


const int Model::GetCardDisplayIndex(const CardAssignment& card_assignment)
{
	switch (card_assignment)
	{
	case CardAssignment::PLAYED:
		return m_played_card_display_index;
	case CardAssignment::FIELD:
		return m_field_card_display_index;
	default:
		throw 1;
	}
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


void Model::AddToCaptures(const Card& card)
{
	m_players[m_active_player_index]->AddCardToCaptures(card);
}


void Model::SwapActivePlayer()
{
	// Advance to next player. Modulo back to 0 (fist player) when value becomes last player + 1 (m_player_count = m_players.size).
	m_inactive_player_index = m_active_player_index;
	m_active_player_index = (m_active_player_index + 1) % m_player_count;
}


void Model::DrawCardToMatch()
{
	m_drawn_card = DrawCard();
}


const Card& Model::GetDrawnCard() const
{
	return m_drawn_card;
}


const int Model::GetRoundScore(const PlayerIs& player_is) const
{
	int player_index{ GetPlayerIndex(player_is) };
	return m_players[player_index]->GetRoundScore();
}


void Model::SetRoundScore(const int score, const PlayerIs& player_is)
{
	int player_index{ GetPlayerIndex(player_is) };
	m_players[player_index]->SetRoundScore(score);
}


void Model::IncreaseTotalScore(const int final_round_score, const PlayerIs& player_is)
{
	int player_index{ GetPlayerIndex(player_is) };
	m_players[player_index]->IncreaseTotalScore(final_round_score);
}


void Model::IncreaseDealerTotalScore(const int dealer_advantage)
{
	m_players[m_dealer_index]->IncreaseTotalScore(dealer_advantage);
}


const int Model::GetTotalScore(const PlayerIs& player_is) const
{
	int player_index{ GetPlayerIndex(player_is) };
	return m_players[player_index]->GetTotalScore();
}


void Model::ClearYakus()
{
	m_players[m_active_player_index]->ClearYakus();
}


void Model::AddYaku(const Yaku& yaku, const PlayerIs& player_is)
{
	int player_index{ GetPlayerIndex(player_is) };
	m_players[player_index]->AddYaku(yaku);
}


const std::vector<Yaku>& Model::GetYakus(const PlayerIs& player_is) const
{
	int player_index{ GetPlayerIndex(player_is) };
	return m_players[player_index]->GetYakus();
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


void Model::SetRoundStatus(const bool is_round_active)
{
	m_is_round_active = is_round_active;
}


const bool Model::IsRoundActive() const
{
	return m_is_round_active;
}


void Model::SetPlayerKoiKoi(const bool is_koi_koi_active, const PlayerIs& player_is)
{
	int player_index{ GetPlayerIndex(player_is) };
	m_players[player_index]->SetKoiKoi(true);
}


const bool Model::GetPlayerKoiKoi(const PlayerIs& player_is) const
{
	int player_index{ GetPlayerIndex(player_is) };
	return m_players[player_index]->IsKoiKoiActive();
}


const bool Model::IsKoiKoiActive() const
{
	return (m_players[m_active_player_index]->IsKoiKoiActive()
		|| m_players[m_inactive_player_index]->IsKoiKoiActive());
}


const int Model::GetPlayerIndex(const PlayerIs& player_is) const
{
	return player_is == PlayerIs::ACTIVE ? m_active_player_index : m_inactive_player_index;
}