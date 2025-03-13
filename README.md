# Option Pricing in C++

## Project Overview
This project involves implementing various financial models in C++ to price different types of options. The project is divided into four main parts:

1. **Black-Scholes Model**: Implementation of the Black-Scholes model for pricing European vanilla options.
2. **Cox-Ross-Rubinstein (CRR) Model**: Implementation of the CRR binomial tree model for pricing European options.
3. **Path-Dependent Options and Monte Carlo Simulation**: Implementation of path-dependent options (e.g., Asian options) and Monte Carlo simulation for pricing.
4. **American Options in the Binomial Model**: Extension of the CRR model to price American options.

## Project Structure

### Part I: Black-Scholes Model
- **Objective**: Implement the Black-Scholes model to price European vanilla options.
- **Classes**:
  - `Option`: Abstract base class with a pure virtual method `payoff(double)`.
  - `EuropeanVanillaOption`: Derived from `Option`, with additional attributes for strike price and option type (call/put).
  - `CallOption` and `PutOption`: Derived from `EuropeanVanillaOption`, implementing specific payoff functions.
  - `BlackScholesPricer`: Class to compute the price and delta of an option using the Black-Scholes formula.

### Part II: Cox-Ross-Rubinstein (CRR) Model
- **Objective**: Implement the CRR binomial tree model to price European options.
- **Classes**:
  - `BinaryTree<T>`: Template class to represent the binary tree structure used in the CRR model.
  - `CRRPricer`: Class to compute the price of an option using the CRR procedure. It also supports a closed-form formula for option pricing.
  - `EuropeanDigitalOption`: Derived from `Option`, with specific implementations for digital call and put options.

### Part III: Path-Dependent Options and Monte Carlo Simulation
- **Objective**: Implement path-dependent options (e.g., Asian options) and use Monte Carlo simulation for pricing.
- **Classes**:
  - `AsianOption`: Derived from `Option`, with a specific implementation for Asian options.
  - `AsianCallOption` and `AsianPutOption`: Derived from `AsianOption`, implementing specific payoff functions.
  - `MT`: Singleton class encapsulating a random number generator for Monte Carlo simulation.
  - `BlackScholesMCPricer`: Class to estimate the price of an option using Monte Carlo simulation.

### Part IV: American Options in the Binomial Model
- **Objective**: Extend the CRR model to price American options.
- **Classes**:
  - `AmericanOption`: Derived from `Option`, with specific implementations for American call and put options.
  - `CRRPricer`: Modified to handle American options, including the computation of early exercise policies.
