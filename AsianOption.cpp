#include "AsianOption.h"

#pragma region AsianOption
// Constructor
AsianOption::AsianOption(std::vector<double> timeSteps, double strike) : Option(timeSteps.back())
{
	if (strike <= 0)
		throw std::invalid_argument("Strike should be nonnegative");
	else {
		m_strike = strike;
		m_timeSteps = timeSteps;
	}
}

// Destructor
AsianOption::~AsianOption() { }

// Overriden version returning all the time steps of the option to compute the payoff paths
std::vector<double> AsianOption::getTimeSteps() { return m_timeSteps; }

// Returns the payoff of one path
double AsianOption::payoffPath(std::vector<double> spot_prices)
{
	long m = spot_prices.size();
	double sum = 0;

	for (int i = 0; i < m; i++)
		sum += spot_prices.at(i);

	double mean = sum / m;
	return payoff(mean);
}

// Overriden version returning true to indicate that this option is asian
bool AsianOption::isAsianOption() { return true; }

// Overriden version returning the strike 
double AsianOption::GetStrike() { return m_strike; }

#pragma endregion

#pragma region AsianCallOption
// Constructor
AsianCallOption::AsianCallOption(std::vector<double> timeSteps, double strike) : AsianOption(timeSteps, strike) { }

// Destructor
AsianCallOption::~AsianCallOption() { }

// Returns the type of the option, in this case a call
OptionType AsianCallOption::GetOptionType() { return OptionType::Call; }

// Returns the payoff of a call
double AsianCallOption::payoff(double spot_price) { return std::max(spot_price - m_strike, 0.0); }
#pragma endregion

#pragma region AsianPutOption
// Constructor
AsianPutOption::AsianPutOption(std::vector<double> timeSteps, double strike) : AsianOption(timeSteps, strike) { }

// Destructor
AsianPutOption::~AsianPutOption() { }

// Returns the type of the option, in this case a put
OptionType AsianPutOption::GetOptionType() { return OptionType::Put; }

// Returns the payoff of a put
double AsianPutOption::payoff(double spot_price) { return std::max(m_strike - spot_price, 0.0); }
#pragma endregion
