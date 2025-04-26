#include <iostream>
#include <cstdlib>
#include <string>
#include "CallOption.h"
#include "PutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "CRRPricer.h"

int main(int argc, char* argv[]) {
    if (argc < 8) {
        std::cerr << "Usage: ./crr_pricer option_type S0 K T r sigma N\n";
        return 1;
    }

    std::string option_type = argv[1];
    double S0 = atof(argv[2]);
    double K = atof(argv[3]);
    double T = atof(argv[4]);
    double r = atof(argv[5]);
    double sigma = atof(argv[6]);
    int N = atoi(argv[7]); // number of steps in the binomial tree

    Option* option = nullptr;

    if (option_type == "call") {
        option = new CallOption(T, K);
    } else if (option_type == "put") {
        option = new PutOption(T, K);
    } else if (option_type == "digital_call") {
        option = new EuropeanDigitalCallOption(T, K);
    } else if (option_type == "digital_put") {
        option = new EuropeanDigitalPutOption(T, K);
    } else if (option_type == "american_call") {
        option = new AmericanCallOption(T, K);
    } else if (option_type == "american_put") {
        option = new AmericanPutOption(T, K);
    } else {
        std::cerr << "Unknown option type: " << option_type << std::endl;
        return 1;
    }

    // Build CRR pricer using r and sigma
    CRRPricer pricer(option, N, S0, r, sigma);
    pricer.compute();
    double price = pricer();

    std::cout << price << std::endl;

    delete option;
    return 0;
}