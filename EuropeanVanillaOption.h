#pragma once
# include "Option.h"

class EuropeanVanillaOption : Option {

	private:
		double _strike;

	public:
		EuropeanVanillaOption(double strike,double expiry);
		double GetStrike() const;
		enum optionType { call, put };
		virtual optionType GetOptionType() const = 0;
		virtual ~EuropeanVanillaOption() = default;
};