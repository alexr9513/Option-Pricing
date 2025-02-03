#pragma once
#include "AsianOption.h"
#include <stdexcept>

class AsianCallOption : public AsianOption {
public:
    AsianCallOption(const std::vector<double>& timeSteps, double strike)
        : AsianOption(timeSteps.back(), timeSteps), _strike(strike) {
        if (strike < 0) {
            throw std::invalid_argument("Strike price cannot be negative.");
        }
    }

	OptionType getOptionType() const override { return OptionType::Call; }

    double getStrike() const { return _strike; }

    double payoff(double averagePrice) const override {
        return (averagePrice > _strike) ? (averagePrice - _strike) : 0.0;
    }

private:
    double _strike;
};