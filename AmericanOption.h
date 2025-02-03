#pragma once
#include "Option.h"
#include <stdexcept>

class AmericanOption : public Option {
protected:
    double _strike;

public:
    AmericanOption(double expiry, double strike)
        : Option(expiry), _strike(strike) {
        if (strike < 0 || expiry < 0) {
            throw std::invalid_argument("Negative values are not allowed.");
        }
    }
    double getStrike() const override { return _strike; }
    bool isAmericanOption() const override { return true; }
};