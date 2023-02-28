#pragma once

#include "model.h"
#include "view.h"

#include <vector>
#include "card.h"
#include "game_enum.h"


class GameSetup
{
public:
	GameSetup(Model& model, View& view);

	const Result Setup();

private:
	void PrepareNewRound();

	const State GetState(const std::vector<Card>& cards);
	const State GetCardState(std::array<int, 12>& cards_in_month);

	const State ProcessHandState(const PlayerIs& player_is);


	Model& m_model;
	View& m_view;
};

