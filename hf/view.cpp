#include "view.h"

#include <iostream>


void View::ShowField(const std::vector<Card>& field) const
{
	std::cout << "\nFIELD CONTAINS:\n";
	
	int card_index{ 0 };
	for (const Card& card : field)
	{
		std::cout << ++card_index << ": ";
		ShowCard(card);
		std::cout << '\n';
	}
}


void View::ShowHand(const std::vector<Card>& hand) const
{
	std::cout << "\nHAND CONTAINS:\n";

	int card_index{ 0 };
	for (const Card& card : hand)
	{
		std::cout << ++card_index << ": ";
		ShowCard(card);
		std::cout << '\n';
	}
}


void View::ShowCard(const Card& card) const
{
	std::cout << card.GetDisplayMonth()	<< " "
		<< card.GetDisplayCategory() << " "
		<< card.GetDisplayDetail();
}


void View::ShowDrawnCard(const Card& drawn_card) const
{
	std::cout << "\nDRAWN CARD IS:\n";
	std::cout << drawn_card.GetDisplayMonth() << " " << drawn_card.GetDisplayCategory() << " " << drawn_card.GetDisplayDetail() << '\n';
}


void View::ShowPrompt(const Prompt& prompt) const
{
	switch (prompt)
	{
	case Prompt::PLAY_CARD:
		ShowPlayCardPrompt();
		break;
	case Prompt::MATCH_PLAYED_CARD:
		ShowMatchPlayedCardPrompt();
		break;
	case Prompt::MATCH_DRAWN_CARD:
		ShowMatchDrawnCardPrompt();
		break;
	case Prompt::DECIDE_KOIKOI:
		ShowDecideKoiKoiPrompt();
	default:
		break;
	}
}


void View::ShowPlayCardPrompt() const
{
	std::cout << "\nEnter card ID # in hand to play: ";
}


void View::ShowMatchPlayedCardPrompt() const
{
	std::cout << "\nEnter card ID # on field to match with (enter 0 if no match), or [C]hange played card: ";	
}


void View::ShowMatchDrawnCardPrompt() const
{
	std::cout << "\nEnter card ID # on field to match with (enter 0 if no match): ";
}


void View::ShowDecideKoiKoiPrompt() const
{
	std::cout << "\nDeclare [K]oi-koi or [S]hobu: ";
}


void View::ShowInputResult(const std::string& input, const Result& result) const
{
	if (result == Result::OK)
	{
		std::cout << "Accepted: " << input << '\n';
	}
	else
	{
		std::cout << "Rejected: " << input << '\n';
	}
}


void View::ShowMatchMessage(const Result& result) const
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
	else if (result == Result::AVAILABLE_MATCH)
	{
		std::cout << "\n* * * * * * * * * * * * * * * *";
		std::cout << "\n* Played card can be matched. *";
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
		std::cout << "\n* * * * * * * * * * * * * *";
		std::cout << "\n* Selection is not valid. *";
		std::cout << "\n* * * * * * * * * * * * * *\n";
	}
}


void View::ShowPlayerTurn(const int active_player_id) const
{	
	std::cout << "\n*** PLAYER " << (active_player_id + 1) << " : START TURN ***\n";
}


void View::ShowCaptureIntro(const int player_id) const
{
	std::cout << "\n*** PLAYER " << (player_id + 1) << " CAPTURES ***\n";
}


void View::ShowCaptureUpdate() const
{
	std::cout << "\n*** NEW YAKU FROM CAPTURE ***\n";
}


void View::ShowCaptures(const std::vector<Card>& hand, const std::vector<Yaku>& yakus) const
{	
	ShowCapturesByCategory(Category::BRIGHT, hand, yakus);
	ShowCapturesByCategory(Category::ANIMAL, hand, yakus);
	ShowCapturesByCategory(Category::RIBBON, hand, yakus);
	ShowCapturesByCategory(Category::KASU, hand, yakus);
}


void View::ShowEmptyCaptureMessage() const
{
	std::cout << "No captures yet!";
}


void View::ShowCapturesByCategory(const Category& filter_category, const std::vector<Card>& hand, const std::vector<Yaku>& yakus) const
{
	// List all cards in category.
	if (ShowCardsInCategory(filter_category, hand))
	{
		std::cout << '\n';
	}
	else
	{
		return;
	}

	// List yakus and points for category.
	if (ShowYakusInCategory(filter_category, yakus))
	{
		return;
	}
	else
	{
		std::cout << "No Yaku in category.\n";
	}
}


const bool View::ShowCardsInCategory(const Category& filter_category, const std::vector<Card>& hand) const
{
	bool has_card_in_category{ false };
	for (const Card& card : hand)
	{
		if (card.GetCategory() == filter_category)
		{
			if (has_card_in_category)
			{
				std::cout << " | ";
			}
			has_card_in_category = true;
			ShowCard(card);
		}
	}

	return has_card_in_category;
}


const bool View::ShowYakusInCategory(const Category& filter_category, const std::vector<Yaku>& yakus) const
{
	bool has_yaku_in_category{ false };
	for (const Yaku& yaku : yakus)
	{
		if (yaku.GetCategory() == filter_category)
		{
			has_yaku_in_category = true;
			ShowYaku(yaku);
		}
	}

	return has_yaku_in_category;
}


void View::ShowYaku(const Yaku& yaku) const
{
	std::cout << yaku.GetDisplayYakuName()
		<< " (" << yaku.GetScore() << " mon)"
		<< '\n';
}


void View::ShowRoundWinner(const int rounds_played, const int active_player_id) const
{
	std::cout << "Player " << active_player_id + 1 << " wins round " << rounds_played << "!";
}


void View::ShowGameWinner(const int player_id) const // default = -1
{
	if (player_id == -1)
	{
		std::cout << "The game ends in a draw! 0o0";
	}
	else
	{
		std::cout << "Player " << player_id + 1 << " wins the game!";
	}
}


void View::ShowScore(const int round_score, const int total_score) const
{
	std::cout << "Round score: " << round_score;
	std::cout << "\nTotal score: " << total_score;
}