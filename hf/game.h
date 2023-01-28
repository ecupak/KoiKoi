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
	
	void GetResponse();
	
	void ShowGame();
	void ProcessResponse();
	const Result GetMatchResult(const int card_played_index, const int card_on_field_index);
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