#pragma once

#include <vector>
#include <string>

#include "card.h"
#include "yaku.h"
#include "game_enum.h"
#include "view_enum.h"


class View
{
public:
	View() { };

	void ShowField(const std::vector<Card>& field) const;
	void ShowHand(const std::vector<Card>& hand) const;	
	void ShowDrawnCard(const Card& drawn_card) const;

	void ShowInputResult(const std::string& input, const Result& result) const;	
	
	void ShowPlayerTurn(const int active_player_id) const;

	void ShowPrompt(const Prompt& prompt) const;

	void ShowCaptureIntro(const int player_id) const;
	void ShowCaptureUpdate() const;
	void ShowEmptyCaptureMessage() const;
	void ShowCaptures(const std::vector<Card>& hand, const std::vector<Yaku>& yakus) const;

	void ShowMatchMessage(const Result& result) const;
	void ShowStateMessage(const State& state, const int player_index) const;

	void ShowRoundWinner(const int rounds_played, const int winning_player_id) const;
	void ShowRoundTie(const int rounds_played) const;
	void ShowScore(const int player_id, const int round_score, const int total_score) const;
	void ShowGameWinner(const int winning_player_id = -1) const;

private:
	void ShowCard(const Card& card) const;
	
	void ShowPlayCardPrompt() const;
	void ShowMatchPlayedCardPrompt() const;
	void ShowMatchDrawnCardPrompt() const;
	void ShowDecideKoiKoiPrompt() const;
	void ShowDecideRematchPrompt() const;

	void ShowCapturesByCategory(const Category& filter_category, const std::vector<Card>& hand, const std::vector<Yaku>& yakus, const bool has_newline) const;
	const bool ShowCardsInCategory(const Category& filter_category, const std::vector<Card>& hand) const;
	const bool ShowYakusInCategory(const Category& filter_category, const std::vector<Yaku>& yakus) const;
	void ShowYaku(const Yaku& yaku) const;
};