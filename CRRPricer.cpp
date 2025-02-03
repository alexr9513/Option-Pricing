#pragma once
#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

CRRPricer::CRRPricer(Option* option, int depth, double assetPrice, double up, double down, double interestRate)
    : _option(option), _depth(depth), _assetPrice(assetPrice), _up(up), _down(down), _interestRate(interestRate) {
    validateNoArbitrage();
    _priceTree.setDepth(depth);
    _exerciseTree.setDepth(depth);
}

CRRPricer::CRRPricer(Option* option, int depth, double assetPrice, double r, double sigma)
    : _option(option), _depth(depth), _assetPrice(assetPrice) {
    // Calculate time step
    double T = _option->getExpiry();
    double h = T / depth;

    // Calculate U, D, and R
    _up = std::exp((r + 0.5 * sigma * sigma) * h + sigma * std::sqrt(h)) - 1;
    _down = std::exp((r + 0.5 * sigma * sigma) * h - sigma * std::sqrt(h)) - 1;
    _interestRate = std::exp(r * h) - 1;

    validateNoArbitrage();
    _priceTree.setDepth(depth);
    _exerciseTree.setDepth(depth);
}

void CRRPricer::validateNoArbitrage() const {
    if (!(_down < _interestRate && _interestRate < _up)) {
        throw std::invalid_argument("Arbitrage conditions violated: Ensure D < R < U.");
    }
}

void CRRPricer::compute() {
    // Initialize terminal payoffs
    for (int i = 0; i <= _depth; ++i) {
        double terminalPrice = _assetPrice * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
        _priceTree.setNode(_depth, i, _option->payoff(terminalPrice));
        _exerciseTree.setNode(_depth, i, false); // No early exercise at expiry
    }

    // Backward induction
    double q = (_interestRate - _down) / (_up - _down);
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double continuationValue = (q * _priceTree.getNode(n + 1, i + 1) +
                (1 - q) * _priceTree.getNode(n + 1, i)) /
                (1 + _interestRate);
            double intrinsicValue = _option->payoff(_assetPrice * std::pow(1 + _up, i) * std::pow(1 + _down, n - i));
            if (_option->isAmericanOption() && intrinsicValue > continuationValue) {
                _priceTree.setNode(n, i, intrinsicValue);
                _exerciseTree.setNode(n, i, true); // Early exercise at this node
            }
            else {
                _priceTree.setNode(n, i, continuationValue);
                _exerciseTree.setNode(n, i, false); // No early exercise
            }
        }
    }
}

double CRRPricer::get(int depth, int index) const {
    return _priceTree.getNode(depth, index);
}

bool CRRPricer::getExercise(int depth, int index) const {
    return _exerciseTree.getNode(depth, index);
}

double CRRPricer::operator()(bool closed_form) {
    if (!closed_form) {
        compute();
        return _priceTree.getNode(0, 0);
    }

    // Closed-form implementation for European options
    if (_option->isAmericanOption()) {
        throw std::logic_error("Closed-form pricing is not available for American options.");
    }

    double q = (_interestRate - _down) / (_up - _down);
    double price = 0.0;
    for (int i = 0; i <= _depth; ++i) {
        double prob = std::exp(std::lgamma(_depth + 1) - std::lgamma(i + 1) - std::lgamma(_depth - i + 1)) *
            std::pow(q, i) * std::pow(1 - q, _depth - i);
        double terminalPrice = _assetPrice * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
        price += prob * _option->payoff(terminalPrice);
    }
    return price / std::pow(1 + _interestRate, _depth);
}
