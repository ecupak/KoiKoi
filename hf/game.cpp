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
		switch (m_model.GetScreen())
		{
		case Screen::GAME:
			ShowGame();
			ProcessGameResponse();
			break;
		case Screen::CAPTURES:
			//DisplayMyCollection();
			break;
		}
	}
}


void Game::ShowGame()
{
	switch (m_model.GetPhase())
	{
	case Phase::MATCH_FROM_HAND:
		m_view.ShowHand(m_model.GetPlayerHand());
		m_view.ShowField(m_model.GetField());
		break;
	case Phase::MATCH_FROM_DRAW:
		m_view.ShowDrawnCard(m_model.GetDrawnCard());
		m_view.ShowField(m_model.GetField());
		break;
	}
}


void Game::ProcessGameResponse()
{	
	int card_played_display_index{ -1 };
	int card_on_field_display_index{ -1 };

	Response response{ GetResponse(card_played_display_index, card_on_field_display_index) };
	ProcessResponse(response, card_played_display_index, card_on_field_display_index);
}


const Response Game::GetResponse(int& card_played_display_index, int& card_on_field_display_index)
{		
	Response response{ Response::NONE };

	do
	{
		int prompt_id{ 1 };

		// Player only selects card to play during 'match from hand' phase.
		if (IsPlayingCardFromHand())
		{
			response = GetPromptResponse(prompt_id++, card_played_display_index);
		}

		// Skip asking for field card if player wants to view a different screen.
		if (IsNewScreenRequested(response))
		{
			return response;
		}

		// Will always need to match card from hand or drawn card to a field card.
		response = GetPromptResponse(prompt_id, card_on_field_display_index);

	} while (response == Response::CHANGE_CARD);

	return response;	
}


const bool Game::IsPlayingCardFromHand()
{
	return (m_model.GetPhase() == Phase::MATCH_FROM_HAND);
}


const bool Game::IsNewScreenRequested(const Response& response)
{
	return (response == Response::VIEW_CAPTURES);
}


const Response Game::GetPromptResponse(const int prompt_order, int& card_index)
{
	Response response{ Response::NONE };
	const Prompt prompt{ GetPrompt(prompt_order) };

	while (response == Response::NONE)
	{
		m_view.ShowPrompt(prompt);
	
		response = GetResponseToPrompt(prompt, card_index);
	}

	return response;
}


const Prompt Game::GetPrompt(const int prompt_order)
{
	switch (m_model.GetPhase())
	{
	case Phase::MATCH_FROM_HAND:
		return GetMatchFromHandPrompt(prompt_order);		
	case Phase::MATCH_FROM_DRAW:
		return Prompt::MATCH_DRAWN_CARD;
	}
}


const Prompt Game::GetMatchFromHandPrompt(const int prompt_order)
{
	switch (prompt_order)
	{
	case 0:
		return Prompt::PLAY_CARD;
	case 1:
		return Prompt::MATCH_PLAYED_CARD;
	}
}


const Response Game::GetResponseToPrompt(const Prompt& prompt, int& card_index)
{
	const std::string input{ GetInput() };

	return GetResponseFromInput(input, prompt, card_index);
}


const std::string Game::GetInput()
{
	std::string input{};

	do
	{
		std::getline(std::cin, input);

	} while (input.length() < 1);

	return input;
}


const Response Game::GetResponseFromInput(const std::string& input, const Prompt& prompt, int& card_index)
{
	Response response{ Response::NONE };

	while (response == Response::NONE)
	{
		response = GetScreenChangeResponse(input[0]);

		if (response == Response::NONE && prompt == Prompt::MATCH_PLAYED_CARD)
		{
			response = GetCardChangeResponse(input[0]);
		}

		if (response == Response::NONE)
		{
			response = GetCardIndexResponse(input, card_index);
		}
	}

	return response;
}


const Response Game::GetScreenChangeResponse(const char input)
{
	switch (input)
	{
	case 'v':
	case 'V':
		return Response::VIEW_CAPTURES;
	default:
		return Response::NONE;
	}
}


const Response Game::GetCardChangeResponse(const char input)
{
	switch (input)
	{
	case 'c':
	case 'C':
		return Response::VIEW_CAPTURES;
	default:
		return Response::NONE;
	}
}


const Response Game::GetCardIndexResponse(const std::string& input, int& card_index)
{
	switch (GetCardIndexResult(input, card_index))
	{
	case Result::OK:
		return Response::CONTINUE;
	case Result::INVALID:
		return Response::NONE;
	}
}


const Result Game::GetCardIndexResult(const std::string& input, int& card_index)
{
	// Extract index form input and confirm if it is valid with result.
	std::string extracted_index{ GetIndexFromInput(input) };
	Result result{ GetExtractedIndexResult(extracted_index) };

	// If valid, assign to card_index.
	if (result == Result::OK)
	{
		card_index = std::stoi(extracted_index);
	}

	return result;
}


const std::string Game::GetIndexFromInput(const std::string& input)
{
	std::string index{};

	// Copy each character into index if it is a number (ASCII decimal code 48 to 57).
	for (const char& character : input)
	{
		int decimal_code{ static_cast<int>(character) };

		if (decimal_code >= 48 && decimal_code <= 57)
		{
			index += character;

			// Will only ever need 2 digits.
			if (index.length() == 2)
			{
				break;
			}
		}
		else
		{
			// Stop at first non-numeric character.
			break;
		}
	}

	return index;
}


const Result Game::GetExtractedIndexResult(const std::string& extracted_index)
{
	// If extracted_index has at least 1 number copied into it, it is valid input.
	if (extracted_index.length() > 0)
	{
		return Result::OK;
	}
	else
	{
		return Result::INVALID;
	}
}






// Break for new class.


void Game::ProcessMatchResult(const int card_played_index, const int card_on_field_index)
{
	Result result{ GetMatchResult(card_played_index, card_on_field_index) };

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


void Game::SelectNewScreen(const Response& response)
{
	switch (response)
	{
	case Response::PLAY_FIELD:
		m_screen = Screen::GAME;
		break;
	case Response::VIEW_CAPTURES:
		m_screen = Screen::CAPTURES;
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