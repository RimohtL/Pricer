#pragma once
#include <iostream>
#include <vector>

enum class OptionType { Call, Put };

class Option
{
	public:
		Option(double);
		virtual ~Option();

		double GetExpiry();

		virtual double payoff(double) = 0;
		virtual double GetStrike() = 0;
		virtual OptionType GetOptionType() = 0;
		virtual std::vector<double> getTimeSteps();
		virtual double payoffPath(std::vector<double>);
		virtual bool isAsianOption();
		virtual bool isAmericanOption();
		virtual bool isDigital();

	protected: // Only accessible for children classes
		double _expiry;
};
