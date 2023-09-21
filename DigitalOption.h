#pragma once
#include "Option.h"

#pragma region DigitalOption
class DigitalOption : public Option
{
	public:
		DigitalOption(double, double);
		~DigitalOption();

		double GetStrike() override;
		bool isDigital() override;

		virtual OptionType GetOptionType() override = 0;
		virtual double payoff(double) override = 0;

		friend class BlackScholesPricer;

	protected:
		double m_strike;
};
#pragma endregion

#pragma region DigitalCallOption
class DigitalCallOption : public DigitalOption
{
	public:
		DigitalCallOption(double, double);
		~DigitalCallOption();

		OptionType GetOptionType() override;
		double payoff(double) override;
};
#pragma endregion

#pragma region DigitalPutOption
class DigitalPutOption : public DigitalOption
{
	public:
		DigitalPutOption(double, double);
		~DigitalPutOption();

		OptionType GetOptionType() override;
		double payoff(double) override;
};
#pragma endregion
