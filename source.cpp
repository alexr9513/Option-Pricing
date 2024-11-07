#pragma once
#include <iostream>
#include "BlackScholesPricer.h"
#include "CallOption.h"
#include "PutOption.h"
#include "CRRPricer.h"


int main()
{
    std::cout << "C++ project\n\n";

    std::cout << "Black-Scholes Pricer\n\n";

    double expiry = 0.2;         // Time to expiry in years
    double strike = 110;       // Strike price
    double assetPrice = 100;   // Current asset price
    double interestRate = 0.05;  // Risk-free interest rate (5%)
    double volatility = 0.1;     // Volatility (20%)

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


    // test call put parity, Call price - Put price = S - K.exp(-r.t)

    std::cout << "LS parity " << assetPrice - strike * std::exp(-interestRate * expiry) << std::endl;
    std::cout << "RS parity " << callPrice - putPrice << std::endl;

    std::cout << "\nCRR Pricer\n\n";
	CRRPricer crrPricer(&callOption,3, assetPrice,0.07,-0.07, interestRate);
	std::cout << "CRR Pricer using computed values: " << crrPricer(false) << std::endl;
    std::cout << "CRR Pricer using closed-form solution: " << crrPricer(true) << std::endl;
    std::cout << "tree:" << std::endl;
	crrPricer.display();

    return 0;
}
