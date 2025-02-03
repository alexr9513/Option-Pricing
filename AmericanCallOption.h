#pragma once
#include "AmericanOption.h"
#include "OptionType.h"

class AmericanCallOption : public AmericanOption {
public:
    AmericanCallOption(double expiry, double strike)
        : AmericanOption(expiry, strike) {}

    double payoff(double assetPrice) const override {
        return (assetPrice > _strike) ? (assetPrice - _strike) : 0.0;
    }

    OptionType getOptionType() const override {
        return OptionType::Call;
    }
};
