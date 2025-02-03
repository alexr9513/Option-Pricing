#pragma once
#include "AsianOption.h"
#include <stdexcept>

double AsianOption::payoffPath(const std::vector<double>& assetPrices) const {
    if (assetPrices.empty()) {
        throw std::invalid_argument("Asset prices vector is empty.");
    }

    double sum = 0.0;
    for (double price : assetPrices) {
        sum += price;
    }
    double average = sum / assetPrices.size();
    return payoff(average);
}
