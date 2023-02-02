#pragma once

#include "player.h"
#include "card.h"
#include "game_enum.h"


class Model
{
public:
	Model();

	void PrepareNewRound();
	
	void ClearCards();
	void ClearScores();	

	const std::vector<Card>& GetField() const;
	const std::vector<Card>& GetPlayerHand() const;

	const Card& TakeFromHand(const int card_in_hand_index);
	const Card& TakeFromField(const int card_on_field_index);

	void AddToField(const Card& card);
	void AddToCollection(const Card& card);

	void SwapActivePlayer();
	const int GetActivePlayer() const;

	void SetPlayerScore(const int score);
	const int GetPlayerScore() const;
	
	void ClearYakus();
	void AddYaku(const Yaku& yaku);
	const std::vector<Yaku>& GetYakus() const;

	void GetNextDrawnCard();
	const Card& GetDrawnCard() const;

	void SetPhase(const Phase& phase);
	const Phase& GetPhase() const;

	void SetScreen(const Screen& screen);
	const Screen& GetScreen() const;

private:
	void CreateDrawPile();
	void ShuffleDrawPile();
	const Card DrawCard();
	void DealCards();

	void StartTurn(Player& player);

	std::vector<Card> m_draw_pile;
	std::vector<Card> m_field;

	Card m_drawn_card;

	Player m_player_1;
	Player m_player_2;	
	Player* m_players[2];

	int m_active_player_index{ 0 };
	int m_player_count{ 2 };

	Phase m_phase{ Phase::NONE };
	Screen m_screen{ Screen::NONE };
};