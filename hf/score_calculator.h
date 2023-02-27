#pragma once

#include "card.h"
#include "model.h"


class ScoreCalculator
{
public:
	// METHODS
	ScoreCalculator() { }

	void CalculateNewScore(Model& model, const PlayerIs& player_is);

private:
	// METHODS
	void ScoreBrights(Model& model, const std::vector<Card>& brights);
	void ScoreAnimals(Model& model, const std::vector<Card>& animals);
	void ScoreRibbons(Model& model, const std::vector<Card>& ribbons);
	void ScoreViewings(Model& model, const std::vector<Card>& animals, const std::vector<Card>& brights);
	void ScoreKasu(Model& model, const std::vector<Card>& kasu);

	const int GetExtendedYakuScore(const int size, const int set_end) const;

	// VARIABLES
	PlayerIs m_player_is{ PlayerIs::ACTIVE };
};