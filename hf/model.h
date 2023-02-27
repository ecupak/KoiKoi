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
	const std::vector<Card>& GetHand(const PlayerIs& player_is) const;
	const std::vector<Card>& GetCaptures(const PlayerIs& player_is) const;

	void SetCardDisplayIndex(const CardAssignment& card_assignment, const int card_index);
	const int GetCardDisplayIndex(const CardAssignment& card_assignment);

	const Card& TakeFromHand(const int card_in_hand_index);
	const Card& TakeFromField(const int card_on_field_index);

	void AddToField(const Card& card);
	void AddToCaptures(const Card& card);

	void SwapActivePlayer();
	const int GetPlayerIndex(const PlayerIs& player_is) const;

	void SetRoundScore(const int score, const PlayerIs& player_is);
	const int GetRoundScore(const PlayerIs& player_is) const;
	
	void IncreaseTotalScore(const int score, const PlayerIs& player_is);
	void IncreaseDealerTotalScore(const int dealer_advantage);
	const int GetTotalScore(const PlayerIs& player_is) const;

	void ClearYakus();
	void AddYaku(const Yaku& yaku, const PlayerIs& player_is);
	const std::vector<Yaku>& GetYakus(const PlayerIs& player_is) const;

	void DrawCardToMatch();
	const Card& GetDrawnCard() const;

	void SetPhase(const Phase& phase);
	const Phase& GetPhase() const;

	void SetScreen(const Screen& screen);
	const Screen& GetScreen() const;

	void SetRoundStatus(const bool is_round_active);
	const bool IsRoundActive() const;

	void SetPlayerKoiKoi(const bool is_koi_koi_active, const PlayerIs& player_is);
	const bool GetPlayerKoiKoi(const PlayerIs& player_is) const;
	const bool IsKoiKoiActive() const;	

private:
	void CreateDrawPile();
	void ShuffleDrawPile();
	const Card DrawCard();
	void DealCards();

	void SetDealer();

	void StartTurn(Player& player);


	std::vector<Card> m_draw_pile;
	std::vector<Card> m_field;

	int m_played_card_display_index{ -1 };
	int m_field_card_display_index{ -1 };

	Card m_drawn_card;

	Player m_player_1;
	Player m_player_2;	
	Player* m_players[2];

	int m_active_player_index{ 0 };
	int m_inactive_player_index{ 1 };
	int m_dealer_index{ 0 };
	int m_player_count{ 2 };

	Phase m_phase{ Phase::NONE };
	Screen m_screen{ Screen::NONE };
	bool m_is_round_active{ true };
};