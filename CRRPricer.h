#pragma once
#include "BinaryTree.h"
#include "Option.h"
#include <vector>
#include <stdexcept>

class CRRPricer {
private:
    Option* _option;
    BinaryTree<double> _priceTree;
    BinaryTree<bool> _exerciseTree; // To store the early exercise policy
    int _depth;
    double _assetPrice;
    double _up;
    double _down;
    double _interestRate;

    void validateNoArbitrage() const;

public:
    CRRPricer(Option* option, int depth, double assetPrice, double up, double down, double interestRate);
    CRRPricer(Option* option, int depth, double assetPrice, double r, double sigma);

    void compute();
    double get(int depth, int index) const;
    bool getExercise(int depth, int index) const;
    double operator()(bool closed_form = false);
};