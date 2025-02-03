#pragma once
#include "EuropeanDigitalOption.h"
#include "OptionType.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalPutOption(double expiry, double strike)
        : EuropeanDigitalOption(expiry, strike) {}

    double payoff(double assetPrice) const override {
        return (assetPrice <= _strike) ? 1.0 : 0.0;
    }

    OptionType getOptionType() const override {
        return OptionType::Put;
    }
};