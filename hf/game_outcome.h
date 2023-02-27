#pragma once

#include "model.h"
#include "view.h"

#include "game_enum.h"


class GameOutcome
{
public:
	// METHODS

	GameOutcome(Model& model, View& view);

	const Outcome GetOutcome(const Result& result);

private:
	// METHODS

	// Trunk.
	const Outcome GetMatchOutcome(const Result& result);
	const Outcome GetScoringOutcome(const Result& result);

	// Match path.
	void CaptureCards();
	void AddPlayedCardToField();
	const Card GetPlayedCard(const int played_card_index) const;
	const Card GetFieldCard(const int field_card_index) const;

	// VARIABLES
	Model& m_model;
	View& m_view;
};

