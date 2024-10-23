#pragma once
#include <iostream>
#include <algorithm>
#include "PutOption.h"

PutOption::PutOption(double strike, double expiry) : EuropeanVanillaOption(strike, expiry) {}

double PutOption::payoff(double S) const {
	return std::max(GetStrike()-S, 0.0);
}

EuropeanVanillaOption::optionType PutOption::GetOptionType() const {
	return put;
}