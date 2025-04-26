#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "CallOption.h"
#include "PutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "BlackScholesMCPricer.h"

int main(int argc, char* argv[]) {
    if (argc < 10) {
        std::cerr << "Usage: ./bs_mc_pricer option_type S0 K T r sigma m nb_simulations ci_target\n";
        return 1;
    }

    std::string option_type = argv[1];
    double S0 = atof(argv[2]);
    double K = atof(argv[3]);
    double T = atof(argv[4]);
    double r = atof(argv[5]);
    double sigma = atof(argv[6]);
    double m = atof(argv[7]); // number of fixings per year (for Asian options)
    int nb_simulations = atoi(argv[8]); // number of simulations each batch
    double ci_target = atof(argv[9]);   // target confidence interval width

    Option* option = nullptr;

    if (option_type == "call") {
        option = new CallOption(T, K);
    } else if (option_type == "put") {
        option = new PutOption(T, K);
    } else if (option_type == "digital_call") {
        option = new EuropeanDigitalCallOption(T, K);
    } else if (option_type == "digital_put") {
        option = new EuropeanDigitalPutOption(T, K);
    } else if (option_type == "asian_call") {
        std::vector<double> fixing_dates;
        for (int i = 1; i <= m * T; i++) {
            fixing_dates.push_back(i / m);
        }
        option = new AsianCallOption(fixing_dates, K);
    } else if (option_type == "asian_put") {
        std::vector<double> fixing_dates;
        for (int i = 1; i <= m * T; i++) {
            fixing_dates.push_back(i / m);
        }
        option = new AsianPutOption(fixing_dates, K);
    } else {
        std::cerr << "Unknown option type: " << option_type << std::endl;
        return 1;
    }

    BlackScholesMCPricer pricer(option, S0, r, sigma);
    std::vector<double> ci;

    do {
        pricer.generate(nb_simulations);
        ci = pricer.confidenceInterval();
    } while (ci[1] - ci[0] > ci_target);

    double price = pricer();
    std::cout << price << std::endl;

    delete option;
    return 0;
}