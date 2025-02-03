#pragma once
#include <random>

class MT {
private:
    static std::mt19937 _generator;

    MT() = default; // Private constructor to prevent instantiation

public:
    // Delete copy constructor and assignment operator to ensure singleton behavior
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    // Uniform random variable in [0, 1]
    static double rand_unif();

    // Standard normal random variable
    static double rand_norm();
};