#pragma once

#include <string>

#include "card_enum.h"


class Card
{
public:
	Card() {};

	Card(int _id, int _month, Category _category, Detail _detail)
		: id{ _id }
		, month{ _month }
		, category{ _category }
		, detail{ _detail }
	{	}

	const std::string GetDisplayID() const;
	const std::string GetDisplayMonth() const;
	const std::string GetDisplayCategory() const;
	const std::string GetDisplayDetail() const;

	const int GetMonth() const;
	const Category GetCategory() const;
	const Detail GetDetail() const;

private:
	int id{ -1 };
	int month{ -1 };
	Category category{ Category::UNDEFINED };
	Detail detail{ Detail::UNDEFINED };
};