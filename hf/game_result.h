#pragma once

#include "model.h"

#include "game_enum.h"


class GameResult
{
public:
	// METHODS
	GameResult(Model& model);

	const Result GetResult(const Response& response);

private:
	// METHODS

	// Trunk.
	const Result GetMatchResult() const;
	const Result GetScoringResult(const Response& response);

	// Match result path.
	const Result GetFieldCardResult() const;
	const bool IsResultNotOK(const Result& result) const;
	const Result GetPlayedCardResult() const;
	const bool GetCaptureResult() const;

	// Field card check.
	const Result GetFieldCardValidationResult() const;
	const bool HasPlayerDeclaredNoMatch(const int field_card_display_index) const;
	const Result GetNoMatchConfirmationResult() const;
	const Card& GetCardToPlay() const;

	// Played card check (always ok when card was drawn).
	const bool IsPlayedCardDrawn() const;

	// Capture check.
	const bool DoesPlayedMatchField() const;
	const bool DoesDrawnMatchField() const;

	// General.
	const bool IsCardInRange(const int card_display_index, const int range_max) const;
	

	// VARIABLES
	Model& m_model;
};

