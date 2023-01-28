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


private:
	const Response GetResponse(const Prompt& prompt, const Phase& phase, int* card_index);
	
	void ShowPrompt(const Prompt& prompt, const Phase& phase) const;
	const std::string GetInput();

	const Response GetResponseFromInput(const Phase& phase, int* card_index);
	const Response MainSwitch(const char first_character);
	const Response MatchSwitch(const std::string& input, const Phase& phase, int* card_index);

	void ShowPlayedCardPrompt() const;
	void ShowFieldCardPrompt(const Phase& phase) const;
	void ShowMyCollectionPrompt() const;
	void ShowTheirCollectionPrompt() const;
	
	const bool IsNewScreenRequested(const Response& response);
		
	const Result GetCardIndex(const std::string& input, int* card_index);
};