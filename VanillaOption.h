#pragma once
#include "Option.h"
#include <iostream>

#pragma region VanillaOption
class VanillaOption : public Option
{
	public:
		VanillaOption(double, double);
		~VanillaOption();

		double GetStrike() override;

		virtual OptionType GetOptionType() override = 0;
		virtual double payoff(double) override = 0;

		friend class BlackScholesPricer;

	protected:
		double m_strike;
};
#pragma endregion

#pragma region CallOption
class CallOption : public VanillaOption
{
	public:
		CallOption(double, double);
		~CallOption();

		OptionType GetOptionType() override;
		double payoff(double) override;
};
#pragma endregion

#pragma region PutOption
class PutOption : public VanillaOption
{
	public:
		PutOption(double, double);
		~PutOption();

		OptionType GetOptionType() override;
		double payoff(double) override;
};
#pragma endregion
