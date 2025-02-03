#pragma once
#include "Option.h"
#include <vector>

class AsianOption : public Option {
protected:
    std::vector<double> _timeSteps;

public:
    AsianOption(double expiry, const std::vector<double>& timeSteps)
        : Option(expiry), _timeSteps(timeSteps) {}

    const std::vector<double>& getTimeSteps() const { return _timeSteps; }
    double payoffPath(const std::vector<double>& assetPrices) const override;
    bool isAsianOption() const override { return true; }
};
