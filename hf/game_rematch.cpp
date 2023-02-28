#include "game_rematch.h"

#include <iostream>


GameRematch::GameRematch(View& view)
	: m_view{ view }
{	}


const Response GameRematch::GetResponse() const
{
	Response response{ Response::NONE };

	while (response == Response::NONE)
	{
		m_view.ShowPrompt(Prompt::DECIDE_REMATCH);
		
		const std::string input{ GetInput() };

		response = GetDecideRematchResponse(input);
	}

	return response;
}


const std::string GameRematch::GetInput() const
{
	std::string input{};

	while (input.length() < 1)
	{
		std::getline(std::cin, input);
	}

	return input;
}


const Response GameRematch::GetDecideRematchResponse(const std::string& input) const
{
	switch (input[0])
	{
	case 'p':
	case 'P':
		return Response::REMATCH;
	case 'q':
	case 'Q':
		return Response::STOP;
	default:
		return Response::NONE;
	}
}