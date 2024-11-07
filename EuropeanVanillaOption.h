#pragma once
# include "Option.h"

class BlackScholesPricer;

class EuropeanVanillaOption : public Option {

	private:
		double _strike;

	public:
		EuropeanVanillaOption(double strike,double expiry);
		double GetStrike() const;
		enum optionType { call, put };
		virtual optionType GetOptionType() const = 0;
		friend class BlackScholesPricer;
		virtual ~EuropeanVanillaOption() = default;
};