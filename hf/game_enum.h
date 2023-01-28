#pragma once

enum class Phase
{
	MATCH_FROM_HAND,
	MATCH_FROM_DRAW,
	YAKU,
	KOI_KOI,
	AGARI,
	NONE,
};


enum class Response
{
	PLAY_FIELD,
	CHANGE_CARD,
	CONTINUE,
	VIEW_MY_COLLECTION,
	VIEW_THEIR_COLLECTION,	
	NONE,
};


enum class Result
{
	OK,
	NO_MATCH,
	INVALID,
	MISMATCH,
	NONE,
};


enum class Screen
{
	GAME,
	MY_COLLECTION,
	THEIR_COLLECTION,
	NONE,
};