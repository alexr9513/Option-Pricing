#pragma once
#include "EuropeanVanillaOption.h"

class BlackScholesPricer {

private:
	EuropeanVanillaOption* _option;
	double _S;
	double _r;
	double _sigma;

public:
	BlackScholesPricer(EuropeanVanillaOption* option, double asset_price,
		double interest_rate, double volatility);
	double operator()() const;
	double delta() const;

};