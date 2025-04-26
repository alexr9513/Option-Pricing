#pragma once
#include "BlackScholesPricer.h"
#include <cmath>
#include <algorithm>

BlackScholesPricer::BlackScholesPricer(Option* option, double assetPrice, double interestRate, double volatility)
    : _option(option), _assetPrice(assetPrice), _interestRate(interestRate), _volatility(volatility) {}

double BlackScholesPricer::d1() const {
    return (std::log(_assetPrice / _option->getStrike()) +
        (_interestRate + 0.5 * _volatility * _volatility) * _option->getExpiry()) /
        (_volatility * std::sqrt(_option->getExpiry()));
}

double BlackScholesPricer::d2() const {
    return d1() - _volatility * std::sqrt(_option->getExpiry());
}

double BlackScholesPricer::operator()() const {
    double S = _assetPrice;
    double K = _option->getStrike();
    double T = _option->getExpiry();
    double r = _interestRate;
    double sigma = _volatility;

    if (_option->isDigital()) {
        // Digital options pricing
        if (_option->getOptionType() == OptionType::Call) { // Digital call
            return std::exp(-r * T) * 0.5 * std::erfc(-d2() / std::sqrt(2));
        }
        else { // Digital put
            return std::exp(-r * T) * 0.5 * std::erfc(d2() / std::sqrt(2));
        }
    }
    else {
        // Vanilla options pricing
        if (_option->getOptionType() == OptionType::Call) { // Call
            return S * 0.5 * std::erfc(-d1() / std::sqrt(2)) -
                K * std::exp(-r * T) * 0.5 * std::erfc(-d2() / std::sqrt(2));
        }
        else { // Put
            return K * std::exp(-r * T) * 0.5 * std::erfc(d2() / std::sqrt(2)) -
                S * 0.5 * std::erfc(d1() / std::sqrt(2));
        }
    }
}

double BlackScholesPricer::delta() const {
    double pi = 3.14159265358979323846;
    if (_option->isDigital()) {
        // Digital options delta
        return (_option->getOptionType() == OptionType::Call)
            ? std::exp(-0.5 * d2() * d2()) / (_volatility * std::sqrt(2 * pi * _option->getExpiry()))
            : -std::exp(-0.5 * d2() * d2()) / (_volatility * std::sqrt(2 * pi * _option->getExpiry()));
    }
    else {
        // Vanilla options delta
        return (_option->getOptionType() == OptionType::Call)
            ? 0.5 * std::erfc(-d1() / std::sqrt(2))
            : -0.5 * std::erfc(-d1() / std::sqrt(2));
    }
}
