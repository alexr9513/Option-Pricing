#pragma once
#include "AmericanOption.h"
#include "OptionType.h"

class AmericanPutOption : public AmericanOption {
public:
    AmericanPutOption(double expiry, double strike)
        : AmericanOption(expiry, strike) {}

    double payoff(double assetPrice) const override {
        return (assetPrice < _strike) ? (_strike - assetPrice) : 0.0;
    }

    OptionType getOptionType() const override {
        return OptionType::Put;
    }
};
