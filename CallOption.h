#pragma once
#include "EuropeanVanillaOption.h"
#include "OptionType.h"

class CallOption : public EuropeanVanillaOption {
public:
    CallOption(double expiry, double strike)
        : EuropeanVanillaOption(expiry, strike) {}

    double payoff(double assetPrice) const override {
        return (assetPrice > _strike) ? (assetPrice - _strike) : 0.0;
    }

    OptionType getOptionType() const override {
        return OptionType::Call;
    }
};
