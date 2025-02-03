#pragma once
#include <vector>
#include "OptionType.h"

class Option {
protected:
    double _expiry;

public:
    explicit Option(double expiry) : _expiry(expiry) {}
    virtual ~Option() = default;

    virtual OptionType getOptionType() const = 0;

    double getExpiry() const { return _expiry; }
    virtual double getStrike() const = 0;
    virtual bool isDigital() const { return false; }

    virtual double payoff(double assetPrice) const = 0;
    virtual double payoffPath(const std::vector<double>& assetPrices) const { return payoff(assetPrices.back()); };
    virtual bool isAsianOption() const { return false; }
    virtual bool isAmericanOption() const { return false; }
};
