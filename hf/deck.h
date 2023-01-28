#pragma once

#include <array>
#include "card.h"


class Deck
{
public:
	Deck() { };

	const std::array<Card, 48>& GetCards() const { return deck; }

private:
	const std::array<Card, 48> deck
	{
		{
			{0, 1, Category::BRIGHT, Detail::OTHER},
			{1, 1, Category::RIBBON, Detail::POEM},
			{2, 1, Category::KASU, Detail::OTHER},
			{3, 1, Category::KASU, Detail::OTHER},

			{4, 2, Category::ANIMAL, Detail::OTHER},
			{5, 2, Category::RIBBON, Detail::POEM},
			{6, 2, Category::KASU, Detail::OTHER},
			{7, 2, Category::KASU, Detail::OTHER},

			{8, 3, Category::BRIGHT, Detail::SAKURA_CURTAIN},
			{9, 3, Category::RIBBON, Detail::POEM},
			{10, 3, Category::KASU, Detail::OTHER},
			{11, 3, Category::KASU, Detail::OTHER},

			{12, 4, Category::ANIMAL, Detail::OTHER},
			{13, 4, Category::RIBBON, Detail::OTHER},
			{14, 4, Category::KASU, Detail::OTHER},
			{15, 4, Category::KASU, Detail::OTHER},

			{16, 5, Category::ANIMAL, Detail::OTHER},
			{17, 5, Category::RIBBON, Detail::OTHER},
			{18, 5, Category::KASU, Detail::OTHER},
			{19, 5, Category::KASU, Detail::OTHER},

			{20, 6, Category::ANIMAL, Detail::BUTTERFLY},
			{21, 6, Category::RIBBON, Detail::BLUE},
			{22, 6, Category::KASU, Detail::OTHER},
			{23, 6, Category::KASU, Detail::OTHER},

			{24, 7, Category::ANIMAL, Detail::BOAR},
			{25, 7, Category::RIBBON, Detail::OTHER},
			{26, 7, Category::KASU, Detail::OTHER},
			{27, 7, Category::KASU, Detail::OTHER},

			{28, 8, Category::BRIGHT, Detail::MOON},
			{29, 8, Category::ANIMAL, Detail::OTHER},
			{30, 8, Category::KASU, Detail::OTHER},
			{31, 8, Category::KASU, Detail::OTHER},

			{32, 9, Category::ANIMAL, Detail::SAKE},
			{33, 9, Category::RIBBON, Detail::BLUE},
			{34, 9, Category::KASU, Detail::OTHER},
			{35, 9, Category::KASU, Detail::OTHER},

			{36, 10, Category::ANIMAL, Detail::DEER},
			{37, 10, Category::RIBBON, Detail::BLUE},
			{38, 10, Category::KASU, Detail::OTHER},
			{39, 10, Category::KASU, Detail::OTHER},

			{40, 11, Category::BRIGHT, Detail::RAINMAN},
			{41, 11, Category::ANIMAL, Detail::OTHER},
			{42, 11, Category::RIBBON, Detail::OTHER},
			{43, 11, Category::KASU, Detail::OTHER},

			{44, 12, Category::BRIGHT, Detail::OTHER},
			{45, 12, Category::KASU, Detail::OTHER},
			{46, 12, Category::KASU, Detail::OTHER},
			{47, 12, Category::KASU, Detail::OTHER}
		}
	};
};

