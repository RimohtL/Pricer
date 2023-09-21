#pragma once
#include "Option.h"

#pragma region AmericanOption
class AmericanOption : public Option
{
	public:
		AmericanOption(double, double);
		~AmericanOption();

		bool isAmericanOption() override;
		double GetStrike() override;

		virtual double payoff(double) override = 0;
		virtual OptionType GetOptionType() override = 0;

	protected:
		double m_strike;
};
#pragma endregion

#pragma region AmericanOption
class AmericanCallOption : public AmericanOption
{
	public:
		AmericanCallOption(double, double);
		~AmericanCallOption();

		OptionType GetOptionType() override;
		double payoff(double) override;
};
#pragma endregion

#pragma region AmericanOption
class AmericanPutOption : public AmericanOption
{
	public:
		AmericanPutOption(double, double);
		~AmericanPutOption();

		OptionType GetOptionType() override;
		double payoff(double) override;
};
#pragma endregion

