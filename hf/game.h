#pragma once

#include "view.h"
#include "model.h"

#include <vector>

#include "score_calculator.h"
#include "game_enum.h"
#include "card.h"


class Game
{
public:
	Game(View& view, Model& model);

	void Begin();
	
	
	void ProcessMatchFromHand(const int card_in_hand_index, const int card_on_field_index);

private:
	const bool StartMatch();
	void StartRound();
	void StartTurn();
		
	void ShowGame();
	void ProcessGameResponse();
	const Response GetResponse(int& card_played_display_index, int& card_on_field_display_index);
	void ProcessResponse(response, card_played_display_index, card_on_field_display_index);


	
	const std::string GetInput();

	const Result GetMatchResult(const int card_played_index, const int card_on_field_index);

	const bool IsPlayingCardFromHand();
	const bool IsNewScreenRequested(const Response& response);

	const Response GetPromptResponse(const int prompt_order, int& card_index);
	const Prompt GetPrompt(const int prompt_order);
	const Prompt GetMatchFromHandPrompt(const int prompt_order);

	const Response GetResponseToPrompt(const Prompt& prompt, int& card_index);
	const Response GetResponseFromInput(const std::string& input, const Prompt& prompt, int& card_index);

	const Response GetScreenChangeResponse(const char input);
	const Response GetCardChangeResponse(const char input);
	const Response GetCardIndexResponse(const std::string& input, int& card_index);

	const Result GetCardIndexResult(const std::string& input, int& card_index);
	const std::string GetIndexFromInput(const std::string& input);
	const Result GetExtractedIndexResult(const std::string& extracted_index);

	void ProcessMatchResult(const int card_played_index, const int card_on_field_index);

	const bool IsCardInHand(const int card_from_hand_index);
	const bool IsCardOnField(const int card_from_field_index);
	const bool IsPlayedCardMatchFieldCard(const int card_in_hand_index, const int card_on_field_index);
	
	void ProcessMatchPhase(const Result& result, const int card_in_hand_display_index, const int card_on_field_display_index);
	void ConcludeMatchPhase();
	void CheckForYaku();	
		
	void SelectNewScreen(const Response& response);

	void StartPhaseYaku();
	
	void AdvancePhase();
	void PassTurn();
	void SwapActivePlayer();

	Phase m_phase{ Phase::MATCH_FROM_HAND };
	Screen m_screen{ Screen::GAME };

	View& m_view;
	Model& m_model;
	ScoreCalculator m_score_calculator;

	bool m_is_round_over{ false };
};