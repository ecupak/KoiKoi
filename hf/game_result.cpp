#include "game_result.h"

GameResult::GameResult(Model& model)
	: m_model{ model }
{	}


const Result GameResult::GetResult(const Response& response)
{
	switch (m_model.GetPhase())
	{
	case Phase::MATCH_FROM_HAND:
	case Phase::MATCH_FROM_DRAW:
		return GetMatchResult();
	case Phase::SCORING:
		return GetScoringResult(response);
	default:
		throw 1;
	}
}


const Result GameResult::GetMatchResult() const
{
	// Validate field card first to detect a 'no match' situation.
	Result field_card_result{ GetFieldCardResult() };

	if (IsResultNotOK(field_card_result))
	{
		return field_card_result; // NO_MATCH, AVAILABLE_MATCH, INVALID.
	}

	// Validate the played card.
	Result played_card_result{ GetPlayedCardResult() };

	if (IsResultNotOK(played_card_result))
	{
		return played_card_result; // INVALID.
	}

	// Confirm cards match.
	if (GetCaptureResult())
	{
		return Result::OK;
	}
	else
	{
		return Result::MISMATCH;
	}
}


const bool GameResult::IsResultNotOK(const Result& result) const
{
	return (result != Result::OK);
}


const Result GameResult::GetFieldCardResult() const
{
	Result field_card_result{ GetFieldCardValidationResult() };

	switch (field_card_result)
	{
	case Result::NO_MATCH:
		return GetNoMatchConfirmationResult();
	default:
		return field_card_result;
	}
}


const Result GameResult::GetFieldCardValidationResult() const
{
	const int field_card_display_index{ m_model.GetCardDisplayIndex(CardAssignment::FIELD) };

	if (HasPlayerDeclaredNoMatch(field_card_display_index))
	{
		return Result::NO_MATCH;
	}

	if (IsCardInRange(field_card_display_index, static_cast<int>(m_model.GetField().size())))
	{
		return Result::OK;
	}
	else
	{
		return Result::INVALID;
	}
}


const bool GameResult::HasPlayerDeclaredNoMatch(const int field_card_display_index) const
{
	return field_card_display_index == 0;
}


const bool GameResult::IsCardInRange(const int card_display_index, const int range_max) const
{
	return (card_display_index >= 1 && card_display_index <= range_max);
}


const Result GameResult::GetNoMatchConfirmationResult() const
{
	const Card& card_to_play{ GetCardToPlay() };
	std::vector<Card> cards_on_field{ m_model.GetField() };

	for (const Card& matchable_card : cards_on_field)
	{
		if (card_to_play.GetMonth() == matchable_card.GetMonth())
		{
			return Result::AVAILABLE_MATCH;
		}
	}

	return Result::NO_MATCH;
}


const Card& GameResult::GetCardToPlay() const
{
	switch (m_model.GetPhase())
	{
	case Phase::MATCH_FROM_HAND:
		return m_model.GetHand(PlayerIs::ACTIVE).at(m_model.GetCardDisplayIndex(CardAssignment::PLAYED) - 1);
	case Phase::MATCH_FROM_DRAW:
		return  m_model.GetDrawnCard();
	default:
		throw 1;
	}
}


const Result GameResult::GetPlayedCardResult() const
{
	if (IsPlayedCardDrawn())
	{
		return Result::OK;
	}

	const int played_card_display_index{ m_model.GetCardDisplayIndex(CardAssignment::PLAYED) };

	if (IsCardInRange(played_card_display_index, static_cast<int>(m_model.GetHand(PlayerIs::ACTIVE).size())))
	{
		return Result::OK;
	}

	return Result::INVALID;
}


const bool GameResult::IsPlayedCardDrawn() const
{
	return (m_model.GetPhase() == Phase::MATCH_FROM_DRAW);
}


const bool GameResult::GetCaptureResult() const
{
	switch (m_model.GetPhase())
	{
	case Phase::MATCH_FROM_HAND:
		return DoesPlayedMatchField();
	case Phase::MATCH_FROM_DRAW:
		return DoesDrawnMatchField();
	default:
		throw 1;
	}
}


const bool GameResult::DoesPlayedMatchField() const
{
	const int played_card_index{ m_model.GetCardDisplayIndex(CardAssignment::PLAYED) - 1 };
	const int field_card_index{ m_model.GetCardDisplayIndex(CardAssignment::FIELD) - 1 };

	return m_model.GetHand(PlayerIs::ACTIVE).at(played_card_index).GetMonth() == m_model.GetField().at(field_card_index).GetMonth();
}


const bool GameResult::DoesDrawnMatchField() const
{
	const int field_card_index{ m_model.GetCardDisplayIndex(CardAssignment::FIELD) - 1 };

	return m_model.GetDrawnCard().GetMonth() == m_model.GetField().at(field_card_index).GetMonth();
}


const Result GameResult::GetScoringResult(const Response& response)
{
	switch (response)
	{
	case Response::CONTINUE: // No new yaku.
		return Result::OK;
	case Response::KOI_KOI:
		// Set other player koi-koi to true (double points if they score).
		m_model.SetPlayerKoiKoi(true, PlayerIs::INACTIVE);
		return Result::OK;
	case Response::SHOBU:
		return Result::END_ROUND;
	default:
		throw 1;
	}
}