#include "game_outcome.h"


GameOutcome::GameOutcome(Model& model, View& view)
	: m_model{ model }
	, m_view{ view }
{	}


const Outcome GameOutcome::GetOutcome(const Result& result)
{
	switch (m_model.GetPhase())
	{
	case Phase::MATCH_FROM_HAND:
	case Phase::MATCH_FROM_DRAW:
		return GetMatchOutcome(result);
	case Phase::SCORING:
		return GetScoringOutcome(result);
	default:
		throw 1;
	}
}


const Outcome GameOutcome::GetMatchOutcome(const Result& result)
{
	m_view.ShowMatchMessage(result);

	switch (result)
	{
	case Result::OK:
		CaptureCards();
		return Outcome::CONTINUE;
	case Result::NO_MATCH:
		AddPlayedCardToField();
		return Outcome::CONTINUE;
	default:
		return Outcome::REPEAT;
	}
}


void GameOutcome::CaptureCards()
{
	const int played_card_index{ m_model.GetCardDisplayIndex(CardAssignment::PLAYED) - 1 };
	const int field_card_index{ m_model.GetCardDisplayIndex(CardAssignment::FIELD) - 1 };

	m_model.AddToCaptures(GetPlayedCard(played_card_index));
	m_model.AddToCaptures(GetFieldCard(field_card_index));
}


void GameOutcome::AddPlayedCardToField()
{
	const int played_card_index{ m_model.GetCardDisplayIndex(CardAssignment::PLAYED) - 1 };

	m_model.AddToField(GetPlayedCard(played_card_index));
}


const Card GameOutcome::GetPlayedCard(const int played_card_index) const
{
	return (m_model.GetPhase() == Phase::MATCH_FROM_HAND
		? m_model.TakeFromHand(played_card_index)
		: m_model.GetDrawnCard()
		);
}


const Card GameOutcome::GetFieldCard(const int field_card_index) const
{
	return (m_model.TakeFromField(field_card_index));
}


const Outcome GameOutcome::GetScoringOutcome(const Result& result)
{
	switch (result)
	{
	case Result::OK:
		return Outcome::CONTINUE;
	case Result::END_ROUND:
		m_model.SetRoundStatus(false);
		return Outcome::CONTINUE;
	default:
		throw 1;
	}
}