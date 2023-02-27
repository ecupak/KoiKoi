#pragma once

#include "model.h"
#include "view.h"
#include "score_calculator.h"

#include "game_enum.h"


class GameResponse
{
public:
	// METHODS
	GameResponse(Model& model, View& view);

	const Response GetResponse();

private:
	// METHODS

	// Get response start/trunk.
	const Response GetMatchFromHandResponse();
	const Response GetMatchFromDrawResponse();
	const Response GetScoringResponse();
	const bool HasMadeNewYaku();
	void ShowCaptureUpdate(const PlayerIs& player_is) const;
	const Response GetPromptResponse(const Prompt& prompt);

	// Show prompts and get response.
	const Response GetPlayCardPromptResponse();
	const Response GetMatchPlayedCardPromptResponse();
	const Response GetCardChangeResponse(const std::string input);
	const Response GetMatchDrawnCardPromptResponse();
	const Response GetDecideKoiKoiPromptResponse();
	const Response GetDecideKoiKoiResponse(const std::string input);
	const std::string GetInput();

	// Get 2-digit number (card index) from player input.
	const Response GetCardIndexResponse(const std::string& input, const CardAssignment& card_assignment);
	const Result GetCardIndexResult(const std::string& input, const CardAssignment& card_assignment);
	const std::string GetIndexFromInput(const std::string& input);
	const Result GetExtractedIndexResult(const std::string& extracted_index);

	// VARIABLES
	Model& m_model;
	View& m_view;
	ScoreCalculator m_score_calculator;
};

