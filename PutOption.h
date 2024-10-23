#pragma once
#include "EuropeanVanillaOption.h"

class PutOption : EuropeanVanillaOption {
public :
	PutOption(double strike, double expiry);
	double payoff(double S) const override;
	optionType GetOptionType() const override;
};