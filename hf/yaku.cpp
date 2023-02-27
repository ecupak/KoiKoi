#include "yaku.h"


Yaku::Yaku(const Category& _category, const YakuName& _name, const int _score)
	: category(_category)
	, name(_name)
	, score(_score)
{	}


const Category Yaku::GetCategory() const
{
	return category;
}


const int Yaku::GetScore() const
{
	return score;
}


const std::string Yaku::GetDisplayYakuName() const
{
	switch (name)
	{
	case YakuName::BRIGHT_5:
		return "Bright 5";
	case YakuName::BRIGHT_4:
		return "Bright 4";
	case YakuName::BRIGHT_4_RAINY:
		return "Rainy Bright 4";
	case YakuName::BRIGHT_3:
		return "Bright 3";
	case YakuName::ANIMAL_ISO:
		return "Ino-Shika-Cho";
	case YakuName::ANIMAL_TANE:
		return "Tane";
	case YakuName::RIBBON_COMBO:
		return "Akatan - Aotan Combo";
	case YakuName::RIBBON_AKATAN:
		return "Akatan";
	case YakuName::RIBBON_AOTAN:
		return "Aotan";
	case YakuName::RIBBON_TANZAKU:
		return "Tanzaku";
	case YakuName::VIEWING_MOON:
		return "Moon Viewing";
	case YakuName::VIEWING_FLOWER:
		return "Blossom Viewing";
	case YakuName::KASU:
		return "Kasu";
	default:
		return "";
	}
}