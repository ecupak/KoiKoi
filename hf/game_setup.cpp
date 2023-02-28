#include "game_setup.h"

#include <array>


GameSetup::GameSetup(Model& model, View& view)
	: m_model{ model }
	, m_view{ m_view }
{	}


const Result GameSetup::Setup()
{
	// Reset round until field state is valid.
	do
	{
		PrepareNewRound();

	} while (GetState(m_model.GetField()) != State::NORMAL);
	
	// Check state of both player hands.
	State state_A{ ProcessHandState(PlayerIs::ACTIVE) };
	State state_B{ ProcessHandState(PlayerIs::INACTIVE) };

	// Return to game the result.
	if (state_A == State::NORMAL && state_B == State::NORMAL)
	{
		return Result::OK;
	}
	else
	{
		return Result::END_ROUND;
	}
}


void GameSetup::PrepareNewRound()
{
	m_model.ClearCards();
	m_model.ClearScores();

	m_model.CreateDrawPile();
	m_model.ShuffleDrawPile();
	m_model.DealCards();

	m_model.SetDealer();

	m_model.SetRoundStatus(true);	
}


const State GameSetup::ProcessHandState(const PlayerIs& player_is)
{
	State hand_state{ GetState(m_model.GetHand(player_is)) };

	if (hand_state != State::NORMAL)
	{
		m_view.ShowStateMessage(hand_state, m_model.GetPlayerIndex(player_is));
		m_model.IncreaseTotalScore(6, player_is);
	}

	return hand_state;
}


const State GameSetup::GetState(const std::vector<Card>& cards)
{	
	std::array<int, 12> cards_in_month{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (Card card : cards)
	{
		int month{ card.GetMonth() - 1 };
		++cards_in_month.at(month);
	}

	return GetCardState(cards_in_month);
}


const State GameSetup::GetCardState(std::array<int, 12>& cards_in_month)
{
	int num_of_sets_of_2{ 0 };

	for (int month{ 0 }; month < 12; ++month)
	{
		int cards_in_given_month{ cards_in_month[month] };

		// Check for 4 sets of 2 cards in hand.
		if (cards_in_given_month == 2)
		{
			if (++num_of_sets_of_2 == 4)
			{
				return State::KUTTSUKI;
			}
		}

		// Check for a full month in hand.
		if (cards_in_given_month == 4)
		{
			return State::TESHI;
		}
	}
	
	return State::NORMAL;
}