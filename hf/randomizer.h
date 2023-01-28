#pragma once

#include <random>


class Randomizer
{
public:
	static std::mt19937 rng;

private:
	Randomizer() { }
};


std::mt19937 Randomizer::rng{ std::random_device{}() };