#pragma once
#include "Option.h"
#include <vector>

#pragma region AsianOption
class AsianOption : public Option
{
	public:
		AsianOption(std::vector<double>, double);
		~AsianOption();

		std::vector<double> getTimeSteps() override;
		double payoffPath(std::vector<double>) override;
		bool isAsianOption() override;
		double GetStrike() override;

		virtual double payoff(double) override = 0;
		virtual OptionType GetOptionType() override = 0;

	protected:
		std::vector<double> m_timeSteps;
		double m_strike;
};
#pragma endregion

#pragma region AsianCallOption
class AsianCallOption : public AsianOption
{
	public:
		AsianCallOption(std::vector<double>, double);
		~AsianCallOption();

		OptionType GetOptionType() override;
		double payoff(double) override;
};
#pragma endregion

#pragma region AsianPutOption
class AsianPutOption : public AsianOption
{
	public:
		AsianPutOption(std::vector<double>, double);
		~AsianPutOption();

		OptionType GetOptionType() override;
		double payoff(double) override;
};
#pragma endregion
