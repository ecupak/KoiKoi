#include "game.h"

#include <iostream>

#include "deck.h"


Game::Game(View& view, Model& model)
	: m_view{ view }
	, m_model{ model }
{	}


void Game::Begin()
{
	bool is_rematch_requested{ false };

	do
	{
		is_rematch_requested = StartMatch();

	} while (is_rematch_requested);
}


const bool Game::StartMatch()
{
	int rounds_played{ 0 };
	int rounds_to_play{ 12 };

	do
	{
		m_model.PrepareNewRound();		
		StartRound();

		//DisplayMyCollection();
		//DisplayTheirCollection();
		//DisplayRoundResult();

		// Round completed.
		++rounds_played;

	} while (rounds_played < rounds_to_play);

	// ask and return if the players want to play again.
	return false;
}


void Game::StartRound()
{	
	StartTurn();
	while (m_is_round_over == false)
	{
		switch (m_screen)
		{
		case Screen::GAME:
			ShowGame();
			ProcessResponse();
			break;
		case Screen::MY_COLLECTION:
			//DisplayMyCollection();
			break;
		case Screen::THEIR_COLLECTION:
			//DisplayTheirCollection();
			break;
		}
	}
}


void Game::ShowGame()
{
	m_view.ShowField(m_model.GetField());

	switch (m_phase)
	{
	case Phase::MATCH_FROM_HAND:
		m_view.ShowHand(m_model.GetPlayerHand());
		break;
	case Phase::MATCH_FROM_DRAW:
		m_view.ShowDrawnCard(m_model.GetDrawnCard());
		break;
	}
}


void Game::ProcessResponse()
{
	int card_in_hand_display_index{ -1 };
	int card_on_field_display_index{ -1 };
	Response response{ m_view.GetGameResponse(m_phase, card_in_hand_display_index, card_on_field_display_index) };

	// If player requested a new screen (not CONTINUE), then don't process match.
	if (response != Response::CONTINUE)
	{
		SelectNewScreen(response);
	}
	else
	{
		// These indexes are from 1 to size() - noted as display index.
		Result result{ GetMatchResult(card_in_hand_display_index, card_on_field_display_index) };
		
		switch (result)
		{
		case Result::OK:
		case Result::NO_MATCH:
			ProcessMatchPhase(result, card_in_hand_display_index, card_on_field_display_index);			
			ConcludeMatchPhase();			
			break;
		default:
			// Card index out of bounds or cards do not match.
			m_view.ShowMessage(result);
			break;
		}
	}	
}


void Game::SelectNewScreen(const Response& response)
{
	switch (response)
	{
	case Response::PLAY_FIELD:
		m_screen = Screen::GAME;
		break;
	case Response::VIEW_MY_COLLECTION:
		m_screen = Screen::MY_COLLECTION;
		break;
	case Response::VIEW_THEIR_COLLECTION:
		m_screen = Screen::THEIR_COLLECTION;
		break;
	}
}


const Result Game::GetMatchResult(const int card_in_hand_display_index, const int card_on_field_display_index)
{
	// Verify selected card indexes are valid. IsCardInHand is always true if phase is 'match from draw'.
	if (IsCardInHand(card_in_hand_display_index) && IsCardOnField(card_on_field_display_index))
	{
		if (IsPlayedCardMatchFieldCard(card_in_hand_display_index, card_on_field_display_index))
		{
			return Result::OK;		
		}
		else
		{
			return Result::NO_MATCH;
		}
	}
	else
	{
		return Result::INVALID;
	}
}


const bool Game::IsCardInHand(const int card_in_hand_display_index)
{
	// Skip (always true) when card is drawn from deck.
	if (m_phase == Phase::MATCH_FROM_DRAW) return true;

	// Confirm card index is within hand size.
	if (card_in_hand_display_index < 1)
	{
		return false;
	}
	else if (card_in_hand_display_index > m_model.GetPlayerHand().size())
	{
		return false;
	}
	else
	{
		return true;
	}
}


const bool Game::IsCardOnField(const int card_on_field_display_index)
{
	// Confirm card index is within field size (or 0 / no match available).
	if (card_on_field_display_index < 0)
	{
		return false;
	}
	else if (card_on_field_display_index > m_model.GetField().size())
	{
		return false;
	}
	else
	{
		return true;
	}
}


const bool Game::IsPlayedCardMatchFieldCard(const int card_played_display_index, const int card_on_field_display_index)
{
	if (m_phase == Phase::MATCH_FROM_HAND)
	{
		int real_index{ card_played_display_index - 1 };
		return m_model.GetPlayerHand().at(real_index).GetMonth() == m_model.GetField().at(real_index).GetMonth();
	}
	else
	{
		int real_index{ card_on_field_display_index - 1 };
		return m_model.GetDrawnCard().GetMonth() == m_model.GetField().at(real_index).GetMonth();
	}
}


void Game::ProcessMatchPhase(const Result& result, const int card_in_hand_display_index, const int card_on_field_display_index)
{
	// Get played card from hand or from deck.
	const Card played_card{ m_phase == Phase::MATCH_FROM_HAND
		? m_model.TakeFromHand(card_in_hand_display_index - 1)
		: m_model.GetDrawnCard()
	};

	// If no match could be made, add played card to field.
	if (card_on_field_display_index == 0)
	{
		m_model.AddToField(played_card);
	}
	// Else played card matched field card, so add cards to collection.
	else 
	{
		m_model.AddToCollection(played_card);
		m_model.AddToCollection(m_model.TakeFromField(card_on_field_display_index - 1));
	}

	m_view.ShowMessage(result);
}


void Game::ConcludeMatchPhase()
{
	// If second phase has ended, score captured cards and pass turn.
	if (m_phase == Phase::MATCH_FROM_DRAW)
	{
		// check if yaku (ask player koi-koi / agari(shobu?)).
		CheckForYaku();

		PassTurn();
	}
	// If still in first phase, advance to second phase.
	else
	{
		AdvancePhase();
	}
}


void Game::CheckForYaku()
{
	int old_score{ m_model.GetPlayerScore() };
	int new_score{ m_score_calculator.CalculateNewScore(m_model) };

	if (new_score != old_score)
	{
		// yaku has been made.
		// ask player koi-koi or shobu?
		
		
		// if koi-koi, set other player with koi-koi status
		
		 
		// if shobu, end game
		
		// end game: apply scores.
		// if 7 or more points, get double.
		// if koi-koi status, get double (stacks).
	}
}


void Game::PassTurn()
{
	SwapActivePlayer();
	StartTurn();
}


void Game::SwapActivePlayer()
{
	m_model.SwapActivePlayer();
}


void Game::StartTurn()
{
	// Check if active player has cards in hand.
	// If not, round is over.
	// - Calculate scores: highest score is stored.
	// - Tied scored: deal keeps.
	// - No yakus: dealer privelage (6 pts)

	m_phase = Phase::MATCH_FROM_HAND;
	m_screen = Screen::GAME;
	m_view.ShowPlayerTurn(m_model.GetActivePlayer());

}


void Game::AdvancePhase()
{
	// Draw card from deck to be played during second phase.	
	m_model.GetNextDrawnCard();
	m_phase = Phase::MATCH_FROM_DRAW;
}