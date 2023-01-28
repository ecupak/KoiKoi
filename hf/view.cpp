#include "view.h"

#include <iostream>


void View::ShowField(const std::vector<Card>& field) const
{
	std::cout << "\nFIELD CONTAINS:\n";
	
	int card_index{ 0 };
	for (const Card& card : field)
	{
		std::cout << ++card_index << ": " << card.GetDisplayMonth() << " " << card.GetDisplayCategory() << " " << card.GetDisplayDetail() << '\n';
	}
}


void View::ShowHand(const std::vector<Card>& hand) const
{
	std::cout << "\nHAND CONTAINS:\n";

	int card_index{ 0 };
	for (const Card& card : hand)
	{
		std::cout << ++card_index << ": " << card.GetDisplayMonth() << " " << card.GetDisplayCategory() << " " << card.GetDisplayDetail() << '\n';
	}
}


void View::ShowDrawnCard(const Card& drawn_card) const
{
	std::cout << "\nDRAWN CARD IS:\n";
	std::cout << drawn_card.GetDisplayMonth() << " " << drawn_card.GetDisplayCategory() << " " << drawn_card.GetDisplayDetail() << '\n';
}


const Response View::GetGameResponse(const Phase& phase, int& card_played_index, int& card_on_field_index)
{
	Response response{ Response::NONE };
	
	// Do while final reponse is CHANGE_CARD (stop when the final response is CONTINUE or return early if new screen requested).
	do
	{
		// Player only selects card to play during 'match from hand' phase.
		if (phase == Phase::MATCH_FROM_HAND)
		{
			response =  GetResponse(Prompt::PLAYED_CARD, phase, &card_played_index);

			// Skip asking for field card if player wants to view a different screen.
			if (IsNewScreenRequested(response))
			{
				return response;
			}
		}

		// Will always need to match card from hand or drawn card to a field card.
		response = GetResponse(Prompt::FIELD_CARD, phase, &card_on_field_index);

	} while (response == Response::CHANGE_CARD);

	return response;
}


const bool View::IsNewScreenRequested(const Response& response)
{
	switch (response)
	{
	case Response::VIEW_MY_COLLECTION:
	case Response::VIEW_THEIR_COLLECTION:
		return true;
	default:
		return false;
	}
}


const Response View::GetResponse(const Prompt& prompt, const Phase& phase, int* card_index)
{
	while (true)
	{
		// Display prompt.
		ShowPrompt(prompt, phase);

		// Process response.
		Response response{ GetResponseFromInput(phase, card_index) };

		// If no response, start over.
		if (response != Response::NONE)
		{
			return response;
		}
	}
}


void View::ShowPrompt(const Prompt& prompt, const Phase& phase) const
{
	switch (prompt)
	{
	case Prompt::PLAYED_CARD:
		ShowPlayedCardPrompt();
		break;
	case Prompt::FIELD_CARD:
		ShowFieldCardPrompt(phase);
		break;
	case Prompt::MY_COLLECTION:
		ShowMyCollectionPrompt();
		break;
	case Prompt::THEIR_COLLECTION:
		ShowTheirCollectionPrompt();
		break;
	default:
		break;
	}
}


const Response View::GetResponseFromInput(const Phase& phase, int* card_index)
{
	// Get input.
	std::string input{ GetInput() };

	// Check for a new screen request first.
	Response response{ MainSwitch(input[0]) };

	// If not a screen change, see if player is matching cards.
	if (card_index != nullptr && response == Response::NONE)
	{
		response = MatchSwitch(input, phase, card_index);
	}

	return response;
}


const std::string View::GetInput()
{
	std::string input{};

	do
	{
		std::getline(std::cin, input);

	} while (input.length() < 1);

	return input;
}


const Response View::MainSwitch(const char first_character)
{
	switch (first_character)
	{
	case 'g':
	case 'G':
		return Response::PLAY_FIELD;
	case 'm':
	case 'M':
		return Response::VIEW_MY_COLLECTION;
	case 'o':
	case 'O':
		return Response::VIEW_THEIR_COLLECTION;
	default:
		return Response::NONE;
	}
}


