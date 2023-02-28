#pragma once

#include "view.h"
#include "game_enum.h"


class GameRematch
{
public:
	GameRematch(View& view);

	const Response GetResponse() const;

private:
	const std::string GetInput() const;
	const Response GetDecideRematchResponse(const std::string& input) const;


	View& m_view;
};

