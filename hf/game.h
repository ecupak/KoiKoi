#pragma once

#include "view.h"
#include "model.h"

#include <vector>

#include "score_calculator.h"
#include "game_response.h"
#include "game_result.h"
#include "game_outcome.h"

#include "game_enum.h"
#include "card.h"


class Game
{
public:
	// METHODS

	Game(Model& model, View& view);

	void Begin();	

private:
	// METHODS
	 
	// Match loop.
	const bool StartMatch();
	void StartRound();
	void ProcessRoundResults(const int rounds_played);
	void ShowRoundResults(const int rounds_played);
	void ShowScore(const PlayerIs& player_is);
	void SaveRoundResults();
	void ShowGameResult();
		
	// Round loop.
	const bool IsRoundActive() const;
	void TakeTurn();
	void AdvanceTurn();

	// Turn loop.
	void StartTurn();
	void ShowCards() const;
	void ProcessResponse();
	const bool IsPhase(const Phase& phase) const;
	void AdvancePhase();
	
	// General.
	void ShowCaptureReview(const PlayerIs& player_is);
	

	// VARIABLES
	Model& m_model;
	View& m_view;
	ScoreCalculator m_score_calculator;
	GameResponse m_game_response;
	GameResult m_game_result;
	GameOutcome m_game_outcome;
};