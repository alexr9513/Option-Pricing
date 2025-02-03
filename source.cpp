#include <iostream>
#include <vector>
#include "CallOption.h"
#include "PutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "CRRPricer.h"
#include "BlackScholesPricer.h"
#include "BlackScholesMCPricer.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"

void CRRPricerTest() {
    double S0(100), K(101), T(5), r(0.01), sigma(0.1);
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalCallOption(T, K));
    opt_ptrs.push_back(new AmericanCallOption(T, K));
    opt_ptrs.push_back(new PutOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalPutOption(T, K));
    opt_ptrs.push_back(new AmericanPutOption(T, K));

    CRRPricer* pricer;

    double N(5), U(0.05), D(-0.045), R(0.01);
    for (auto& opt_ptr : opt_ptrs) {

        pricer = new CRRPricer(opt_ptr, N, S0, U, D, R);

        pricer->compute();

        std::cout << "price: " << (*pricer)() << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;

    }
}

void BlackScholesTest() {
    double S0(100), K(101), T(5), r(0.01), sigma(0.1);
    CallOption opt1(T, K);
    EuropeanDigitalCallOption opt2(T, K);
    PutOption opt3(T, K);
    EuropeanDigitalPutOption opt4(T, K);

    BlackScholesPricer pricer1(&opt1, S0, r, sigma);
    std::cout << "European call option price = " << pricer1() << std::endl;
    std::cout << std::endl;

    BlackScholesPricer pricer2(&opt2, S0, r, sigma);
    std::cout << "European digital call option price = " << pricer2() << std::endl;
    std::cout << std::endl;

    BlackScholesPricer pricer3(&opt3, S0, r, sigma);
    std::cout << "European put option price = " << pricer3() << std::endl;
    std::cout << std::endl;

    BlackScholesPricer pricer4(&opt4, S0, r, sigma);
    std::cout << "European digital put option price = " << pricer4() << std::endl;
    std::cout << std::endl;
}

void BlackScholesMCTest() {

    double S0(100), K(101), T(5), r(0.01), sigma(0.1);

    std::vector<double> fixing_dates;
    for (int i = 1; i <= 50; i++) {
        fixing_dates.push_back(0.1 * i);
    }
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalCallOption(T, K));
    opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
    opt_ptrs.push_back(new PutOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalPutOption(T, K));
    opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));

    std::vector<double> ci;
    BlackScholesMCPricer* pricer;

    for (auto& opt_ptr : opt_ptrs) {
        pricer = new BlackScholesMCPricer(opt_ptr, S0, r, sigma);
        do {
            pricer->generate(1000000);
            ci = pricer->confidenceInterval();
        } while (ci[1] - ci[0] > 1e-2);
        std::cout << "price: " << (*pricer)() << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;
    }
}


int main() {
    std::cout <<"CRR pricer test\n" << std::endl;
    CRRPricerTest();
    std::cout << "\nBlack-Scholes pricer test\n" << std::endl;
    BlackScholesTest();
	std::cout << "\nBlack-Scholes-MC pricer test\n" << std::endl;
    BlackScholesMCTest();
	return 0;
}