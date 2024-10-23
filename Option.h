#pragma once
#include <iostream>

class Option
{
	private :
		double _expiry;

	public:
		Option(double e);
		double GetExpiry() const;
		virtual double payoff(double) const = 0;
		virtual ~Option() = default;

};
