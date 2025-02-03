#pragma once
#include "MT.h"

// Initialize the static random number generator
std::mt19937 MT::_generator(std::random_device{}());

double MT::rand_unif() {
    static std::uniform_real_distribution<double> uniform_dist(0.0, 1.0);
    return uniform_dist(_generator);
}

double MT::rand_norm() {
    static std::normal_distribution<double> normal_dist(0.0, 1.0);
    return normal_dist(_generator);
}