#pragma once
#include "BlackScholesPricer.h"
#include <cmath>

// Standard normal cumulative distribution function
double N(double x) {
	return 0.5 * std::erfc(-x / std::sqrt(2));
}

BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double asset_price,
	double interest_rate, double volatility) 
	: _option(option), _S(asset_price), _r(interest_rate), _sigma(volatility) {}

double BlackScholesPricer::operator()() const {
	double T = _option->GetExpiry();
	double K = _option->GetStrike();
	double S = _S;
	double r = _r;
	double sigma = _sigma;

	double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
	double d2 = d1 - sigma * std::sqrt(T);

	if(_option->GetOptionType() == EuropeanVanillaOption::call)
	{
		return S * N(d1) - N(d2) * K * std::exp(-r * T);
	}
	else
	{
		return N(-d2) * K * std::exp(-r * T) - N(-d1) * S;
	}
}

double BlackScholesPricer::delta() const {
	double T = _option->GetExpiry();
	double K = _option->GetStrike();
	double S = _S;
	double r = _r;
	double sigma = _sigma;

	double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

	if (_option->GetOptionType() == EuropeanVanillaOption::call)
	{
		return N(d1);
	}
	else
	{
		return -N(-d1);
	}
}