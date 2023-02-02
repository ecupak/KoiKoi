#pragma once

#include <vector>
#include <string>

#include "card.h"
#include "game_enum.h"
#include "view_enum.h"


class View
{
public:
	View() { };

	void ShowField(const std::vector<Card>& field) const;
	void ShowHand(const std::vector<Card>& hand) const;	
	void ShowDrawnCard(const Card& drawn_card) const;

	const Response GetGameResponse(const Phase& phase, int& card_played_index, int& card_on_field_index);
	
	void ShowMessage(const Result& result) const;
	void ShowPlayerTurn(const int active_player_id) const;

	void ShowPrompt(const Prompt& prompt) const;

private:
	const Response GetResponse(const Prompt& prompt, const Phase& phase, int* card_index);
	
	
	const std::string GetInput();

	const Response GetResponseFromInput(const Phase& phase, int* card_index);
	const Response MainSwitch(const char first_character);
	const Response MatchSwitch(const std::string& input, const Phase& phase, int* card_index);

	void ShowPlayCardPrompt() const;
	void ShowMatchPlayedCardPrompt() const;
	void ShowMatchDrawnCardPrompt() const;
	void ShowCapturedCardsPrompt() const;
	
	const bool IsNewScreenRequested(const Response& response);
		
	const Result GetCardIndex(const std::string& input, int* card_index);
};