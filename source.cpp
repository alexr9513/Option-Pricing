#pragma once
#include <iostream>
#include "BlackScholesPricer.h"
#include "CallOption.h"
#include "PutOption.h"

int main()
{
    std::cout << "C++ project\n";

    double expiry = 1.0;         // Time to expiry in years
    double strike = 100.0;       // Strike price
    double assetPrice = 105.0;   // Current asset price
    double interestRate = 0.05;  // Risk-free interest rate (5%)
    double volatility = 0.2;     // Volatility (20%)

    // Create a Call Option
    CallOption callOption(expiry, strike);

    // Create a Black-Scholes Pricer for the Call Option
    BlackScholesPricer callPricer(&callOption, assetPrice, interestRate, volatility);

    // Calculate price and delta
    double callPrice = callPricer();
    double callDelta = callPricer.delta();

    std::cout << "Call Option Price: " << callPrice << std::endl;
    std::cout << "Call Option Delta: " << callDelta << std::endl;

    // Create a Put Option
    PutOption putOption(expiry, strike);

    // Create a Black-Scholes Pricer for the Put Option
    BlackScholesPricer putPricer(&putOption, assetPrice, interestRate, volatility);

    // Calculate price and delta
    double putPrice = putPricer();
    double putDelta = putPricer.delta();

    std::cout << "Put Option Price: " << putPrice << std::endl;
    std::cout << "Put Option Delta: " << putDelta << std::endl;

    return 0;
}
