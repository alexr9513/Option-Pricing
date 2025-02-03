#pragma once
#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include "MT.h"
#include <cmath>
#include <stdexcept>

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initialPrice, double interestRate, double volatility)
    : _option(option), _initialPrice(initialPrice), _interestRate(interestRate), _volatility(volatility),
    _numPaths(0), _priceEstimate(0.0), _priceSquaredSum(0.0) {}

void BlackScholesMCPricer::generate(int numPaths) {
    if (!_option->isAsianOption()) {
        double dt = _option->getExpiry();
        double drift = (_interestRate - 0.5 * _volatility * _volatility) * dt;
        double diffusion = _volatility * std::sqrt(dt);

        for (int i = 0; i < numPaths; ++i) {
            double z = MT::rand_norm();
            double endPrice = _initialPrice * std::exp(drift + diffusion * z);
            double discountedPayoff = std::exp(-_interestRate * dt) * _option->payoff(endPrice);

            // Update mean and variance
            _priceEstimate = ((_numPaths * _priceEstimate) + discountedPayoff) / (_numPaths + 1);
            _priceSquaredSum += discountedPayoff * discountedPayoff;
            _numPaths++;
        }
    }
    else
    {
        // Get the time steps from the AsianOption
        const std::vector<double>& timeSteps = dynamic_cast<const AsianOption*>(_option)->getTimeSteps();
        int numSteps = timeSteps.size();

        for (int i = 0; i < numPaths; ++i) {
            // Simulate the price path
            std::vector<double> pathPrices(numSteps);

            // Initialize the first step
            double t1 = timeSteps[0];
            double drift = (_interestRate - 0.5 * _volatility * _volatility) * t1;
            double diffusion = _volatility * std::sqrt(t1);
            double z = MT::rand_norm(); // Random normal variable
            pathPrices[0] = _initialPrice * std::exp(drift + diffusion * z);

            // Simulate the rest of the path
            for (int j = 1; j < numSteps; ++j) {
                double tk = timeSteps[j] - timeSteps[j - 1];
                double drift = (_interestRate - 0.5 * _volatility * _volatility) * tk;
                double diffusion = _volatility * std::sqrt(tk);
                double z = MT::rand_norm(); // Random normal variable
                pathPrices[j] = pathPrices[j - 1] * std::exp(drift + diffusion * z);
            }

            // Compute the discounted payoff
            double discountedPayoff = std::exp(-_interestRate * _option->getExpiry()) * _option->payoffPath(pathPrices);

            // Update mean and variance
            _priceEstimate = ((_numPaths * _priceEstimate) + discountedPayoff) / (_numPaths + 1);
            _priceSquaredSum += discountedPayoff * discountedPayoff;
            _numPaths++;
        }
	}
}

double BlackScholesMCPricer::operator()() const {
    if (_numPaths == 0) {
        throw std::logic_error("No paths generated yet.");
    }
    return _priceEstimate;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (_numPaths == 0) {
        throw std::logic_error("No paths generated yet.");
    }

    double variance = (_priceSquaredSum / _numPaths) - (_priceEstimate * _priceEstimate);
    double stdError = std::sqrt(variance / _numPaths);
    double margin = 1.96 * stdError; // 95% confidence interval

    return { _priceEstimate - margin, _priceEstimate + margin };
}
