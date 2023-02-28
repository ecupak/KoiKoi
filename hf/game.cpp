#include "game.h"
#include "deck.h"


Game::Game(Model& model, View& view)
	: m_model{ model }
	, m_view{ view }
	, m_game_setup{ model, view }
	, m_game_response{ model, view }
	, m_game_result{ model }
	, m_game_outcome{ model, view }
	, m_game_rematch{ view }
{	}


void Game::Begin()
{
	bool is_rematch_requested{ false };

	do
	{
		is_rematch_requested = StartMatch();

	} while (is_rematch_requested);
}


const bool Game::StartMatch()
{
	int rounds_played{ 0 };
	int rounds_to_play{ 3 }; // 12 or 6
	
	do
	{
		Result setup_result{ m_game_setup.Setup() };
		
		if (setup_result == Result::OK)
		{
			StartRound();
		}
		
		++rounds_played;

		ProcessRoundResults(rounds_played);
		
	} while (rounds_played < rounds_to_play);

	ShowGameResult();
		
	return WillPlayAgain();
}


void Game::StartRound()
{
	while (IsRoundActive())
	{
		TakeTurn();

		if (IsRoundActive())
		{
			AdvanceTurn();
		}
	}
}


const bool Game::IsRoundActive() const
{
	return (m_model.IsRoundActive());
}


void Game::TakeTurn()
{
	StartTurn(); // Show captures and field.

	while (true)
	{
		ShowCards();
		ProcessResponse(); // Show prompt and get/process input.
		AdvancePhase(); // match from hand > match from draw > scoring > end turn

		if (IsPhase(Phase::END_TURN))
		{
			break;
		}
	}
}


void Game::StartTurn()
{
	m_model.SetPhase(Phase::MATCH_FROM_HAND);

	m_view.ShowPlayerTurn(m_model.GetPlayerIndex(PlayerIs::ACTIVE));

	ShowCaptureReview(PlayerIs::ACTIVE);
	ShowCaptureReview(PlayerIs::INACTIVE);
}


void Game::ShowCaptureReview(const PlayerIs& player_is)
{
	m_view.ShowCaptureIntro(m_model.GetPlayerIndex(player_is));

	if (m_model.GetCaptures(player_is).size() > 0)
	{		
		m_view.ShowCaptures(m_model.GetCaptures(player_is), m_model.GetYakus(player_is));
	}
	else
	{
		m_view.ShowEmptyCaptureMessage();
	}
}


const bool Game::IsPhase(const Phase& phase) const
{
	return (m_model.GetPhase() == phase);
}


void Game::ShowCards() const
{
	switch (m_model.GetPhase())
	{
	case Phase::MATCH_FROM_HAND:
		m_view.ShowHand(m_model.GetHand(PlayerIs::ACTIVE));
		m_view.ShowField(m_model.GetField());
		break;
	case Phase::MATCH_FROM_DRAW:
		m_view.ShowDrawnCard(m_model.GetDrawnCard());
		m_view.ShowField(m_model.GetField());
		break;
	}
}


void Game::ProcessResponse()
{
	Outcome outcome{ Outcome::REPEAT };

	while (outcome == Outcome::REPEAT)
	{
		Response response{ m_game_response.GetResponse() }; // returns CONTINUE, KOIKOI, SHOBU.
		Result result{ m_game_result.GetResult(response) }; // returns OK, NO_MATCH, AVAILABLE_MATCH, MISMATCH, INVALID
		outcome = m_game_outcome.GetOutcome(result); // returns CONTINUE or TRY_AGAIN.
	}
}


void Game::AdvancePhase()
{
	switch (m_model.GetPhase())
	{
	case Phase::MATCH_FROM_HAND:
		m_model.SetPhase(Phase::MATCH_FROM_DRAW);
		m_model.DrawCardToMatch();
		break;
	case Phase::MATCH_FROM_DRAW:
		m_model.SetPhase(Phase::SCORING);
		break;
	case Phase::SCORING:
		m_model.SetPhase(Phase::END_TURN);
		break;
	}
}


void Game::AdvanceTurn()
{
	m_model.SwapActivePlayer();
}


void Game::ProcessRoundResults(const int rounds_played)
{
	SaveRoundScore();
	
	ShowRoundScore();	

	ShowRoundResult(rounds_played);
}


void Game::SaveRoundScore()
{
	m_model.IncreaseTotalScore(m_model.GetRoundScore(PlayerIs::ACTIVE), PlayerIs::ACTIVE);
	m_model.IncreaseTotalScore(m_model.GetRoundScore(PlayerIs::INACTIVE), PlayerIs::INACTIVE);
}


void Game::ShowRoundScore()
{
	ShowScore(PlayerIs::ACTIVE);
	ShowScore(PlayerIs::INACTIVE);
}


void Game::ShowScore(const PlayerIs& player_is)
{
	ShowCaptureReview(player_is);
	m_view.ShowScore(m_model.GetPlayerIndex(player_is), m_model.GetRoundScore(player_is), m_model.GetTotalScore(player_is));
}


void Game::ShowRoundResult(const int rounds_played)
{
	int score_active{ m_model.GetRoundScore(PlayerIs::ACTIVE) };
	int score_inactive{ m_model.GetRoundScore(PlayerIs::INACTIVE) };
	
	PlayerIs winning_player{ score_active > score_inactive 
		? PlayerIs::ACTIVE 
		: score_inactive > score_active
			? PlayerIs::INACTIVE 
			: PlayerIs::NONE 
	};

	if (winning_player == PlayerIs::NONE)
	{
		m_view.ShowRoundTie(rounds_played);
	}
	else
	{
		m_view.ShowRoundWinner(rounds_played, m_model.GetPlayerIndex(winning_player));
	}
}


void Game::ShowGameResult()
{
	int active_score{ m_model.GetTotalScore(PlayerIs::ACTIVE) };
	int inactive_score{ m_model.GetTotalScore(PlayerIs::INACTIVE) };

	if (active_score > inactive_score)
	{
		m_view.ShowGameWinner(m_model.GetPlayerIndex(PlayerIs::ACTIVE));
	}
	else if (inactive_score > active_score)
	{
		m_view.ShowGameWinner(m_model.GetPlayerIndex(PlayerIs::INACTIVE));
	}
	else
	{
		m_view.ShowGameWinner();
	}
}


const bool Game::WillPlayAgain() const
{
	Response response{ m_game_rematch.GetResponse() };
	
	return response == Response::REMATCH;
}
