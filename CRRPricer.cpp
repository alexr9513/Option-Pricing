#pragma once
#include <iostream>
#include <cmath>
#include "CRRPricer.h"
#include "BinaryTree.h"
#include "Option.h"

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up,
	double down, double interest_rate)
{
	this->_option = option;
	this->_depth = depth;
	this->_asset_price = asset_price;
	// no arbitrage iif down < r < up
	if (down < interest_rate && interest_rate < up) {
		this->_up = up;
		this->_down = down;
		this->_interest_rate = interest_rate;
	}
	else {
		this->_up = 0;
		this->_down = 0;
		this->_interest_rate = 0;
	}

	_tree.SetDepth(depth + 1);
}

void CRRPricer::compute() {
	// Step 1: Initialize asset prices at each node
	for (int i = 0; i <= _depth; i++) {
		for (int j = 0; j<= i; j++) {
			double value = _asset_price * std::pow(1 + _up, j) * std::pow(1 + _down,i-j);
			_tree.SetNode(i, j, value);
		}
	}

	// Step 2: Calculate option values at maturity (N-th level)
	for (int j = 0; j <= _depth; j++) {
		double payoff = _option->payoff(_tree.GetNode(_depth, j));
		_tree.SetNode(_depth, j, payoff);
	}

	// Step 3: Backward induction to find option price at root
	double q = (_interest_rate - _down) / (_up - _down);
	for (int i = _depth - 1; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			double value = (q * _tree.GetNode(i + 1, j + 1) + (1 - q) * _tree.GetNode(i + 1, j)) / (1 + _interest_rate);
			_tree.SetNode(i, j, value);
		}
	}
}

double CRRPricer::get(int i, int j) {
	return _tree.GetNode(i, j);
}

double CRRPricer::operator()(bool closed_form) {
	if (closed_form) {
		return closedFormPrice();
	}
	compute();
	return _tree.GetNode(0, 0);
}

// Closed-form solution for option price using the binomial model
double CRRPricer::closedFormPrice() {
	double q = (_interest_rate - _down) / (_up - _down);
	double option_price = 0.0;

	for (int i = 0; i <= _depth; i++) {
		double prob = binomialCoefficient(_depth, i) * std::pow(q, i) * std::pow(1 - q, _depth - i);
		double payoff = _option->payoff(_asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i));
		option_price += prob * payoff;
	}

	return option_price / std::pow(1 + _interest_rate, _depth);
}

// Helper function to compute binomial coefficient "n choose k"
int CRRPricer::binomialCoefficient(int n, int k) {
	int coeff = 1;
	for (int i = 1; i <= k; i++) {
		coeff = coeff * (n - i + 1) / i;
	}
	return coeff;
}

void CRRPricer::display() {
	_tree.display();
}