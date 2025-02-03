#pragma once
#include "Option.h"
#include <stdexcept>

class EuropeanDigitalOption : public Option {
protected:
    double _strike;

public:
    EuropeanDigitalOption(double expiry, double strike)
        : Option(expiry), _strike(strike) {
        if (strike < 0 || expiry < 0) {
            throw std::invalid_argument("Negative values are not allowed.");
        }
    }

	double getStrike() const { return _strike; }

    bool isDigital() const override { return true; }
};
