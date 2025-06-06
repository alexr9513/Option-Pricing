#pragma once
#include "EuropeanVanillaOption.h"
#include "OptionType.h"

class PutOption : public EuropeanVanillaOption {
public:
    PutOption(double expiry, double strike)
        : EuropeanVanillaOption(expiry, strike) {}

    double payoff(double assetPrice) const override {
        return (assetPrice < _strike) ? (_strike - assetPrice) : 0.0;
    }

    OptionType getOptionType() const override {
        return OptionType::Put;
    }
};