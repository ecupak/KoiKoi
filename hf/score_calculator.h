#pragma once

#include "card.h"
#include "model.h"


class ScoreCalculator
{
public:
	ScoreCalculator() { }

	const int CalculateNewScore(Model& model);

private:
	void ScoreBrights(Model& model, const std::vector<Card>& brights);
	void ScoreAnimals(Model& model, const std::vector<Card>& animals);
	void ScoreRibbons(Model& model, const std::vector<Card>& ribbons);
	void ScoreViewings(Model& model, const std::vector<Card>& animals, const std::vector<Card>& brights);
	void ScoreKasu(Model& model, const std::vector<Card>& kasu);

	const int GetExtendedYakuScore(const int size, const int set_end) const;
};