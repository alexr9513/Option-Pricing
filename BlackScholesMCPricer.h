#pragma once
#include "Option.h"
#include "MT.h"
#include <vector>

class BlackScholesMCPricer {
private:
    Option* _option;
    double _initialPrice;
    double _interestRate;
    double _volatility;
    int _numPaths;
    double _priceEstimate;
    double _priceSquaredSum; // To calculate variance

public:
    BlackScholesMCPricer(Option* option, double initialPrice, double interestRate, double volatility);

    void generate(int numPaths);
    double operator()() const;
    std::vector<double> confidenceInterval() const;

    int getNbPaths() const { return _numPaths; }
};