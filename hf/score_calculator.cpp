#include "score_calculator.h"

#include "yaku.h"
#include "game_enum.h"


void ScoreCalculator::CalculateNewScore(Model& model, const PlayerIs& player_is)
{
	m_player_is = player_is;

	std::vector<Card> hand{ model.GetCaptures(player_is) };

	std::vector<Card> brights;
	std::vector<Card> animals;
	std::vector<Card> ribbons;
	std::vector<Card> kasu;

	// Sort cards by category.
	for (const Card& card : hand)
	{
		switch (card.GetCategory())
		{
		case Category::BRIGHT:
			brights.push_back(card);
			break;
		case Category::ANIMAL:
			animals.push_back(card);
			break;
		case Category::RIBBON:
			ribbons.push_back(card);
			break;
		case Category::KASU:
			kasu.push_back(card);
			break;
		}
	}

	// Score each category (store yaku name and score with player).
	ScoreBrights(model, brights);
	ScoreAnimals(model, animals);
	ScoreRibbons(model, ribbons);
	ScoreViewings(model, animals, brights);
	ScoreKasu(model, kasu);

	// Finally, calculate new score based on yakus.
	int new_score{ 0 };
	std::vector<Yaku> yakus{ model.GetYakus(player_is) };
	for (const Yaku& yaku : yakus)
	{
		new_score += yaku.GetScore();
	}

	model.SetRoundScore(new_score, player_is);
}


void ScoreCalculator::ScoreBrights(Model& model, const std::vector<Card>& brights)
{
	int size{ static_cast<int>(brights.size()) };

	// Nothing to score.
	if (size < 3)
	{
		return;
	}

	// Get details for special scoring.
	bool is_rainman_captured{ false };
	for (const Card& card : brights)
	{
		if (card.GetDetail() == Detail::RAINMAN)
		{
			is_rainman_captured = true;
			break;
		}
	}

	// Scoring.
	if (size == 5)
	{
		model.AddYaku(Yaku{ Category::BRIGHT, YakuName::BRIGHT_5, 10 }, m_player_is);
	}
	else if (size == 4 && !is_rainman_captured)
	{
		model.AddYaku(Yaku{ Category::BRIGHT,YakuName::BRIGHT_4, 8 }, m_player_is);
	}
	else if (size == 4 && is_rainman_captured)
	{
		model.AddYaku(Yaku{ Category::BRIGHT,YakuName::BRIGHT_4_RAINY, 7 }, m_player_is);
	}
	else if (size == 3 && !is_rainman_captured)
	{
		model.AddYaku(Yaku{ Category::BRIGHT,YakuName::BRIGHT_3, 5 }, m_player_is);
	}
}


void ScoreCalculator::ScoreAnimals(Model& model, const std::vector<Card>& animals)
{
	int size{ static_cast<int>(animals.size()) };

	// Nothing to score.
	if (size < 3)
	{
		return;
	}

	// Get details for special scoring.
	int ino_shika_cho_count{ 0 };
	for (const Card& card : animals)
	{
		Detail detail{ card.GetDetail() };

		if (detail == Detail::BOAR
			|| detail == Detail::DEER
			|| detail == Detail::BUTTERFLY)
		{
			++ino_shika_cho_count;
		}
	}

	// Scoring.
	if (ino_shika_cho_count == 3)
	{
		model.AddYaku(Yaku{ Category::ANIMAL, YakuName::ANIMAL_ISO, 5 + GetExtendedYakuScore(size, 3) }, m_player_is);
	}
	else if (size >= 5)
	{
		model.AddYaku(Yaku{ Category::ANIMAL, YakuName::ANIMAL_TANE, 1 + GetExtendedYakuScore(size, 5) }, m_player_is);
	}
}


void ScoreCalculator::ScoreRibbons(Model& model, const std::vector<Card>& ribbons)
{
	int size{ static_cast<int>(ribbons.size()) };

	// Nothing to score.
	if (size < 3)
	{
		return;
	}

	// Get details for special scoring.
	int poem_count{ 0 };
	int blue_count{ 0 };
	for (const Card& card : ribbons)
	{
		if (card.GetDetail() == Detail::POEM)
		{
			++poem_count;
		}
		else if (card.GetDetail() == Detail::BLUE)
		{
			++blue_count;
		}
	}

	// Scoring.
	if (poem_count == 3 && blue_count == 3)
	{
		model.AddYaku(Yaku{ Category::RIBBON, YakuName::RIBBON_COMBO, 10 + GetExtendedYakuScore(size, 6) }, m_player_is);
	}
	else if (poem_count == 3)
	{
		model.AddYaku(Yaku{ Category::RIBBON,YakuName::RIBBON_AKATAN, 5 + GetExtendedYakuScore(size, 3) }, m_player_is);
	}
	else if (blue_count == 3)
	{
		model.AddYaku(Yaku{ Category::RIBBON,YakuName::RIBBON_AOTAN, 5 + GetExtendedYakuScore(size, 3) }, m_player_is);
	}
	else if (size >= 5)
	{
		model.AddYaku(Yaku{ Category::RIBBON,YakuName::RIBBON_TANZAKU, 1 + GetExtendedYakuScore(size, 5) }, m_player_is);
	}
}


void ScoreCalculator::ScoreViewings(Model& model, const std::vector<Card>& animals, const std::vector<Card>& brights)
{
	// Nothing to score.
	if (animals.size() == 0 || brights.size() == 0)
	{
		return;
	}

	// Check for sake cup.
	bool is_sake_captured{ false };
	for (const Card& card : animals)
	{
		if (card.GetDetail() == Detail::SAKE)
		{
			is_sake_captured = true;
		}
	}

	if (!is_sake_captured)
	{
		return;
	}

	// Check if moon or sakura curtain are captured and score if they are.
	for (const Card& card : brights)
	{
		Detail detail{ card.GetDetail() };

		if (detail == Detail::MOON)
		{
			model.AddYaku(Yaku{ Category::BRIGHT, YakuName::VIEWING_MOON, 5 }, m_player_is);
		}
		else if (detail == Detail::SAKURA_CURTAIN)
		{
			model.AddYaku(Yaku{ Category::BRIGHT, YakuName::VIEWING_FLOWER, 5 }, m_player_is);
		}
	}
}


void ScoreCalculator::ScoreKasu(Model& model, const std::vector<Card>& kasu)
{
	int size{ static_cast<int>(kasu.size()) };

	// Nothing to score.
	if (size < 10)
	{
		return;
	}

	// Scoring
	if (size >= 10)
	{
		model.AddYaku(Yaku{ Category::KASU, YakuName::KASU, 1 + GetExtendedYakuScore(size, 10) }, m_player_is);
	}
}


const int ScoreCalculator::GetExtendedYakuScore(const int size, const int set_end) const
{
	if (size <= set_end)
	{
		return 0;
	}
	else
	{
		return (size - set_end);
	}
}