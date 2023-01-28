#pragma once

#include <string>


enum class YakuName
{
	BRIGHT_5,
	BRIGHT_4,
	BRIGHT_4_RAINY,
	BRIGHT_3,

	ANIMAL_ISO,
	ANIMAL_TANE,

	RIBBON_COMBO,
	RIBBON_AKATAN,
	RIBBON_AOTAN,
	RIBBON_TANZAKU,

	VIEWING_MOON,
	VIEWING_FLOWER,

	KASU,

	NONE,
};


struct Yaku
{
public:
	Yaku(const YakuName& _name, const int _score);

	const int GetScore() const;
	const std::string GetDisplayYakuName() const;

private:
	YakuName name{ YakuName::NONE };
	int score{ 0 };
};