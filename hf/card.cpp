#include "card.h"


const std::string Card::GetDisplayID() const
{
	std::string prefix{ "" };
	if (id < 10) prefix = "0";
	return prefix + std::to_string(id);
}


const std::string Card::GetDisplayMonth() const
{
	std::string prefix{ "M" };
	if (month < 10) prefix += "0";
	return prefix + std::to_string(month);
}


const std::string Card::GetDisplayCategory() const
{
	switch (category)
	{
	case Category::BRIGHT:
		return "BRIGHT";
	case Category::ANIMAL:
		return "ANIMAL";
	case Category::RIBBON:
		return "RIBBON";
	case Category::KASU:
		return "KASU";
	default:
		return "UNKNOWN";
	}
}


const std::string Card::GetDisplayDetail() const
{
	switch (detail)
	{
	case Detail::FLOWER:
		return "SAKURA CURTAIN";
	case Detail::MOON:
		return "MOON";
	case Detail::RAINMAN:
		return "RAINMAN";
	case Detail::BOAR:
		return "BOAR";
	case Detail::DEER:
		return "DEER";
	case Detail::BUTTERFLY:
		return "BUTTERFLY";
	case Detail::SAKE:
		return "SAKE CUP";
	case Detail::POEM:
		return "POEM";
	case Detail::BLUE:
		return "BLUE";
	default:
		return "";
	}
}


const int Card::GetMonth() const
{
	return month;
}


const Category Card::GetCategory() const
{
	return category;
}


const Detail Card::GetDetail() const
{
	return detail;
}