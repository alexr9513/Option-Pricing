#pragma once
#include "EuropeanVanillaOption.h"
#include "Option.h"


EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {
    if (expiry < 0 || strike < 0) {
        throw std::invalid_argument("Expiry and strike must be nonnegative.");
    }
}

double EuropeanVanillaOption::GetStrike() const{
    return _strike;
}
