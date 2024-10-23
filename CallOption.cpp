#pragma once
#include <iostream>
#include <algorithm>
#include "CallOption.h"

CallOption::CallOption(double strike, double expiry) : EuropeanVanillaOption(strike,expiry){}

double CallOption::payoff(double S) const {
	return std::max(S - GetStrike(),0.0);
}

EuropeanVanillaOption::optionType CallOption::GetOptionType() const {
	return call;
}