#pragma once

enum class PlayerIs
{
	ACTIVE,
	INACTIVE,
	BOTH,
	NONE,
};


enum class State
{
	NORMAL,
	TESHI,
	KUTTSUKI,
	UNKNOWN,
};


enum class Phase
{
	MATCH_FROM_HAND,
	MATCH_FROM_DRAW,
	SCORING,
	END_TURN,
	NONE,
};


enum class Response
{
	CHANGE_CARD,
	CONTINUE,
	KOI_KOI,
	SHOBU,
	REMATCH,
	STOP,
	NONE,
};


enum class Result
{
	OK,
	NO_MATCH,
	INVALID,
	MISMATCH,
	AVAILABLE_MATCH,
	END_ROUND,
	NONE,
};


enum class Outcome
{
	CONTINUE,
	REPEAT,
};


enum class YakuResponse
{
	KOIKOI,
	SHOBU,
	NONE,
};


enum class CardAssignment
{
	PLAYED,
	FIELD,
};


enum class Screen
{
	GAME,
	YAKU,
	CAPTURES,
	NONE,
};