#pragma once
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption {
	public:
		CallOption(double strike, double expiry);
		double payoff(double S) const override;
		optionType GetOptionType() const override;
};