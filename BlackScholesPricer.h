#pragma once
#include "Option.h"
#include <cmath>

class BlackScholesPricer {
private:
    Option* _option;
    double _assetPrice;
    double _interestRate;
    double _volatility;

    double d1() const;
    double d2() const;

public:
    BlackScholesPricer(Option* option, double assetPrice, double interestRate, double volatility);
    double operator()() const;
    double delta() const;
};