const Response View::MatchSwitch(const std::string& input, const Phase& phase, int* card_index)
{	
	switch (input[0])
	{
	case 'c':
	case 'C':
		// Can only change previous card during 'match from hand' phase.
		return (phase == Phase::MATCH_FROM_HAND
			? Response::CHANGE_CARD
			: Response::NONE
			);
	default:
		// Returns RESULTS. INVALID if not a number. OK if number.
		switch (GetCardIndex(input, card_index))
		{
		case Result::OK:
			return Response::CONTINUE;
		case Result::INVALID:
			return Response::NONE;
		}
	}	
}


const Result View::GetCardIndex(const std::string& input, int* card_index)
{
	std::string index{};

	// Copy each character into index if it is a number (ASCII decimal code 48 to 57).
	for (const char& character : input)
	{
		int decimal_code{ static_cast<int>(character) };
		if (decimal_code >= 48 && decimal_code <= 57)
		{
			index += character;

			// Will only ever need 2 digits.
			if (index.length() == 2)
			{
				break;
			}
		}
		else
		{
			// Stop at first non-numeric character.
			break;
		}
	}
	
	// If index has at least 1 number copied into it, transfer to card_index; was success.
	if (index.length() > 0)
	{
		*card_index = std::stoi(index);
		return Result::OK;
	}
	else
	{
		return Result::INVALID;
	}
}


void View::ShowPlayedCardPrompt() const
{
	std::cout << "\nEnter card ID # in hand to play, or the [letter] of one of these commands:\n";
	std::cout << "View [M]y Collection | View [O]pponent's Collection\n";
}


void View::ShowFieldCardPrompt(const Phase& phase) const
{
	std::cout << "\nEnter card ID # on field to match with (enter 0 if no match), or the [letter] of one of these commands:\n";

	// Only allowed to change played card if selected from hand (vs drawn from deck).
	if (phase == Phase::MATCH_FROM_HAND)
	{
		std::cout << "[C]hange previous input | ";
	}

	std::cout << "View [M]y Collection | View [O]pponent's collection\n";
}


void View::ShowMyCollectionPrompt() const
{
	std::cout << "\nEnter the [letter] of one of these commands:\n";
	std::cout << "Return to [G]ame | View [O]pponent's collection\n";
}


void View::ShowTheirCollectionPrompt() const
{
	std::cout << "\nEnter the [letter] of one of these commands:\n";
	std::cout << "Return to [G]ame | View [M]y Collection\n";
}


void View::ShowMessage(const Result& result) const
{
	if (result == Result::OK)
	{
		std::cout << "\n* * * * * * * * * * * * * * * * * * * * * *";
		std::cout << "\n* Cards captured and added to collection! *";
		std::cout << "\n* * * * * * * * * * * * * * * * * * * * * *\n";

	}
	else if (result == Result::NO_MATCH)
	{
		std::cout << "\n* * * * * * * * * * * * * * * *";
		std::cout << "\n* Played card added to field. *";
		std::cout << "\n* * * * * * * * * * * * * * * *\n";
	}
	else if (result == Result::MISMATCH)
	{
		std::cout << "\n* * * * * * * * * * * * * * * *";
		std::cout << "\n* Selected cards do not match *";
		std::cout << "\n* * * * * * * * * * * * * * * *\n";
	}
	else if (result == Result::INVALID)
	{
		std::cout << "\n* * * * * * * * * * * * * * * * * *";
		std::cout << "\n* Selected card(s) are not valid. *";
		std::cout << "\n* * * * * * * * * * * * * * * * * *\n";
	}
}


void View::ShowPlayerTurn(const int active_player_id) const
{	
	std::cout << "\n*** PLAYER " << (active_player_id + 1) << " : START TURN ***\n";
}