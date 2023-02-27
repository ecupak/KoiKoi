#include "game_response.h"
#include <iostream>


GameResponse::GameResponse(Model& model, View& view)
	: m_model{model}
	, m_view{view}
{	}


const Response GameResponse::GetResponse()
{
	Response response{ Response::NONE };

	while (response == Response::NONE)
	{
		switch (m_model.GetPhase())
		{
		case Phase::MATCH_FROM_HAND:
			response = GetMatchFromHandResponse(); // CONTINUE.
			break;
		case Phase::MATCH_FROM_DRAW:
			response = GetMatchFromDrawResponse(); // CONTINUE.
			break;
		case Phase::SCORING:
			response = GetScoringResponse(); // KOIKOI or SHOBU.
			break;
		}
	}

	return response;
}


const Response GameResponse::GetMatchFromHandResponse()
{
	Response response{ Response::NONE };

	// Response types are CHANGE_CARD or CONTINUE.
	// Only exit loop on CONTINUE.
	do
	{
		response = GetPromptResponse(Prompt::PLAY_CARD);
		response = GetPromptResponse(Prompt::MATCH_PLAYED_CARD);

	} while (response == Response::CHANGE_CARD);

	return response;
}


const Response GameResponse::GetMatchFromDrawResponse()
{
	return GetPromptResponse(Prompt::MATCH_DRAWN_CARD);
}


const Response GameResponse::GetScoringResponse()
{
	// Determine if yaku was made.
	if (HasMadeNewYaku())
	{
		// If already in koikoi, game ends with next yaku.
		if (m_model.IsKoiKoiActive())
		{
			return Response::SHOBU;
		}
		else
		{
			ShowCaptures(PlayerIs::ACTIVE);
			return GetPromptResponse(Prompt::DECIDE_KOIKOI);
		}
	}
	else
	{
		return Response::CONTINUE;
	}
}


const bool GameResponse::HasMadeNewYaku()
{
	int old_score{ m_model.GetRoundScore(PlayerIs::ACTIVE) };

	m_score_calculator.CalculateNewScore(m_model, PlayerIs::ACTIVE);

	int new_score{ m_model.GetRoundScore(PlayerIs::ACTIVE) };

	return (new_score != old_score);
}


void GameResponse::ShowCaptureUpdate(const PlayerIs& player_is)
{
	m_view.ShowCaptureUpdate();
	m_view.ShowCaptures(m_model.GetCaptures(player_is), m_model.GetYakus(player_is));
}


const Response GameResponse::GetPromptResponse(const Prompt& prompt)
{
	Response response{ Response::NONE };

	while (response == Response::NONE)
	{
		m_view.ShowPrompt(prompt);

		switch (prompt)
		{
		case Prompt::PLAY_CARD:
			response = GetPlayCardPromptResponse();
			break;
		case Prompt::MATCH_PLAYED_CARD:
			response = GetMatchPlayedCardPromptResponse();
			break;
		case Prompt::MATCH_DRAWN_CARD:
			response = GetMatchDrawnCardPromptResponse();
			break;
		case Prompt::DECIDE_KOIKOI:
			response = GetDecideKoiKoiPromptResponse();
		}
	}

	return response;
}


const Response GameResponse::GetPlayCardPromptResponse()
{
	const std::string input{ GetInput() };

	return GetCardIndexResponse(input, CardAssignment::PLAYED);
}


const Response GameResponse::GetMatchPlayedCardPromptResponse()
{
	const std::string input{ GetInput() };

	Response response{ Response::NONE };

	// Can change played card response.
	response = GetCardChangeResponse(input);

	if (response == Response::NONE)
	{
		response = GetCardIndexResponse(input, CardAssignment::FIELD);
	}

	return response;
}


const Response GameResponse::GetCardChangeResponse(const std::string input)
{
	switch (input[0])
	{
	case 'c':
	case 'C':
		return Response::CHANGE_CARD;
	default:
		return Response::NONE;
	}
}


const Response GameResponse::GetMatchDrawnCardPromptResponse()
{
	const std::string input{ GetInput() };

	return GetCardIndexResponse(input, CardAssignment::FIELD);
}


const Response GameResponse::GetDecideKoiKoiPromptResponse()
{
	const std::string input{ GetInput() };

	return GetDecideKoiKoiResponse(input);
}


const Response GameResponse::GetDecideKoiKoiResponse(const std::string input)
{
	switch (input[0])
	{
	case 'k':
	case 'K':
		return Response::KOI_KOI;
	case 's':
	case 'S':
		return Response::SHOBU;
	default:
		return Response::NONE;
	}
}


const std::string GameResponse::GetInput()
{
	std::string input{};

	while (input.length() < 1)
	{
		std::getline(std::cin, input);
	}

	return input;
}


const Response GameResponse::GetCardIndexResponse(const std::string& input, const CardAssignment& card_assignment)
{
	switch (GetCardIndexResult(input, card_assignment))
	{
	case Result::OK:
		return Response::CONTINUE;
	case Result::INVALID:
		return Response::NONE;
	default:
		throw 1;
	}
}


const Result GameResponse::GetCardIndexResult(const std::string& input, const CardAssignment& card_assignment)
{
	// Extract index form input and confirm if it is valid with result.
	std::string extracted_index{ GetIndexFromInput(input) };
	Result result{ GetExtractedIndexResult(extracted_index) };

	m_view.ShowInputResult(input, result);

	// If valid, store index of selected card.
	if (result == Result::OK)
	{
		int card_index = std::stoi(extracted_index);
		m_model.SetCardDisplayIndex(card_assignment, card_index);
	}

	return result;
}


const std::string GameResponse::GetIndexFromInput(const std::string& input)
{
	std::string index{};

	// Copy each character into index if it is a number (ASCII decimal code 48 to 57).
	for (const char& character : input)
	{
		int decimal_code{ static_cast<int>(character) };

		if (decimal_code >= 48 && decimal_code <= 57)
		{
			index += character;
		}
		else // Stop at first non-numeric character.
		{
			break;
		}

		// Will only ever need 2 digits.
		if (index.length() == 2)
		{
			break;
		}
	}

	return index;
}


const Result GameResponse::GetExtractedIndexResult(const std::string& extracted_index)
{
	// If extracted_index has at least 1 number copied into it, it is valid input.
	if (extracted_index.length() > 0)
	{
		return Result::OK;
	}
	else
	{
		return Result::INVALID;
	}
}